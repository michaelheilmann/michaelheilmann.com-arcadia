// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

#include "Arcadia.Tools.TemplateEngine.Library/Context.h"

#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"
#include "Arcadia.Tools.TemplateEngine.Library/FileContext.h"

#include "Arcadia.Tools.TemplateEngine.Library/Library.h"

static void
Context_constructImpl
  (
    Arcadia_Thread* thread,
    Context* self
  );

static void
Context_destruct
  (
    Arcadia_Thread* thread,
    Context* self
  );

static void
Context_visit
  (
    Arcadia_Thread* thread,
    Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Context_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*) & Context_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Context_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Context", Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

void
Context_constructImpl
  (
    Arcadia_Thread* thread,
    Context* self
  )
{
  Arcadia_TypeValue _type = _Context_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  static const uint8_t sourceBytes[] =
    u8"{\n"
    u8"  generatorName : \"Michael Heilmann's Arcadia Template Engine\",\n"
    u8"  generatorHome : \"https://michaelheilmann.com\",\n"
    u8"}\n"
    ;
  Arcadia_String* sourceString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, sourceBytes, sizeof(sourceBytes) - 1)));
  self->environment = Environment_loadString(thread, sourceString);
  Arcadia_TemplateEngine_registerTimeLibrary(thread, self->environment);
  self->targetBuffer = NULL;
  self->target = NULL;
  self->temporaryBuffer = NULL;
  self->temporary = NULL;
  self->stack = NULL;
  self->files = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->log = Arcadia_Log_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Context_destruct
  (
    Arcadia_Thread* thread,
    Context* self
  )
{/*Intentionally empty.*/}

static void
Context_visit
  (
    Arcadia_Thread* thread,
    Context* self
  )
{
  if (self->log) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->log);
  }
  if (self->environment) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->environment);
  }
  if (self->targetBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->targetBuffer);
  }
  if (self->target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->target);
  }

  if (self->temporaryBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporaryBuffer);
  }
  if (self->temporary) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporary);
  }
  
  if (self->stack) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->stack);
  }
  if (self->files) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->files);
  }
}

Context*
Context_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Context);
}

static void
recursionGuard
  (
    Arcadia_Thread* thread,
    Context* context,
    Arcadia_FilePath* path
  )
{
  path = Arcadia_FilePath_getFullPath(thread, path);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)context->files); i < n; ++i) {
    Arcadia_FilePath* p = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueAt(thread, context->files, i);
    if (Arcadia_FilePath_isEqualTo(thread, p, path)) {
      Arcadia_String* ps = Arcadia_FilePath_toGeneric(thread, p);
      Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
      Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue(ps);
      Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"recursive include of file `");
      Arcadia_StringBuffer_insertBack(thread, sb, v);
      Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"`");
      fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  Arcadia_List_insertBackObjectReferenceValue(thread, context->files, path);
}

void
Context_onRun
  (
    Arcadia_Thread* thread,
    Context* self
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  while (!Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)self->stack)) {
    Arcadia_Value elementValue = Arcadia_Stack_peek(thread, self->stack);
    Arcadia_Stack_pop(thread, self->stack);
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_Value_getObjectReferenceValue(&elementValue);
    FileContext* fileContext = FileContext_create(thread, self, self->environment, filePath);
    Arcadia_ByteBuffer* sourceByteBuffer = NULL;
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      sourceByteBuffer = Arcadia_FileSystem_getFileContents(thread, fileSystem, fileContext->sourceFilePath);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_String* ps = Arcadia_FilePath_toGeneric(thread, filePath);
      Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
      Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ps);
      Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"failed to read file `");
      Arcadia_StringBuffer_insertBack(thread, sb, v);
      Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"`");
      fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
      Arcadia_Thread_jump(thread);
    }
    fileContext->source = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, sourceByteBuffer);
    recursionGuard(thread, self, filePath);
    FileContext_execute(thread, fileContext);
    Arcadia_List_removeAt(thread, self->files, Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->files) - 1, 1);
  }
}
