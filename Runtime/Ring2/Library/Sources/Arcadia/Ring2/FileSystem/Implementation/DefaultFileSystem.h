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

#if !defined(ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DEFAULTFILESYSTEM_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DEFAULTFILESYSTEM_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/FileSystem/FileSystem.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  
#endif

/// @code
/// class DefaultFileSystem {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DefaultFileSystem", Arcadia_DefaultFileSystem,
                          u8"Arcadia.FileSystem");

struct Arcadia_DefaultFileSystem {
  Arcadia_FileSystem _parent;

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem

  HANDLE stdin;
  HANDLE stdout;
  HANDLE stderr;

#endif

};

Arcadia_DefaultFileSystem*
Arcadia_DefaultFileSystem_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DEFAULTFILESYSTEM_H_INCLUDED
