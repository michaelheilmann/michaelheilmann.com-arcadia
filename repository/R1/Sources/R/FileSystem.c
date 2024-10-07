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

// Last modified: 2024-10-07

#include "R/FileSystem.h"

#include "R/FileHandle.h"
#include "R/FilePath.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/String.h"

static void
R_FileSystem_visit
  (
    R_FileSystem* self
  );

static void
R_FileSystem_destruct
  (
    R_FileSystem* self
  );

static void
R_FileSystem_visit
  (
    R_FileSystem* self
  )
{/*Intentionally empty.*/}

static void
R_FileSystem_destruct
  (
    R_FileSystem* self
  )
{/*Intentionally empty.*/}

void
_R_FileSystem_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType(u8"R.Object", sizeof("R.Object") - 1);
  R_registerObjectType(u8"R.FileSystem", sizeof(u8"R.FileSystem") - 1, sizeof(R_FileSystem), parentType, NULL, &R_FileSystem_visit, &R_FileSystem_destruct);
}

void
R_FileSystem_construct
  (
    R_FileSystem* self
  )
{
  R_Type* _type = R_getObjectType(u8"R.FileSystem", sizeof(u8"R.FileSystem") - 1);
  R_Object_construct((R_Object*)self);
  R_Object_setType((R_Object*)self, _type);
}

R_FileSystem*
R_FileSystem_create
  (
  )
{
  R_FileSystem* self = R_allocateObject(R_getObjectType(u8"R.FileSystem", sizeof(u8"R.FileSystem") - 1));
  R_FileSystem_construct(self);
  return self;
}

R_ByteBuffer*
R_FileSystem_getFileContents
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create();
  R_FileHandle_openForReading(fileHandle, path);
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  char p[5012]; size_t n;
  do {
    R_FileHandle_read(fileHandle, p, 5012, &n);
    if (n > 0) {
      R_ByteBuffer_append_pn(byteBuffer, p, n);
    }
  } while (n > 0);
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
  return byteBuffer;
}

void
R_FileSystem_setFileContents
  (
    R_FileSystem* self,
    R_FilePath* path,
    R_ByteBuffer * contents
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create();
  R_FileHandle_openForWriting(fileHandle, path);
  R_SizeValue bytesToWrite = contents->sz,
              bytesWritten = 0;
  while (bytesToWrite > 0) {
    R_SizeValue bytesWrittenNow;
    R_FileHandle_write(fileHandle, contents->p + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
}

#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  #include <sys/stat.h>
#else
  #error("operating system not (yet) supported")
#endif


void
R_FileSystem_createDirectory
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  R_String* nativePath = R_FilePath_toNative(path);
  if (FALSE == CreateDirectory(nativePath->p, NULL)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  R_String* nativePath = R_FilePath_toNative(path);
  if (-1 == mkdir(nativePath->p, 0777)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#else
  #error("operating system not (yet) supported")
#endif  
}
