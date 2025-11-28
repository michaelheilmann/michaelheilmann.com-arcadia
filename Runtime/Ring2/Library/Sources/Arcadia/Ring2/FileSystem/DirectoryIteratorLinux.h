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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATORLINUX_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATORLINUX_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/FileSystem/DirectoryIterator.h"

#if (Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Macos)
	#include <sys/types.h>
	#include <sys/dir.h>
#else
	#include <dirent.h>
#endif

Arcadia_declareObjectType(u8"Arcadia.DirectoryIteratorLinux", Arcadia_DirectoryIteratorLinux,
                          u8"Arcadia.DirectoryIterator");

struct Arcadia_DirectoryIteratorLinux {
  Arcadia_DirectoryIterator _parent;
  DIR *dir;
  struct dirent *dirent;
};

Arcadia_DirectoryIteratorLinux*
Arcadia_DirectoryIteratorLinux_create
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* path
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATORLINUX_H_INCLUDED
