// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>

static void
main1
  (
    Arcadia_Process* process,
    int argi,
    const char *argv[]
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_UTF8Writer* writer = (Arcadia_UTF8Writer*)Arcadia_UTF8FileHandleWriter_create(thread, fileHandle);

#define Emit(String) \
  Arcadia_UTF8Writer_writeString \
    ( \
      thread, \
      writer, \
      Arcadia_String_create \
        ( \
          thread, \
          Arcadia_Value_makeImmutableUtf8StringValue \
            ( \
              Arcadia_ImmutableUtf8String_create \
                ( \
                  thread, \
                  String, \
                  sizeof(String) - 1 \
                ) \
            ) \
        ) \
    );

  // Test some escape sequences according to VT102, ECMA - 48, ISO / IEC 6429, ANSI X3.64.
  // `\033[38;2;<red>;<green>;<blue>;m` where <red>, <green>, <blue> are a integer literal within the range of [0,255] without signs or leading zeroes.
  // Sets the RGB color of the foreground.
  Emit(u8"\033[38;2;255;255;255m");
  Emit(u8"this is white\n");
  Emit(u8"\033[38;2;255;0;0m");
  Emit(u8"this is red\n");

#undef Emit
}

int
main
  (
    int argc,
    char **argv
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
