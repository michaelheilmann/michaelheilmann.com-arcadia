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

#if !defined(ARCADIA_RING2_FILESYSTEM_DEFAULTFILEHANDLE_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_DEFAULTFILEHANDLE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/FileSystem/FileHandle.h"
typedef struct Arcadia_FilePath Arcadia_FilePath;
typedef struct Arcadia_FileSystem Arcadia_FileSystem;

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>

#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux || \
      Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Cygwin

  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <limits.h> // SSIZE_MAX
  #include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

#else

  #error("environment not (yet) supported")

#endif

Arcadia_declareObjectType(u8"Arcadia.DefaultFileHandle", Arcadia_DefaultFileHandle,
                          u8"Arcadia.FileHandle");

struct Arcadia_DefaultFileHandle {
  Arcadia_FileHandle _parent;
  Arcadia_FileSystem* fileSystem;
  Arcadia_Natural8Value flags;

  #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

    HANDLE fd;

  #elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux || \
        Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Cygwin

    int fd;

  #else

    #error("environment not (yet) supported")

  #endif

};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_create
Arcadia_DefaultFileHandle*
Arcadia_DefaultFileHandle_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* fileSystem
  );

#endif // ARCADIA_RING2_FILESYSTEM_DEFAULTFILEHANDLE_H_INCLUDED
