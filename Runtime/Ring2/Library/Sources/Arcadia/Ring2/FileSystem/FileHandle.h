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

#if !defined(ARCADIA_RING2_FILESYSTEM_FILEHANDLE_H_INCLUDED)
#define ARCADIA_RING2_FILESYSTEM_FILEHANDLE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_FilePath Arcadia_FilePath;
typedef struct Arcadia_FileSystem Arcadia_FileSystem;

// FILE
#include <stdio.h>

Arcadia_declareObjectType(u8"Arcadia.FileHandle", Arcadia_FileHandle,
                          u8"Arcadia.Object");

struct Arcadia_FileHandle {
  Arcadia_Object _parent;
  Arcadia_FileSystem* fileSystem;
  Arcadia_Natural8Value flags;
  FILE* fd;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_create
Arcadia_FileHandle*
Arcadia_FileHandle_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* fileSystem
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_isClosed
Arcadia_BooleanValue
Arcadia_FileHandle_isClosed
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_isOpened
Arcadia_BooleanValue
Arcadia_FileHandle_isOpened
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_isOpenedForReading
Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_isOpenedForWriting
Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_close
void
Arcadia_FileHandle_close
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_openForReading
void
Arcadia_FileHandle_openForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_openForWriting
void
Arcadia_FileHandle_openForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_read
void
Arcadia_FileHandle_read
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void* byes,
    Arcadia_SizeValue bytesToRead,
    Arcadia_SizeValue* bytesRead
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_write
void
Arcadia_FileHandle_write
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void const* bytes,
    Arcadia_SizeValue bytesToWrite,
    Arcadia_SizeValue* bytesWritten
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_openStandardInput
void
Arcadia_FileHandle_openStandardInput
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_openStandardOutput
void
Arcadia_FileHandle_openStandardOutput
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileHandle_openStandardError
void
Arcadia_FileHandle_openStandardError
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

#endif // ARCADIA_RING2_FILESYSTEM_FILEHANDLE_H_INCLUDED
