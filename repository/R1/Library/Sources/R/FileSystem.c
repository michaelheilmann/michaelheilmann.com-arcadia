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

#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // GetFileAttributes
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  #include <sys/stat.h> // stat
  #include <errno.h> // errno
  #include <unistd.h> // getcwd
  #include <linux/limits.h> // PATH_MAX
#else
  #error("operating system not (yet) supported")
#endif

#include "Arms.h"

static void
R_FileSystem_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

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

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_FileSystem_constructImpl,
  .destruct = &R_FileSystem_destruct,
  .visit = &R_FileSystem_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.FileSystem", R_FileSystem, "R.Object", R_Object, &_typeOperations);

static void
R_FileSystem_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_FileSystem* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_FileSystem_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  R_Object_setType((R_Object*)_self, _type);
}

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

R_FileSystem*
R_FileSystem_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_FileSystem* self = R_allocateObject(_R_FileSystem_getType(), 0, &argumentValues[0]);
  return self;
}

R_ByteBuffer*
R_FileSystem_getFileContents
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create(self);
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
  R_FileHandle* fileHandle = R_FileHandle_create(self);
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

R_BooleanValue
R_FileSystem_regularFileExists
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_String* nativePathString = R_FilePath_toNative(path);
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(R_String_getBytes(nativePathString));

  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
         !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(R_String_getBytes(nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        R_setStatus(R_Status_EnvironmentFailed);
        R_jump();
      } break;
    };
    return R_BooleanValue_False;
  }
  return S_IFREG == (stat.st_mode & S_IFMT) || S_IFLNK == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

R_BooleanValue
R_FileSystem_directoryFileExists
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_String* nativePathString = R_FilePath_toNative(path);
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(R_String_getBytes(nativePathString));
  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(R_String_getBytes(nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        R_setStatus(R_Status_EnvironmentFailed);
        R_jump();
      } break;
    };
    return R_BooleanValue_False;
  }
  return S_IFDIR == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

void
R_FileSystem_createDirectory
  (
    R_FileSystem* self,
    R_FilePath* path
  )
{
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  R_String* nativePath = R_FilePath_toNative(path);
  if (FALSE == CreateDirectory(R_String_getBytes(nativePath), NULL)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  R_String* nativePath = R_FilePath_toNative(path);
  if (-1 == mkdir(R_String_getBytes(nativePath), 0777)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#else
  #error("operating system not (yet) supported")
#endif
}

R_FilePath*
R_FileSystem_getWorkingDirectory
  (
    R_FileSystem* self
  )
{
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  DWORD dwBufferSize = GetCurrentDirectory(0, NULL);
  if (0 == dwBufferSize) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  char* pBuffer = NULL;
  if (Arms_MemoryManager_allocate(Arms_getSlabMemoryManager(), &pBuffer, dwBufferSize)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (!GetCurrentDirectory(dwBufferSize, pBuffer)) {
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_FilePath* filePath = R_FilePath_parseWindows(pBuffer, dwBufferSize - 1);
    R_popJumpTarget();
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    return filePath;
  } else {
    R_popJumpTarget();
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    R_jump();
  }
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  c_static_assert(PATH_MAX < R_SizeValue_Maximum, "environment not (yet) supported");
  #define CWD_CAPACITY (PATH_MAX+1)
  char cwd[CWD_CAPACITY];
  if (!getcwd(cwd, CWD_CAPACITY)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  R_FilePath* filePath = R_FilePath_parseUnix(cwd, c_strlen(cwd));
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}
