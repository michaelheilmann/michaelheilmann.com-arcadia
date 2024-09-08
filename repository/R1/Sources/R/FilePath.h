// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
#include "R/Boolean.h"
#include "R/ByteBuffer.h"
#include "R/List.h"
#include "R/String.h"

#include <stdio.h>

typedef struct R_FilePath R_FilePath;

void _R_FilePath_registerType();

struct R_FilePath {
  R_List* fileNames;
  R_BooleanValue relative;
  R_String* root;
};

// Create an empty file path.
R_FilePath*
R_FilePath_create
  (
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
R_FilePath_parseWindowsFilePath
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// Parse a Unix file path.
// 
// Unix is a single root file system hence root is always null.
// If the path begins with a slash, then relative is false.
// Otherwise relative is true.
R_FilePath*
R_FilePath_parseUnixFilePath
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// Invoke R_FilePath_parseUnixFilePath or R_FilePath_parseWindowsFilePath depending on the operating system.
R_FilePath*
R_FilePath_parseNative
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

R_String*
R_FilePath_toNative
  (
    R_FilePath* self
  );

// Windows: GetFullPathName under Windows.
// Linux: not yet implemented.
R_FilePath*
R_FilePath_getFullPath
  (
    R_FilePath* self
  );

R_BooleanValue
R_FilePath_isEqualTo
  (
    R_FilePath* self,
    R_FilePath* other
  );

#endif // R_FILEPATH_H_INCLUDED
