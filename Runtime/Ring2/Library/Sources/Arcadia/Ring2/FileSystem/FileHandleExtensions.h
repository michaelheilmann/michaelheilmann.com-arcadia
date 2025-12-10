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

#if !defined(ARCADIA_RING2_FILESYSTEM_FILEHANDLEEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_FILEHANDLEEXTENSIONS_H_INCLUDED

#include "Arcadia/Ring2/FileSystem/FileHandle.h"
typedef struct Arcadia_String Arcadia_String;
typedef struct Arcadia_StringBuffer Arcadia_StringBuffer;

/// @brief Write the contents of a string buffer to this file handle.
/// @param self A pointer to this file handle.
/// @param string A pointer to the string.
void Arcadia_FileHandle_writeString(Arcadia_Thread* thread, Arcadia_FileHandle* self, Arcadia_String* string);

/// @brief Write the contents of a string buffer to this file handle.
/// @param self A pointer to this file handle.
/// @param string A pointer to the string buffer.
void Arcadia_FileHandle_writeStringBuffer(Arcadia_Thread* thread,Arcadia_FileHandle* self, Arcadia_StringBuffer* stringBuffer);

#endif // ARCADIA_RING2_FILESYSTEM_FILEHANDLEEXTENSIONS_H_INCLUDED
