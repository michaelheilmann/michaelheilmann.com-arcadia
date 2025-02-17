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

// Last modified: 2024-08-31

#include "R/Include.h"

#include <string.h>
#include <stdlib.h>

static Arcadia_BooleanValue
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
  Arcadia_FilePath* firstFile = Arcadia_FilePath_parseNative(process, argv[1], strlen(argv[1]));
  Arcadia_FilePath* secondFile = Arcadia_FilePath_parseNative(process, argv[2], strlen(argv[2]));
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(process);
  if (!Arcadia_FileSystem_regularFileExists(process, fileSystem, firstFile)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NotExists);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_FileSystem_regularFileExists(process, fileSystem, secondFile)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NotExists);
    Arcadia_Process_jump(process);
  }
  Arcadia_ByteBuffer* firstByteBuffer = Arcadia_FileSystem_getFileContents(process, fileSystem, firstFile);
  Arcadia_ByteBuffer* secondByteBuffer = Arcadia_FileSystem_getFileContents(process, fileSystem, secondFile);
  return Arcadia_ByteBuffer_isEqualTo(process, firstByteBuffer, secondByteBuffer);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_BooleanValue areEqual = Arcadia_BooleanValue_False;
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    areEqual = main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return areEqual ? EXIT_SUCCESS : EXIT_FAILURE;
}
