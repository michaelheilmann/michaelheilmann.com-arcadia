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

// Last modified: 2024-08-29

#if !defined(R_FILEHANDLE_H_INCLUDED)
#define R_FILEHANDLE_H_INCLUDED

#include "configure.h"
#include "r/boolean.h"
#include "r/natural8.h"
typedef struct R_ByteBuffer R_ByteBuffer;

#include <stdio.h>

typedef struct R_FileHandle R_FileHandle;

void _R_FileHandle_registerType();

struct R_FileHandle {
  R_Natural8Value flags;
  FILE* fd;
};

/// @brief Create a file handle.
/// @return A pointer to the file handle.
/// @remarks The file handle is not opened.
R_FileHandle* R_FileHandle_create();

/// @brief Get if this file handle is closed.
/// @param self A pointer to this file.
/// @return
/// R_BooleanValue_True if the file handle is closed.
/// R_BooleanValue_False otherwise.
R_BooleanValue R_FileHandle_isClosed(R_FileHandle const* self);

/// @brief Get if this file handle is opened.
/// @param self A pointer to this file.
/// @return
/// R_BooleanValue_True if the file handle is opened.
/// R_BooleanValue_False otherwise.
R_BooleanValue R_FileHandle_isOpened(R_FileHandle const* self);

/// @brief Get if this file handle is openend for reading.
/// @param self A pointer to this file.
/// @return
/// R_BooleanValue_True if the file handle is opened for reading.
/// R_BooleanValue_False otherwise.
R_BooleanValue R_FileHandle_isOpenedForReading(R_FileHandle const* self);

/// @brief Get if this file handle is openend for writing.
/// @param self A pointer to this file.
/// @return
/// R_BooleanValue_True if the file handle is opened for reading.
/// R_BooleanValue_False otherwise.
R_BooleanValue R_FileHandle_isOpenedForWriting(R_FileHandle const* self);

/// @brief Close this file handle. Do nothing if it is not open.
/// @param self A pointer to this file handle.
void R_FileHandle_close(R_FileHandle* self);

/// @brief Open this file handle for reading.
/// @param self A pointer to this file handle.
/// @param path The path to the file to read from.
void R_FileHandle_openForReading(R_FileHandle* self, char const* path);

/// @brief Open this file handle for writing.
/// @param self A pointer to this file handle.
/// @param path The path to the file to write to.
void R_FileHandle_openForWriting(R_FileHandle* self, char const* path);

/// @brief Read from the file.
/// @post
/// <code>*received</code> is assigned the number of Bytes read.
/// This number may be smaller than @a requested if the end of the file was reached.
/// The Bytes were stored at th
/// Sets the status variable to R_Status_OperationInvalid if the file is not opened for reading.
/// Sets the status variable to R_Status_FileSystemOperationFailed if an error is enccountered.
void R_FileHandle_read(R_FileHandle* self, void* buffer, size_t requested, size_t* received);
         
/// Write <code>requested</code> from the array pointed to by <code>buffer</code> to this file handle.
/// Sets the status variable to R_Status_OperationInvalid if the file is not opened for reading.
/// If an error is raised, the existence and contents of the file are unspecified.
void R_FileHandle_write(R_FileHandle* self, void const* bytes, size_t bytesToWrite);

#endif // R_FILEHANDLE_H_INCLUDED
