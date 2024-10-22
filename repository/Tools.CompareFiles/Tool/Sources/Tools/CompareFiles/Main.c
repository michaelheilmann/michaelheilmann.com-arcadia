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

static R_BooleanValue
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
  R_FilePath* firstFile = R_FilePath_parseNative(argv[1], strlen(argv[1]));
  R_FilePath* secondFile = R_FilePath_parseNative(argv[2], strlen(argv[2]));
  R_FileSystem* fileSystem = R_FileSystem_create();
  if (!R_FileSystem_regularFileExists(fileSystem, firstFile)) {
    R_setStatus(R_Status_NotExists);
    R_jump();
  }
  if (!R_FileSystem_regularFileExists(fileSystem, secondFile)) {
    R_setStatus(R_Status_NotExists);
    R_jump();
  }
  R_ByteBuffer* firstByteBuffer = R_FileSystem_getFileContents(fileSystem, firstFile);
  R_ByteBuffer* secondByteBuffer = R_FileSystem_getFileContents(fileSystem, secondFile);
  return R_ByteBuffer_isEqualTo(firstByteBuffer, secondByteBuffer);
}

int
main
  (
    int argc,
    char** argv
  )
{
  R_BooleanValue areEqual = R_BooleanValue_False;
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    areEqual = main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return areEqual ? EXIT_SUCCESS : EXIT_FAILURE;
}
