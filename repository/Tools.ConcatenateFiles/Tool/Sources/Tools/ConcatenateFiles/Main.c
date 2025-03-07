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

static void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  if (argc < 3) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, fileSystem);
  for (int argi = 1; argi < argc - 1; ++argi) {
    Arcadia_FileHandle_openForReading(thread, fileHandle, Arcadia_FilePath_parseNative(thread, argv[argi], strlen(argv[argi])));
    char bytes[5012];
    Arcadia_SizeValue bytesToRead = 5012;
    Arcadia_SizeValue bytesRead = 0;
    do {
      Arcadia_FileHandle_read(thread, fileHandle, bytes, bytesToRead, &bytesRead);
      Arcadia_ByteBuffer_append_pn(thread, byteBuffer, bytes, bytesRead);
    } while (bytesRead > 0);
    Arcadia_FileHandle_close(thread, fileHandle);
  }
  Arcadia_FileHandle_openForWriting(thread, fileHandle, Arcadia_FilePath_parseNative(thread, argv[argc - 1], strlen(argv[argc - 1])));
  Arcadia_SizeValue bytesWritten;
  Arcadia_FileHandle_write(thread, fileHandle, byteBuffer->p, byteBuffer->sz, &bytesWritten);
  Arcadia_FileHandle_close(thread, fileHandle);
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
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  Arcadia_Status status = Arcadia_Thread_getStatus(Arcadia_Process_getThread(process));
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
