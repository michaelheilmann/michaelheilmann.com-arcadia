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

// Last modified: 2024-09-04

#include <stdlib.h>
#include <string.h>
#include "R/Include.h"

#include "Tools/TemplateEngine/FileContext.h"

static void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{ 
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(process);
  Context* context = Context_create(process);
  context->stack = Arcadia_Stack_create(process);
  context->targetBuffer = Arcadia_ByteBuffer_create(process);
  context->target = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context->temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->temporaryBuffer);

  Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(process, u8"HelloWorld.t", strlen(u8"HelloWorld.t"));
  Arcadia_Value filePathValue;
  Arcadia_Value_setObjectReferenceValue(&filePathValue, filePath);
  Arcadia_Stack_push(process, context->stack, filePathValue);
  Context_onRun(process, context);

  Arcadia_FileSystem_setFileContents(process, fileSystem, Arcadia_FilePath_parseGeneric(process, u8"HelloWorld.txt", strlen(u8"HelloWorld.txt")), context->targetBuffer);
}

static void
recursiveInclude1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Context* context = Context_create(process);
  context->stack = Arcadia_Stack_create(process);
  context->targetBuffer = Arcadia_ByteBuffer_create(process);
  context->target = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context->temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->temporaryBuffer);

  Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(process, u8"recursiveInclude1.t", strlen(u8"recursiveInclude1.t"));
  Arcadia_Value filePathValue;
  Arcadia_Value_setObjectReferenceValue(&filePathValue, filePath);
  Arcadia_Stack_push(process, context->stack, filePathValue);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(process, context);
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_setStatus(process, Arcadia_Status_Success);
  }
}

static void
recursiveInclude2
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Context* context = Context_create(process);
  context->stack = Arcadia_Stack_create(process);
  context->targetBuffer = Arcadia_ByteBuffer_create(process);
  context->target = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context->temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context->temporaryBuffer);

  Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(process, u8"recursiveInclude2.t", strlen(u8"recursiveInclude2.t"));
  Arcadia_Value filePathValue;
  Arcadia_Value_setObjectReferenceValue(&filePathValue, filePath);
  Arcadia_Stack_push(process, context->stack, filePathValue);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(process, context);
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_setStatus(process, Arcadia_Status_Success);
  }
}

int 
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
    recursiveInclude1(process, argc, argv);
    recursiveInclude2(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
