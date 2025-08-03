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

#include "Arcadia/Mil/Frontend/Include.h"

static void
onTest
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* sourceFilePath
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FilePath* absoluteSourceFilePath = NULL;
  if (Arcadia_FilePath_isRelative(thread, sourceFilePath)) {
    absoluteSourceFilePath = Arcadia_FileSystem_getWorkingDirectory(thread, fileSystem);
    Arcadia_FilePath_append(thread, absoluteSourceFilePath, sourceFilePath);
  } else {
    absoluteSourceFilePath = sourceFilePath;
  }
  Arcadia_ByteBuffer* sourceFileContents = Arcadia_FileSystem_getFileContents(thread, fileSystem, absoluteSourceFilePath);
  Arcadia_Mil_Parser* parser = Arcadia_Mil_Parser_create(thread);
  Arcadia_Mil_Parser_setInput(thread, parser, (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, sourceFileContents));
  Arcadia_Mil_Parser_run(thread, parser);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  onTest(thread, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Procedures.mil", sizeof(u8"Assets/Procedures.mil") - 1));
  onTest(thread, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Classes.mil", sizeof(u8"Assets/Classes.mil") - 1));
  onTest(thread, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Statements.mil", sizeof(u8"Assets/Statements.mil") - 1));
  onTest(thread, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Variables.mil", sizeof(u8"Assets/Variables.mil") - 1));
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
    main1(process, argc, argv);
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
