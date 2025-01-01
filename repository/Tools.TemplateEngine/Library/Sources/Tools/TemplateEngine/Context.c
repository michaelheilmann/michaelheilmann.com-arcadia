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
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
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

static const R_ObjectType_Operations _objectTypeOperations = {
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

Rex_defineObjectType(u8"Tools.TemplateEngine.Context", Context, u8"R.Object", R_Object, &_typeOperations);

void
Context_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  Context* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Context_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->targetBuffer = NULL;
  _self->target = NULL;
  _self->temporaryBuffer = NULL;
  _self->temporary = NULL;
  _self->stack = NULL;
  _self->files = R_List_create(process);
  R_Object_setType((R_Object*)_self, _type);
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
  R_Object_visit(self->targetBuffer);
  R_Object_visit(self->target);

  R_Object_visit(self->temporaryBuffer);
  R_Object_visit(self->temporary);

  R_Object_visit(self->stack);
  R_Object_visit(self->files);
}

Context*
Context_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Context* self = R_allocateObject(process, _Context_getType(process), 0, &argumentValues[0]);
  return self;
}

static void
recursionGuard
  (
    Arcadia_Process* process,
    Context* context,
    R_FilePath* path
  )
{
  path = R_FilePath_getFullPath(process, path);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(context->files); i < n; ++i) {
    R_FilePath* p = (R_FilePath*)R_List_getObjectReferenceValueAt(process, context->files, i);
    if (R_FilePath_isEqualTo(process, p, path)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
  }
  R_List_appendObjectReferenceValue(process, context->files, path);
}

void
Context_onRun
  (
    Arcadia_Process* process,
    Context* context
  )
{
  R_FileSystem* fileSystem = R_FileSystem_create(process);
  while (!R_Stack_isEmpty(context->stack)) {
    R_Value elementValue = R_Stack_peek(process, context->stack);
    R_Stack_pop(process, context->stack);
    R_FilePath* filePath = (R_FilePath*)R_Value_getObjectReferenceValue(&elementValue);
    FileContext* fileContext = FileContext_create(process, context, filePath);
    R_ByteBuffer* sourceByteBuffer = R_FileSystem_getFileContents(process, fileSystem, fileContext->sourceFilePath);
    fileContext->source = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(process, sourceByteBuffer);
    recursionGuard(process, context, filePath);
    FileContext_execute(process, fileContext);
    R_List_remove(process, context->files, R_List_getSize(context->files) - 1, 1);
  }
}
