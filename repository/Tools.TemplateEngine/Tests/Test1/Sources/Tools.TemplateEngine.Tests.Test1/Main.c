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

// Last modified: 2024-09-04

#include <stdlib.h>
#include <string.h>
#include "R.h"

#include "Tools/TemplateEngine/FileContext.h"

static void
main1
  (
    int argc,
    char** argv
  )
{ 
  R_FileSystem* fileSystem = R_FileSystem_create();
  Context* context = Context_create();
  context->stack = R_Stack_create();
  context->targetBuffer = R_ByteBuffer_create();
  context->target = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->targetBuffer);
  context->temporaryBuffer = R_ByteBuffer_create();
  context->temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->temporaryBuffer);

  R_FilePath* filePath = R_FilePath_parseGeneric("HelloWorld.t", strlen("HelloWorld.t"));
  R_Value filePathValue;
  R_Value_setObjectReferenceValue(&filePathValue, filePath);
  R_Stack_push(context->stack, filePathValue);
  Context_onRun(context);

  R_FileSystem_setFileContents(fileSystem, R_FilePath_parseGeneric("HelloWorld.txt", strlen("HelloWorld.txt")), context->targetBuffer);
}

static void
recursiveInclude1
  (
    int argc,
    char** argv
  )
{
  Context* context = Context_create();
  context->stack = R_Stack_create();
  context->targetBuffer = R_ByteBuffer_create();
  context->target = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->targetBuffer);
  context->temporaryBuffer = R_ByteBuffer_create();
  context->temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->temporaryBuffer);

  R_FilePath* filePath = R_FilePath_parseGeneric("recursiveInclude1.t", strlen("recursiveInclude1.t"));
  R_Value filePathValue;
  R_Value_setObjectReferenceValue(&filePathValue, filePath);
  R_Stack_push(context->stack, filePathValue);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    Context_onRun(context);
    R_popJumpTarget();
    R_setStatus(R_Status_TestFailed);
    R_jump();
  } else {
    R_popJumpTarget();
    R_setStatus(R_Status_Success);
  }
}

static void
recursiveInclude2
  (
    int argc,
    char** argv
  )
{
  Context* context = Context_create();
  context->stack = R_Stack_create();
  context->targetBuffer = R_ByteBuffer_create();
  context->target = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->targetBuffer);
  context->temporaryBuffer = R_ByteBuffer_create();
  context->temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context->temporaryBuffer);

  R_FilePath* filePath = R_FilePath_parseGeneric("recursiveInclude2.t", strlen("recursiveInclude2.t"));
  R_Value filePathValue;
  R_Value_setObjectReferenceValue(&filePathValue, filePath);
  R_Stack_push(context->stack, filePathValue);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    Context_onRun(context);
    R_popJumpTarget();
    R_setStatus(R_Status_TestFailed);
    R_jump();
  } else {
    R_popJumpTarget();
    R_setStatus(R_Status_Success);
  }
}

int 
main
  (
    int argc,
    char** argv
  )
{
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(argc, argv);
    recursiveInclude1(argc, argv);
    recursiveInclude2(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
