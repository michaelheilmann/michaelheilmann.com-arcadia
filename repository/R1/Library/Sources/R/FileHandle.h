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

// Last modified: 2024-08-29

#if !defined(R_FILEHANDLE_H_INCLUDED)
#define R_FILEHANDLE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "R/Object.h"
#include "Arcadia/Ring1/Implementation/Size.h"
typedef struct R_FilePath R_FilePath;
typedef struct R_FileSystem R_FileSystem;

// FILE
#include <stdio.h>

Rex_declareObjectType(u8"R.FileHandle", R_FileHandle, u8"R.Object");

struct R_FileHandle {
  R_Object _parent;
  R_FileSystem* fileSystem;
  Arcadia_Natural8Value flags;
  FILE* fd;
};

// https://michaelheilmann.com/repository/R1/#r-filehandle-create
R_FileHandle*
R_FileHandle_create
  (
    Arcadia_Process* process,
    R_FileSystem* fileSystem
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isclosed
Arcadia_BooleanValue
R_FileHandle_isClosed
  (
    Arcadia_Process* process,
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopened
Arcadia_BooleanValue
R_FileHandle_isOpened
  (
    Arcadia_Process* process,
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopenedforreading
Arcadia_BooleanValue
R_FileHandle_isOpenedForReading
  (
    Arcadia_Process* process,
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopenedforwriting
Arcadia_BooleanValue
R_FileHandle_isOpenedForWriting
  (
    Arcadia_Process* process,
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-close
void
R_FileHandle_close
  (
    R_FileHandle* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-openforreading
void
R_FileHandle_openForReading
  (
    Arcadia_Process* process,
    R_FileHandle* self,
    R_FilePath* path
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-openforwriting
void
R_FileHandle_openForWriting
  (
    Arcadia_Process* process,
    R_FileHandle* self,
    R_FilePath* path
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-read
void
R_FileHandle_read
  (
    Arcadia_Process* process,
    R_FileHandle* self,
    void* byes,
    Arcadia_SizeValue bytesToRead,
    Arcadia_SizeValue* bytesRead
  );
     
// https://michaelheilmann.com/repository/R1/#r-filehandle-write    
void
R_FileHandle_write
  (
    Arcadia_Process* process,
    R_FileHandle* self,
    void const* bytes,
    Arcadia_SizeValue bytesToWrite,
    Arcadia_SizeValue* bytesWritten
  );

#endif // R_FILEHANDLE_H_INCLUDED
