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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Implementation/Configure.h"
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
typedef struct Arcadia_FilePath Arcadia_FilePath;

/// @code
/// class FileSystem {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.FileSystem", Arcadia_FileSystem, u8"Arcadia.Object");

struct Arcadia_FileSystem {
  Arcadia_Object _parent;
};

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_create
Arcadia_FileSystem*
Arcadia_FileSystem_create
  (
    Arcadia_Thread* thread
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_getFileContents
Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_setFileContents
void
Arcadia_FileSystem_setFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path,
    Arcadia_ByteBuffer * contents
  );

void
Arcadia_FileSystem_createDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_regularFileExists
Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_directoryFileExists
Arcadia_BooleanValue
Arcadia_FileSystem_directoryFileExists
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

Arcadia_FilePath*
Arcadia_FileSystem_getWorkingDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_H_INCLUDED
