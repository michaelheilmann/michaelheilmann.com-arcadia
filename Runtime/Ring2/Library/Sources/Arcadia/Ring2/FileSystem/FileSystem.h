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

#if !defined(ARCADIA_RING2_FILESYSTEM_FILESYSTEM_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_FILESYSTEM_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/FileSystem/DirectoryIterator.h"
#include "Arcadia/Ring2/FileSystem/FileHandle.h"
#include "Arcadia/Ring2/FileSystem/FilePath.h"
#include "Arcadia/Ring2/FileSystem/FileType.h"

/// @code
/// class FileSystem {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.FileSystem", Arcadia_FileSystem,
                          u8"Arcadia.Object");

struct Arcadia_FileSystem {
  Arcadia_Object _parent;

  void
  (*createDirectoryFile)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_DirectoryIterator*
  (*createDirectoryIterator)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_FileHandle*
  (*createFileHandle)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self
    );

  void
  (*createRegularFile)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  void
  (*deleteDirectoryFile)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  void
  (*deleteFile)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  void
  (*deleteRegularFile)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_BooleanValue
  (*directoryFileExists)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_FilePath*
  (*getConfigurationDirectory)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self
    );

  Arcadia_FilePath*
  (*getExecutable)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self
    );

  Arcadia_ByteBuffer*
  (*getFileContents)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_FileType
  (*getFileType)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_Natural64Value
  (*getLastWriteTime)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  Arcadia_FilePath*
  (*getSaveDirectory)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self
    );

  Arcadia_FilePath*
  (*getWorkingDirectory)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self
    );

  Arcadia_BooleanValue
  (*regularFileExists)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path
    );

  void
  (*setFileContents)
    (
      Arcadia_Thread* thread,
      Arcadia_FileSystem* self,
      Arcadia_FilePath* path,
      Arcadia_ByteBuffer * contents
    );
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_createDirectoryFile
/// @brief Create a directory file.
/// @param thread A pointer to this thread.
/// @param self A pointer to this file system.
/// @param path A pointer to the path.
/// @error Arcadia_Status_NotFound
/// one or more intermediate directories do not exist; this function will only create the final directory in the path.
void
Arcadia_FileSystem_createDirectoryFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_createDirectoryIterator
Arcadia_DirectoryIterator*
Arcadia_FileSystem_createDirectoryIterator
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

Arcadia_FileHandle*
Arcadia_FileSystem_createFileHandle
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_createRegularFile
/// @brief Create a regular file.
/// @param thread A pointer to this thread.
/// @param self A pointer to this file system.
/// @param path A pointer to the path.
/// @error Arcadia_Status_NotFound
/// one or more intermediate directories do not exist; this function will only create the final directory in the path.
void
Arcadia_FileSystem_createRegularFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_deleteDirectoryFile
void
Arcadia_FileSystem_deleteDirectoryFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_deleteFile
void
Arcadia_FileSystem_deleteFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_deleteRegularFile
void
Arcadia_FileSystem_deleteRegularFile
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

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_getConfigurationDirectory
Arcadia_FilePath*
Arcadia_FileSystem_getConfigurationDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

/// @brief Get the path of the executing executable.
/// @param thread A pointer to this thread.
/// @param self A pointer to this file system.
/// @return A pointer to the executable path.
/// @success The caller acquired a reference to the string.
Arcadia_FilePath*
Arcadia_FileSystem_getExecutable
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_getFileContents
Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_getFileType
Arcadia_FileType
Arcadia_FileSystem_getFileType
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_getLastWriteTime
Arcadia_Natural64Value
Arcadia_FileSystem_getLastWriteTime
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_getSaveDirectory
Arcadia_FilePath*
Arcadia_FileSystem_getSaveDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_getWorkingDirectory
Arcadia_FilePath*
Arcadia_FileSystem_getWorkingDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileSystem_regularFileExists
Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
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

// https://michaelheilmann.com/Arcadia/Ring2/Arcadia_FileSystem_getOrCreate
Arcadia_FileSystem*
Arcadia_FileSystem_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING2_FILESYSTEM_FILESYSTEM_H_INCLUDED
