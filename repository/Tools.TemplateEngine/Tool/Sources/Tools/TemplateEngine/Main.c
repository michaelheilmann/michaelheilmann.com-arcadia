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

// Last modified: 2024-09-08

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "Tools/TemplateEngine/FileContext.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  if (argc < 3) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  R_FileSystem* fileSystem = R_FileSystem_create(process);
  Context* context = Context_create(process);
  context->stack = R_Stack_create(process);
  context->targetBuffer = R_ByteBuffer_create(process);
  context->target = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, context->targetBuffer);
  context->temporaryBuffer = R_ByteBuffer_create(process);
  context->temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, context->temporaryBuffer);
  R_FilePath* filePath = R_FilePath_parseNative(process, argv[1], strlen(argv[1]));
  R_Value filePathValue;
  R_Value_setObjectReferenceValue(&filePathValue, filePath);
  R_Stack_push(process, context->stack, filePathValue);
  Context_onRun(process, context);
  R_FileSystem_setFileContents(process, fileSystem, R_FilePath_parseNative(process, argv[2], strlen(argv[2])), context->targetBuffer);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  status[0] = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
