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

// Last modified: 2024-09-08

#if !defined(R_FILEPATH_H_INCLUDED)
#define R_FILEPATH_H_INCLUDED

#include "R/Configure.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "R/ByteBuffer.h"
#include "R/List.h"
#include "R/String.h"

/// The Generic Path Format
/// directories are separated by a foward slash
/// ```
/// a/b/c
/// ```
/// an absolute path is denotated by a leading slash
/// ```
/// /a/b/c
/// ```
/// trailing slashes are ignored
/// For Windows, `/a` is translated to `a:\` and `/a(/<dir1>)(/<dir2>)*` is translated to `a:\<dir1>(\<dir2>)*`
/// For Linux, `/a(/<dir>)* is translated to `/a(/<dir>)*`
Rex_declareObjectType(u8"R.FilePath", R_FilePath, u8"Arcadia.Object");

struct R_FilePath {
  Arcadia_Object _parent;
  R_List* fileNames;
  Arcadia_BooleanValue relative;
  Arcadia_String* root;
};

// Create an empty file path.
R_FilePath*
R_FilePath_create
  (
    Arcadia_Process* process
  );

// Parse a Windows file path.
//
// Windows is a multi root file system.
// If a drive letter followed by a colon is specified, then the drive letter is the root.
// Otherwise the root is null.
//
// If there is a root and a slash follows, then relative is false.
// Otherwise it is true.
R_FilePath*
R_FilePath_parseWindows
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// Parse a Unix file path.
//
// Unix is a single root file system hence root is always null.
// If the path begins with a slash, then relative is false.
// Otherwise relative is true.
R_FilePath*
R_FilePath_parseUnix
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// Invoke R_FilePath_parseUnix or R_FilePath_parseWindows depending on the operating system.
R_FilePath*
R_FilePath_parseNative
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// Parse a Generic file path.
R_FilePath*
R_FilePath_parseGeneric
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

Arcadia_String*
R_FilePath_toNative
  (
    Arcadia_Process* process,
    R_FilePath* self
  );

// Get the full path name.
// This function can file if the specified file does not exist.
R_FilePath*
R_FilePath_getFullPath
  (
    Arcadia_Process* process,
    R_FilePath* self
  );

Arcadia_BooleanValue
R_FilePath_isEqualTo
  (
    Arcadia_Process* process,
    R_FilePath* self,
    R_FilePath* other
  );

/// @brief Get if this file path is absolute.
/// @param self This file path.
/// @return #Arcadia_BooleanValue_True if this file path is absolute. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
R_FilePath_isAbsolute
  (
    R_FilePath* self
  );

/// @brief Get if this file path is relative.
/// @param self This file path.
/// @return #Arcadia_BooleanValue_True if this file path is relative. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
R_FilePath_isRelative
  (
    R_FilePath* self
  );

/// @brief Appennd a relative path to a path.
/// @param self The path to append to.
/// @param other The relative path to append.
void
R_FilePath_append
  (
    Arcadia_Process* process,
    R_FilePath* self,
    R_FilePath* other
  );

#endif // R_FILEPATH_H_INCLUDED
