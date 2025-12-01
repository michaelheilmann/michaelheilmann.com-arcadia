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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // @todo Remove references to `stdio.h`.

// @todo Remove references to `stdio.h`.
static void
directoryIteratorTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_logf(Arcadia_LogFlags_Info, "directory iterator test 1\n");
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FilePath* filePath = Arcadia_FileSystem_getWorkingDirectory(thread, fileSystem);
  Arcadia_logf(Arcadia_LogFlags_Info, "  working directory: %s\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Directory1", sizeof(u8"Assets/Directory1") - 1));
  Arcadia_logf(Arcadia_LogFlags_Info, "  iterated directory: %s\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  if (Arcadia_FileSystem_directoryFileExists(thread, fileSystem, filePath)) {
    Arcadia_logf(Arcadia_LogFlags_Info, "  directory %s exists\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  }
  Arcadia_DirectoryIterator* directoryIterator = (Arcadia_DirectoryIterator*)Arcadia_FileSystem_createDirectoryIterator(thread, fileSystem, filePath);
  Arcadia_Integer8Value count = 0;
  while (Arcadia_DirectoryIterator_hasValue(thread, directoryIterator)) {
    Arcadia_FilePath* filePath = Arcadia_DirectoryIterator_getValue(thread, directoryIterator);
    Arcadia_Tests_assertTrue(thread, NULL != filePath);
    Arcadia_String* filePathString = Arcadia_FilePath_toGeneric(thread, filePath);
    Arcadia_Tests_assertTrue(thread, NULL != filePathString);
    Arcadia_DirectoryIterator_nextValue(thread, directoryIterator);
    count++;
  }
  Arcadia_Tests_assertTrue(thread, 3 == count);
}

// @todo Remove references to `stdio.h`.
static void
directoryIteratorTest2
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_logf(Arcadia_LogFlags_Info, "directory iterator test 2\n");
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FilePath* filePath = Arcadia_FileSystem_getWorkingDirectory(thread, fileSystem);
  Arcadia_logf(Arcadia_LogFlags_Info, "  working directory: %s\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Assets/Directory2", sizeof(u8"Assets/Directory2") - 1));
  Arcadia_logf(Arcadia_LogFlags_Info, "  iterated directory: %s\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  if (Arcadia_FileSystem_directoryFileExists(thread, fileSystem, filePath)) {
    Arcadia_logf(Arcadia_LogFlags_Info, "  directory %s exists\n", Arcadia_String_getBytes(thread, Arcadia_FilePath_toNative(thread, filePath)));
  }
  Arcadia_DirectoryIterator* directoryIterator = (Arcadia_DirectoryIterator*)Arcadia_FileSystem_createDirectoryIterator(thread, fileSystem, filePath);
  Arcadia_Integer8Value count = 0;
  while (Arcadia_DirectoryIterator_hasValue(thread, directoryIterator)) {
    Arcadia_FilePath* filePath = Arcadia_DirectoryIterator_getValue(thread, directoryIterator);
    Arcadia_Tests_assertTrue(thread, NULL != filePath);
    Arcadia_String* filePathString = Arcadia_FilePath_toGeneric(thread, filePath);
    Arcadia_Tests_assertTrue(thread, NULL != filePathString);
    Arcadia_DirectoryIterator_nextValue(thread, directoryIterator);
    count++;
  }
  Arcadia_Tests_assertTrue(thread, 4 == count);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&directoryIteratorTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&directoryIteratorTest2)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
