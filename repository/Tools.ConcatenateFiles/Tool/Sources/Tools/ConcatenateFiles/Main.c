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

// Last modified: 2024-08-31

#include "R.h"

#include <string.h>
#include <stdlib.h>

static void
main1
  (
    int argc,
    char** argv
  )
{
  if (argc < 3) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_FileSystem* fileSystem = R_FileSystem_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_FileHandle* fileHandle = R_FileHandle_create(fileSystem);
  for (int argi = 1; argi < argc - 1; ++argi) {
    R_FileHandle_openForReading(fileHandle, R_FilePath_parseNative(argv[argi], strlen(argv[argi])));
    char bytes[5012];
    R_SizeValue bytesToRead = 5012;
    R_SizeValue bytesRead = 0;
    do {
      R_FileHandle_read(fileHandle, bytes, bytesToRead, &bytesRead);
      R_ByteBuffer_append_pn(byteBuffer, bytes, bytesRead);
    } while (bytesRead > 0);
    R_FileHandle_close(fileHandle);
  }
  R_FileHandle_openForWriting(fileHandle, R_FilePath_parseNative(argv[argc - 1], strlen(argv[argc - 1])));
  R_SizeValue bytesWritten;
  R_FileHandle_write(fileHandle, byteBuffer->p, byteBuffer->sz, &bytesWritten);
  R_FileHandle_close(fileHandle);
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
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
