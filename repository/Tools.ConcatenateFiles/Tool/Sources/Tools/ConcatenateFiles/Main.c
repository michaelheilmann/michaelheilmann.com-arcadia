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

#include "R.h"

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
  if (argc < 3) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  R_FileSystem* fileSystem = R_FileSystem_create(process);
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create(process);
  R_FileHandle* fileHandle = R_FileHandle_create(process, fileSystem);
  for (int argi = 1; argi < argc - 1; ++argi) {
    R_FileHandle_openForReading(process, fileHandle, R_FilePath_parseNative(process, argv[argi], strlen(argv[argi])));
    char bytes[5012];
    Arcadia_SizeValue bytesToRead = 5012;
    Arcadia_SizeValue bytesRead = 0;
    do {
      R_FileHandle_read(process, fileHandle, bytes, bytesToRead, &bytesRead);
      R_ByteBuffer_append_pn(process, byteBuffer, bytes, bytesRead);
    } while (bytesRead > 0);
    R_FileHandle_close(fileHandle);
  }
  R_FileHandle_openForWriting(process, fileHandle, R_FilePath_parseNative(process, argv[argc - 1], strlen(argv[argc - 1])));
  Arcadia_SizeValue bytesWritten;
  R_FileHandle_write(process, fileHandle, byteBuffer->p, byteBuffer->sz, &bytesWritten);
  R_FileHandle_close(fileHandle);
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
