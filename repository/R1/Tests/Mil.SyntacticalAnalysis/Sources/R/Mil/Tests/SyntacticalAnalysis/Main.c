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

// Last modified: 2024-10-18

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R/Mil/Include.h"

static void
onTest
  (
    R_FilePath* sourceFilePath
  )
{
  R_FileSystem* fileSystem = R_FileSystem_create();
  R_FilePath* absoluteSourceFilePath = NULL;
  if (R_FilePath_isRelative(sourceFilePath)) {
    absoluteSourceFilePath = R_FileSystem_getWorkingDirectory(fileSystem);
    R_FilePath_append(absoluteSourceFilePath, sourceFilePath);
  } else {
    absoluteSourceFilePath = sourceFilePath;
  }
  R_ByteBuffer* sourceFileContents = R_FileSystem_getFileContents(fileSystem, absoluteSourceFilePath);
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8ByteBufferReader_create(sourceFileContents));
  R_Mil_Parser_run(parser);
}

void
main1
  (
    int argc,
    char** argv
  )
{
  onTest(R_FilePath_parseGeneric("Assets/Procedures.mil", sizeof("Assets/Procedures.mil") - 1));
  onTest(R_FilePath_parseGeneric("Assets/Classes.mil", sizeof("Assets/Classes.mil") - 1));
  onTest(R_FilePath_parseGeneric("Assets/Statements.mil", sizeof("Assets/Statements.mil") - 1));
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
