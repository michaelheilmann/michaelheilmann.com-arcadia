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

// Last modified: 2024-09-01

#if !defined(R_FILESYSTEM_H_INCLUDED)
#define R_FILESYSTEM_H_INCLUDED

#include "R/Configure.h"
#include "Arcadia/Ring1/Include.h"
#include "R/ByteBuffer.h"
typedef struct R_FileHandle R_FileHandle;
typedef struct R_FilePath R_FilePath;

/// @code
/// class FileSystem {
///   constructor()
/// }
/// @endcode
Rex_declareObjectType(u8"Arcadia.Library.FileSystem", R_FileSystem, u8"Arcadia.Object");

struct R_FileSystem {
  Arcadia_Object _parent;
};

// https://michaelheilmann.com/repository/R1/#r-filesystem-create
R_FileSystem*
R_FileSystem_create
  (
    Arcadia_Process* process
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-getfilecontents
R_ByteBuffer*
R_FileSystem_getFileContents
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-setfilecontents
void
R_FileSystem_setFileContents
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path,
    R_ByteBuffer * contents
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-createdirectory
void
R_FileSystem_createDirectory
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  );

Arcadia_BooleanValue
R_FileSystem_regularFileExists
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  );

Arcadia_BooleanValue
R_FileSystem_directoryFileExists
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  );

R_FilePath*
R_FileSystem_getWorkingDirectory
  (
    Arcadia_Process* process,
    R_FileSystem* self
  );

#endif // R_FILESYSTEM_H_INCLUDED
