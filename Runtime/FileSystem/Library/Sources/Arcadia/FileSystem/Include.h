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

#if !defined(ARCADIA_FILESYSTEM_INCLUDE_H_INCLUDED)
#define ARCADIA_FILESYSTEM_INCLUDE_H_INCLUDED

// If a file x belongs to a module a and ARCADIA_a_MODULE is not defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_FILESYSTEM_MODULE")
#define ARCADIA_FILESYSTEM_MODULE (1)

// If a file x of a module a is not an export file of that module and ARCADIA_a_EXPORT is defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_FILESYSTEM_EXPORT")
#define ARCADIA_FILESYSTEM_EXPORT (1)

#include "Arcadia/FileSystem/DirectoryIterator.h"
#include "Arcadia/FileSystem/ExistingFilePolicy.h"
#include "Arcadia/FileSystem/FileAccessMode.h"
#include "Arcadia/FileSystem/FileHandle.h"
#include "Arcadia/FileSystem/FileHandleExtensions.h"
#include "Arcadia/FileSystem/FilePath.h"
#include "Arcadia/FileSystem/FileSystem.h"
#include "Arcadia/FileSystem/FileType.h"
#include "Arcadia/FileSystem/NonExistingFilePolicy.h"

#undef ARCADIA_FILESYSTEM_EXPORT
#pragma pop_macro("ARCADIA_FILESYSTEM_EXPORT")

#undef ARCADIA_FILESYSTEM_MODULE
#pragma pop_macro("ARCADIA_FILESYSTEM_MODULE")

#endif // ARCADIA_FILESYSTEM_INCLUDE_H_INCLUDED
