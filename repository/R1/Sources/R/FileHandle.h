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

#include "R/Configure.h"
#include "R/Boolean.h"
#include "R/ByteBuffer.h"
#include "R/Natural8.h"
#include "R/Object.h"
#include "R/Size.h"
typedef struct R_FilePath R_FilePath;

// FILE
#include <stdio.h>

Rex_declareObjectType("R.FileHandle", R_FileHandle, "R.Object");

struct R_FileHandle {
  R_Object _parent;
  R_Natural8Value flags;
  FILE* fd;
};

void
R_FileHandle_construct
  (
    R_FileHandle* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-create
R_FileHandle*
R_FileHandle_create
  (
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isclosed
R_BooleanValue
R_FileHandle_isClosed
  (
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopened
R_BooleanValue
R_FileHandle_isOpened
  (
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopenedforreading
R_BooleanValue
R_FileHandle_isOpenedForReading
  (
    R_FileHandle const* self
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-isopenedforwriting
R_BooleanValue
R_FileHandle_isOpenedForWriting
  (
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
    R_FileHandle* self,
    R_FilePath* path
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-openforwriting
void
R_FileHandle_openForWriting
  (
    R_FileHandle* self,
    R_FilePath* path
  );

// https://michaelheilmann.com/repository/R1/#r-filehandle-read
void
R_FileHandle_read
  (
    R_FileHandle* self,
    void* byes,
    R_SizeValue bytesToRead,
    R_SizeValue* bytesRead
  );
     
// https://michaelheilmann.com/repository/R1/#r-filehandle-write    
void
R_FileHandle_write
  (
    R_FileHandle* self,
    void const* bytes,
    R_SizeValue bytesToWrite,
    R_SizeValue* bytesWritten
  );

#endif // R_FILEHANDLE_H_INCLUDED
