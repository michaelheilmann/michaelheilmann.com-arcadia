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

#if !defined(ARCADIA_FILESYSTEM_FILEPATH_H_INCLUDED)
#define ARCADIA_FILESYSTEM_FILEPATH_H_INCLUDED

#if !defined(ARCADIA_FILESYSTEM_MODULE)
  #error("do not include directly, include `Arcadia/FileSystem/Include.h` instead")
#endif

#include "Arcadia/FileSystem/Configure.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Collections/Include.h"

/// @remarks
/// A general path consists either
/// - a root and zero or more components which is called an absolute path
/// - no root and one or more components which is called a relative path
/// @remarks
/// directories are separated by a foward slash
/// ```
/// a/b/c
/// ```
/// @remarks
/// an absolute path is denoted by a leading slash
/// ```
/// /a/b/c
/// ```
/// For example, under Windows `/C/Windows/Systme` is `CX:\Windows\System` in native format.
Arcadia_declareObjectType(u8"Arcadia.FilePath", Arcadia_FilePath,
                          u8"Arcadia.Object");

struct Arcadia_FilePathDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_FilePath {
  Arcadia_Object _parent;
  Arcadia_List* fileNames;
  // @todo Remove this. @a root already indicates if the path is relative or absolute.
  Arcadia_BooleanValue relative;
  // If this is null, then the file path is relative.
  // Otherwise is is absolute.
  Arcadia_String* root;
};

// Create an empty file path.
Arcadia_FilePath*
Arcadia_FilePath_create
  (
    Arcadia_Thread* thread
  );

// Clone a file path.
Arcadia_FilePath*
Arcadia_FilePath_clone
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

// Parse a Windows file path.
//
// Windows is a multi root file system.
// If a drive letter followed by a colon is specified, then the drive letter is the root.
// Otherwise the root is null.
//
// If there is a root and a slash follows, then relative is false.
// Otherwise it is true.
Arcadia_FilePath*
Arcadia_FilePath_parseWindows
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

// Parse a Unix file path.
//
// Unix is a single root file system hence root is always null.
// If the path begins with a slash, then relative is false.
// Otherwise relative is true.
Arcadia_FilePath*
Arcadia_FilePath_parseUnix
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

// Invoke Arcadia_FilePath_parseUnix or Arcadia_FilePath_parseWindows depending on the operating system.
Arcadia_FilePath*
Arcadia_FilePath_parseNative
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

Arcadia_String*
Arcadia_FilePath_toNative
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_BooleanValue appendZeroTerminator
  );

// Parse a Generic file path.
Arcadia_FilePath*
Arcadia_FilePath_parseGeneric
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

Arcadia_String*
Arcadia_FilePath_toGeneric
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

// Get the full path name.
// This function can file if the specified file does not exist.
Arcadia_FilePath*
Arcadia_FilePath_getFullPath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

Arcadia_BooleanValue
Arcadia_FilePath_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  );

/// @brief Get if this file path is absolute.
/// @param self This file path.
/// @return #Arcadia_BooleanValue_True if this file path is absolute. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_FilePath_isAbsolute
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

/// @brief Get if this file path is relative.
/// @param self This file path.
/// @return #Arcadia_BooleanValue_True if this file path is relative. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_FilePath_isRelative
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

/// @brief Appennd a relative path to a path.
/// @param self The path to append to.
/// @param other The relative path to append.
void
Arcadia_FilePath_append
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  );

/// @brief Return the root path component if any.
/// @return The root path component if any, null otherwise.
/// @remarks
/// For Linux, this is `/` in native form. 
/// For Windows this is something like `C:\` in native form.
Arcadia_FilePath*
Arcadia_FilePath_getRootPath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

/// @brief Return the relative path if any.
/// @return The relative path component if any, null otherwise.
/// @remarks
/// For `C:\` on Windows or for `/` on Linux this function returns null.
/// For `C:\x` on Windows or for `/x` on Linux this is `x`.
/// For `C:\x\y` on Windows or for `/x/y` on Linux this is `x/y`.
/// For `C:\x\y\a.txt` on Windows or for `/x/y/a.txt` this is `x/y/a.txt`.
Arcadia_FilePath*
Arcadia_FilePath_getRelativePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

/// @brief Get the parent path.
/// @param thread A pointer to this thread.
/// @param self A poiner to this file path.
/// @return The parent path if any, null otherwise.
/// @remarks
/// - If there is a root and there are no components, this function returns null.
/// - If there is no root and there is only one component, this function returns null.
/// - Otherwise we remove the last component..
Arcadia_FilePath*
Arcadia_FilePath_getParent
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

Arcadia_String*
Arcadia_FilePath_getExtension
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

void
Arcadia_FilePath_addOrReplaceExtension
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_String* extension
  );

#endif // ARCADIA_FILESYSTEM_FILEPATH_H_INCLUDED
