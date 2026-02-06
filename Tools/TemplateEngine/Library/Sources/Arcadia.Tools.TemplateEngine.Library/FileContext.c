// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia.Tools.TemplateEngine.Library/FileContext.h"

#include <stdio.h> // @todo Remove references to `stdio.h`.

#include "Arcadia.Tools.TemplateEngine.Library/Directives/Parser.h"
#include "Arcadia.Tools.TemplateEngine.Library/Directives/Tree.h"
#include "Arcadia.Tools.TemplateEngine.Library/Context.h"
#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    FileContext* context,
    uint32_t expectedCodePoint
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = Arcadia_UTF8Reader_getCodePoint(thread, context->reader);
  return expectedCodePoint == currentCodePoint;
}

static void
evalInvoke
  (
    Arcadia_Thread* thread,
    FileContext* context,
    Directives_Tree* ast
  )
{
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ast->invoke.name);
  Arcadia_Value v = Environment_get(thread, context->environment, k, Arcadia_BooleanValue_True);
  if (Arcadia_Value_isVoidValue(&v)) {
    // Error.
    Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
    Arcadia_StringBuffer_insertBack(thread, sb, k);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` not defined\n");

    Arcadia_Log_error(thread, context->context->consoleLog, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(sb)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Value_isForeignProcedureValue(&v)) {
    // Error.
    Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
    Arcadia_StringBuffer_insertBack(thread, sb, k);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of procedure string\n");

    Arcadia_Log_error(thread, context->context->consoleLog, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(sb)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ForeignProcedure* p = Arcadia_Value_getForeignProcedureValue(&v);
  Arcadia_Value targetValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);

  Arcadia_SizeValue oldStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_SizeValue numberOfValues = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)ast->invoke.arguments);
  if (numberOfValues > Arcadia_Natural8Value_Maximum - 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0, n = numberOfValues; i < n; ++i) {
    Arcadia_Value temporary = Arcadia_List_getAt(thread, ast->invoke.arguments, i);
    Arcadia_ValueStack_pushValue(thread, &temporary);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, numberOfValues);
  (*p)(thread);
  if (oldStackSize > Arcadia_ValueStack_getSize(thread) || (Arcadia_ValueStack_getSize(thread) - oldStackSize) != 1) {
    Arcadia_ValueStack_popValues(thread, Arcadia_ValueStack_getSize(thread) - oldStackSize);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  targetValue = Arcadia_ValueStack_getValue(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1);


  Arcadia_String* string = NULL;
  if (Arcadia_Value_isInteger16Value(&targetValue)) {
    string = Arcadia_String_createFromInteger16(thread, Arcadia_Value_getInteger16Value(&targetValue));
  } else if (Arcadia_Value_isInteger32Value(&targetValue)) {
    string = Arcadia_String_createFromInteger32(thread, Arcadia_Value_getInteger32Value(&targetValue));
  } else if (Arcadia_Value_isInteger64Value(&targetValue)) {
    string = Arcadia_String_createFromInteger64(thread, Arcadia_Value_getInteger64Value(&targetValue));
  } else if (Arcadia_Value_isInteger8Value(&targetValue)) {
    string = Arcadia_String_createFromInteger8(thread, Arcadia_Value_getInteger8Value(&targetValue));
  } else  if (Arcadia_Value_isObjectReferenceValue(&targetValue)) {
    Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&targetValue);
    if (!Arcadia_Type_isDescendantType(thread, Arcadia_Object_getType(thread, object), _Arcadia_String_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    string = (Arcadia_String*)object;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ByteBuffer_insertBackBytes(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));

}

static void
evalAst
  (
    Arcadia_Thread* thread,
    FileContext* context,
    Directives_Tree* ast
  )
{
  switch (ast->type) {
    case Directives_TreeKind_At: {
      Arcadia_Natural32Value targetCodePoint = '@';
      Arcadia_UTF8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
    } break;
    case Directives_TreeKind_GetVariable: {
      Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ast->getVariable.name);
      Arcadia_Value v = Environment_get(thread, context->environment, k, Arcadia_BooleanValue_True);
      if (Arcadia_Value_isVoidValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` not defined\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } else  if (!Arcadia_Value_isObjectReferenceValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of type string\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&v);
      if (!Arcadia_Type_isDescendantType(thread, Arcadia_Object_getType(thread, object), _Arcadia_String_getType(thread))) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of type string\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_ByteBuffer_insertBackBytes(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, (Arcadia_String*)object), Arcadia_String_getNumberOfBytes(thread, (Arcadia_String*)object));
    } break;
    case Directives_TreeKind_Invoke: {
      if (Arcadia_String_isEqualTo_pn(thread, ast->invoke.name, u8"include", sizeof(u8"include") - 1)) {
        if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)ast->invoke.arguments)) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        }
        Arcadia_Object* object = Arcadia_List_getObjectReferenceValueAt(thread, ast->invoke.arguments, 0);
        if (!Arcadia_Object_isInstanceOf(thread, object, _Arcadia_String_getType(thread))) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
          Arcadia_Thread_jump(thread);
        }
        Arcadia_String* string = (Arcadia_String*)object;
        Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
        Arcadia_Value value;
        Arcadia_Value_setObjectReferenceValue(&value, filePath);
        Arcadia_Stack_push(thread, context->context->stack, value);
        Context_onRunInner(thread, context->context, context->includedFilePath);
      } else {
        evalInvoke(thread, context, ast);
      }
    } break;
    case Directives_TreeKind_String: {
      Arcadia_UTF8Writer_writeString(thread, context->context->target, ast->string);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static Directives_Tree*
parseDirective
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return Directives_Parser_run(thread, context->parser);
}

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    FileContextDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&FileContext_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&FileContext_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&FileContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.FileContext", FileContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{/*Intentionally empty.*/}

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{
  if (self->context) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  }
  if (self->includedFilePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->includedFilePath);
  }
  if (self->reader) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->reader);
  }
  if (self->environment) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->environment);
  }
  if (self->includingFilePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->includingFilePath);
  }
  if (self->parser) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parser);
  }
}

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{
  Arcadia_TypeValue _type = _FileContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (4 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->context = (Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Context_getType(thread));
  self->environment = (Environment*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Environment_getType(thread));

  self->includingFilePath = (Arcadia_FilePath*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_FilePath_getType(thread));;
  self->includedFilePath = (Arcadia_FilePath*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread));

  self->reader = NULL;

  self->parser = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
FileContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    FileContextDispatch* self
  )
{ }

FileContext*
FileContext_create
  (
    Arcadia_Thread* thread,
    Context* context,
    Environment* environment,
    Arcadia_FilePath* includingFilePath,
    Arcadia_FilePath* includedFilePath
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)context);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)environment);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)includingFilePath);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)includedFilePath);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(FileContext);
}

void
FileContext_execute
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_ByteBuffer* sourceByteBuffer = NULL;

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    sourceByteBuffer = Arcadia_FileSystem_getFileContents(thread, fileSystem, context->includedFilePath);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    Arcadia_String* ps = Arcadia_FilePath_toGeneric(thread, context->includedFilePath);
    Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
    Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ps);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"failed to read file `");
    Arcadia_StringBuffer_insertBack(thread, sb, v);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"`\n");

    Arcadia_Log_error(thread, context->context->consoleLog, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(sb)));

    Arcadia_Thread_jump(thread);
  }

  context->reader = (Arcadia_UTF8Reader*)Arcadia_UTF8ByteBufferReader_create(thread, sourceByteBuffer);
  if (!context->parser) {
    context->parser = Directives_Parser_create(thread, Arcadia_FilePath_toGeneric(thread, context->includedFilePath), 0, context->reader);
  }

  while (Arcadia_UTF8Reader_hasCodePoint(thread, context->reader)) {
    Arcadia_Natural32Value sourceCodePoint = Arcadia_UTF8Reader_getCodePoint(thread, context->reader);
    if (sourceCodePoint == '@') {
      Arcadia_UTF8Reader_next(thread, context->reader);
      Directives_Parser_setInput(thread, context->parser, Arcadia_FilePath_toGeneric(thread, context->includedFilePath), 1, context->reader);
      Directives_Tree* ast = parseDirective(thread, context);
      evalAst(thread, context, ast);
    } else {
      Arcadia_Natural32Value targetCodePoint = sourceCodePoint;
      Arcadia_UTF8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
      Arcadia_UTF8Reader_next(thread, context->reader);
    }
  }
}
