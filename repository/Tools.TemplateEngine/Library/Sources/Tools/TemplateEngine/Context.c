// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
Context_destruct
  (
    Context* self
  )
{/*Intentionally empty.*/}

static void
Context_visit
  (
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

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &Context_destruct,
  .visit = &Context_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("Tools.TemplateEngine.Context", Context, "R.Object", R_Object, &_typeOperations);

void
Context_construct
  (
    Context* self
  )
{
  R_Type* _type = _Context_getType();
  R_Object_construct((R_Object*)self);
  self->targetBuffer = NULL;
  self->target = NULL;
  self->temporaryBuffer = NULL;
  self->temporary = NULL;
  self->stack = NULL;
  self->files = R_List_create();
  R_Object_setType((R_Object*)self, _type);
}

Context*
Context_create
  (
  )
{
  Context* self = R_allocateObject(_Context_getType());
  Context_construct(self);
  return self;
}

static void recursionGuard(Context* context, R_FilePath* path) {
  path = R_FilePath_getFullPath(path);
  for (R_SizeValue i = 0, n = R_List_getSize(context->files); i < n; ++i) {
    R_FilePath* p = (R_FilePath*)R_List_getObjectReferenceValueAt(context->files, i);
    if (R_FilePath_isEqualTo(p, path)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
  }
  R_List_appendObjectReferenceValue(context->files, path);
}

void
Context_onRun
  (
    Context* context
  )
{
  R_FileSystem* fileSystem = R_FileSystem_create();
  while (!R_Stack_isEmpty(context->stack)) {
    R_Value elementValue = R_Stack_peek(context->stack);
    R_Stack_pop(context->stack);
    R_FilePath* filePath = (R_FilePath*)R_Value_getObjectReferenceValue(&elementValue);
    FileContext* fileContext = FileContext_create(context, filePath);
    R_ByteBuffer* sourceByteBuffer = R_FileSystem_getFileContents(fileSystem, fileContext->sourceFilePath);
    fileContext->source = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(sourceByteBuffer);
    recursionGuard(context, filePath);
    FileContext_execute(fileContext);
    R_List_remove(context->files, R_List_getSize(context->files) - 1, 1);
  }
}
