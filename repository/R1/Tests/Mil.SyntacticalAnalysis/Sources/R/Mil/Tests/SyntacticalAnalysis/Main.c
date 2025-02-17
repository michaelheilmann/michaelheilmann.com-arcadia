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
#include "R/Include.h"
#include "R/Mil/Include.h"

static void
onTest
  (
    Arcadia_Process* process,
    Arcadia_FilePath* sourceFilePath
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(process);
  Arcadia_FilePath* absoluteSourceFilePath = NULL;
  if (Arcadia_FilePath_isRelative(sourceFilePath)) {
    absoluteSourceFilePath = Arcadia_FileSystem_getWorkingDirectory(process, fileSystem);
    Arcadia_FilePath_append(process, absoluteSourceFilePath, sourceFilePath);
  } else {
    absoluteSourceFilePath = sourceFilePath;
  }
  Arcadia_ByteBuffer* sourceFileContents = Arcadia_FileSystem_getFileContents(process, fileSystem, absoluteSourceFilePath);
  Arcadia_Mil_Parser* parser = Arcadia_Mil_Parser_create(process);
  Arcadia_Mil_Parser_setInput(process, parser, (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, sourceFileContents));
  Arcadia_Mil_Parser_run(process, parser);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  onTest(process, Arcadia_FilePath_parseGeneric(process, u8"Assets/Procedures.mil", sizeof(u8"Assets/Procedures.mil") - 1));
  onTest(process, Arcadia_FilePath_parseGeneric(process, u8"Assets/Classes.mil", sizeof(u8"Assets/Classes.mil") - 1));
  onTest(process, Arcadia_FilePath_parseGeneric(process, u8"Assets/Statements.mil", sizeof(u8"Assets/Statements.mil") - 1));
  onTest(process, Arcadia_FilePath_parseGeneric(process, u8"Assets/Variables.mil", sizeof(u8"Assets/Variables.mil") - 1));
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
