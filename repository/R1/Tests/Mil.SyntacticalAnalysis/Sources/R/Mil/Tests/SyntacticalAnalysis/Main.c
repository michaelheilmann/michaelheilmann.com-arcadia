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

// Last modified: 2024-10-18

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R/Mil/Include.h"

static void
onTest
  (
    Arcadia_Process* process,
    R_FilePath* sourceFilePath
  )
{
  R_FileSystem* fileSystem = R_FileSystem_create(process);
  R_FilePath* absoluteSourceFilePath = NULL;
  if (R_FilePath_isRelative(sourceFilePath)) {
    absoluteSourceFilePath = R_FileSystem_getWorkingDirectory(process, fileSystem);
    R_FilePath_append(process, absoluteSourceFilePath, sourceFilePath);
  } else {
    absoluteSourceFilePath = sourceFilePath;
  }
  R_ByteBuffer* sourceFileContents = R_FileSystem_getFileContents(process, fileSystem, absoluteSourceFilePath);
  R_Mil_Parser* parser = R_Mil_Parser_create(process);
  R_Mil_Parser_setInput(process, parser, (R_Utf8Reader*)R_Utf8ByteBufferReader_create(process, sourceFileContents));
  R_Mil_Parser_run(process, parser);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  onTest(process, R_FilePath_parseGeneric(process, u8"Assets/Procedures.mil", sizeof(u8"Assets/Procedures.mil") - 1));
  onTest(process, R_FilePath_parseGeneric(process, u8"Assets/Classes.mil", sizeof(u8"Assets/Classes.mil") - 1));
  onTest(process, R_FilePath_parseGeneric(process, u8"Assets/Statements.mil", sizeof(u8"Assets/Statements.mil") - 1));
  onTest(process, R_FilePath_parseGeneric(process, u8"Assets/Variables.mil", sizeof(u8"Assets/Variables.mil") - 1));
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
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
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
