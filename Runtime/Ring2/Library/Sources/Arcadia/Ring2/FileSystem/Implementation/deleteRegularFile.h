// Copyright (c) 2018-2024 Michael Heilmann. All rights reserved.

#if !defined(ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DELETEREGULARFILE_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DELETEREGULARFILE_H_INCLUDED

#include "Arcadia/Ring2/FileSystem/FilePath.h"
typedef struct Arcadia_DefaultFileSystem Arcadia_DefaultFileSystem;

/// @brief Delete a regular file.
/// @param thread A pointer to this thread.
/// @param self A pointer to this file system.
/// @param path A pointer to the path.
/// @error Arcadia_Status_AccessDenied access to the file was denied
/// @error Arcadia_Status_OperationFailed deletion failed
/// @error Arcadia_Status_NotFound the file was not found
/// @error Arcadia_Status_ArgumentValueInvalid @a path is a null pointer
/// @error Arcadia_Status_InternalError an internal error occurred
void
Arcadia_DefaultFileSystem_deleteRegularFileHelper
  (
    Arcadia_Thread* thread,
    Arcadia_DefaultFileSystem* self,
    Arcadia_FilePath* path
  );

#endif // ARCADIA_RING2_FILESYSTEM_IMPLEMENTATION_DELETEREGULARFILE_H_INCLUDED
