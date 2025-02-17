// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-09

#include "Tools/TemplateEngine/Context.h"

#include "Tools/TemplateEngine/FileContext.h"

static void
Context_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );  

static void
Context_destruct
  (
    Arcadia_Process* process,
    Context* self
  );

static void
Context_visit
  (
    Arcadia_Process* process,
    Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Context_constructImpl,
  .destruct = &Context_destruct,
  .visit = &Context_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Tools.TemplateEngine.Context", Context, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

void
Context_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Context* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Context_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->targetBuffer = NULL;
  _self->target = NULL;
  _self->temporaryBuffer = NULL;
  _self->temporary = NULL;
  _self->stack = NULL;
  _self->files = Arcadia_List_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Context_destruct
  (
    Arcadia_Process* process,
    Context* self
  )
{/*Intentionally empty.*/}

static void
Context_visit
  (
    Arcadia_Process* process,
    Context* self
  )
{
  Arcadia_Object_visit(process, self->targetBuffer);
  Arcadia_Object_visit(process, self->target);

  Arcadia_Object_visit(process, self->temporaryBuffer);
  Arcadia_Object_visit(process, self->temporary);

  Arcadia_Object_visit(process, self->stack);
  Arcadia_Object_visit(process, self->files);
}

Context*
Context_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Context* self = R_allocateObject(process, _Context_getType(process), 0, &argumentValues[0]);
  return self;
}

static void
recursionGuard
  (
    Arcadia_Process* process,
    Context* context,
    Arcadia_FilePath* path
  )
{
  path = Arcadia_FilePath_getFullPath(process, path);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, context->files); i < n; ++i) {
    Arcadia_FilePath* p = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueAt(process, context->files, i);
    if (Arcadia_FilePath_isEqualTo(process, p, path)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
  }
  Arcadia_List_appendObjectReferenceValue(process, context->files, path);
}

void
Context_onRun
  (
    Arcadia_Process* process,
    Context* context
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(process);
  while (!Arcadia_Stack_isEmpty(context->stack)) {
    Arcadia_Value elementValue = Arcadia_Stack_peek(process, context->stack);
    Arcadia_Stack_pop(process, context->stack);
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_Value_getObjectReferenceValue(&elementValue);
    FileContext* fileContext = FileContext_create(process, context, filePath);
    Arcadia_ByteBuffer* sourceByteBuffer = Arcadia_FileSystem_getFileContents(process, fileSystem, fileContext->sourceFilePath);
    fileContext->source = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, sourceByteBuffer);
    recursionGuard(process, context, filePath);
    FileContext_execute(process, fileContext);
    Arcadia_List_remove(process, context->files, Arcadia_List_getSize(process, context->files) - 1, 1);
  }
}
