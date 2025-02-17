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

// Last modified: 2024-10-07

#include "Arcadia/Ring2/Implementation/FileSystem.h"

#include "Arcadia/Ring2/Implementation/FileHandle.h"
#include "Arcadia/Ring2/Implementation/FilePath.h"
#include "Arcadia/Ring2/Implementation/String.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // GetFileAttributes
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <string.h> // strlen
  #include <sys/stat.h> // stat
  #include <errno.h> // errno
  #include <unistd.h> // getcwd
  #include <linux/limits.h> // PATH_MAX
#else
  #error("operating system not (yet) supported")
#endif

#include "Arms.h"

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self
  );

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_FileSystem_constructImpl,
  .destruct = &Arcadia_FileSystem_destruct,
  .visit = &Arcadia_FileSystem_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"Arcadia.FileSystem", Arcadia_FileSystem, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_FileSystem* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_FileSystem_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

Arcadia_FileSystem*
Arcadia_FileSystem_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_FileSystem* self = R_allocateObject(process, _Arcadia_FileSystem_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create(process, self);
  R_FileHandle_openForReading(process, fileHandle, path);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(process);
  char p[5012]; size_t n;
  do {
    R_FileHandle_read(process, fileHandle, p, 5012, &n);
    if (n > 0) {
      Arcadia_ByteBuffer_append_pn(process, byteBuffer, p, n);
    }
  } while (n > 0);
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
  return byteBuffer;
}

void
Arcadia_FileSystem_setFileContents
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path,
    Arcadia_ByteBuffer * contents
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create(process, self);
  R_FileHandle_openForWriting(process, fileHandle, path);
  Arcadia_SizeValue bytesToWrite = contents->sz,
              bytesWritten = 0;
  while (bytesToWrite > 0) {
    Arcadia_SizeValue bytesWrittenNow;
    R_FileHandle_write(process, fileHandle, contents->p + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
}

Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(process, path);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(Arcadia_String_getBytes(process, nativePathString));

  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
         !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(Arcadia_String_getBytes(process, nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
      } break;
    };
    return Arcadia_BooleanValue_False;
  }
  return S_IFREG == (stat.st_mode & S_IFMT) || S_IFLNK == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

Arcadia_BooleanValue
Arcadia_FileSystem_directoryFileExists
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(process, path);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(Arcadia_String_getBytes(process, nativePathString));
  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(Arcadia_String_getBytes(process, nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
      } break;
    };
    return Arcadia_BooleanValue_False;
  }
  return S_IFDIR == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

void
Arcadia_FileSystem_createDirectory
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePath = Arcadia_FilePath_toNative(process, path);
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  if (FALSE == CreateDirectory(Arcadia_String_getBytes(process, nativePath), NULL)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  if (-1 == mkdir(Arcadia_String_getBytes(process, nativePath), 0777)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_FilePath*
Arcadia_FileSystem_getWorkingDirectory
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  DWORD dwBufferSize = GetCurrentDirectory(0, NULL);
  if (0 == dwBufferSize) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  char* pBuffer = NULL;
  if (Arms_MemoryManager_allocate(Arms_getSlabMemoryManager(), &pBuffer, dwBufferSize)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  if (!GetCurrentDirectory(dwBufferSize, pBuffer)) {
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_FilePath* filePath = Arcadia_FilePath_parseWindows(process, pBuffer, dwBufferSize - 1);
    Arcadia_Process_popJumpTarget(process);
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    return filePath;
  } else {
    Arcadia_Process_popJumpTarget(process);
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Process_jump(process);
  }
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_StaticAssert(PATH_MAX < Arcadia_SizeValue_Maximum, "environment not (yet) supported");
  #define CWD_CAPACITY (PATH_MAX+1)
  char cwd[CWD_CAPACITY];
  if (!getcwd(cwd, CWD_CAPACITY)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseUnix(process, cwd, strlen(cwd));
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}
