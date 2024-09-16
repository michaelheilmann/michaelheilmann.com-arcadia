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
Context_finalize
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
  R_Object_visit(self->target);
  R_Object_visit(self->temporary);
  R_Object_visit(self->stack);
  R_Object_visit(self->files);
}

void
Context_registerType
  (
  )
{
  R_registerObjectType("Tools.TemplateEngine.Context", sizeof("Tools.TemplateEngine.Context") - 1, sizeof(Context), NULL, &Context_visit, &Context_finalize);
}

Context*
Context_create
  (
  )
{
  Context* self = R_allocateObject(R_getObjectType("Tools.TemplateEngine.Context", sizeof("Tools.TemplateEngine.Context") - 1));
  self->target = NULL;
  self->stack = NULL;
  self->temporary = NULL;
  self->files = R_List_create();
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
    fileContext->source = R_Utf8Reader_create(sourceByteBuffer);
    recursionGuard(context, filePath);
    FileContext_execute(fileContext);
    R_List_remove(context->files, R_List_getSize(context->files) - 1, 1);
  }
}
