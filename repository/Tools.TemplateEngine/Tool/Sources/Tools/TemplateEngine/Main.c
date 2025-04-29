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

// Last modified: 2024-09-08

#include <stdlib.h>
#include <string.h>
#include "R/Include.h"
#include "Tools/TemplateEngine/FileContext.h"

void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  if (argc < 3) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
  Context* context = Context_create(thread);
  context->stack = Arcadia_Stack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context->temporaryBuffer);
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(thread, argv[1], strlen(argv[1]));
  Arcadia_Value filePathValue;
  Arcadia_Value_setObjectReferenceValue(&filePathValue, filePath);
  Arcadia_Stack_push(thread, context->stack, filePathValue);
  Context_onRun(thread, context);
  Arcadia_FileSystem_setFileContents(thread, fileSystem, Arcadia_FilePath_parseNative(thread, argv[2], strlen(argv[2])), context->targetBuffer);
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(thread, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  Arcadia_Status status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
