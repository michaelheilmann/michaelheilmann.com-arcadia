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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/FileSystem/FileSystem.h"

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/ARMS/Include.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // GetFileAttributes
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <string.h> // strlen
  #include <sys/stat.h> // stat
  #include <errno.h> // errno
  #include <unistd.h> // getcwd
  #include <linux/limits.h> // PATH_MAX
  #include <pwd.h> // struct passwd
#else
  #error("operating system not (yet) supported")
#endif

#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem

static Arcadia_FilePath*
Arcadia_FileSystem_getHomeFolder
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

#endif

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

static Arcadia_FilePath*
Arcadia_FileSystem_getLocal
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static Arcadia_FilePath*
Arcadia_FileSystem_getRoaming
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

#endif

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_FileSystem_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_FileSystem_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_FileSystem_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.FileSystem", Arcadia_FileSystem,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_FileSystem_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

Arcadia_FileSystem*
Arcadia_FileSystem_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_FileSystem);
}

Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, self);
  Arcadia_FileHandle_openForReading(thread, fileHandle, path);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  char p[5012]; size_t n;
  do {
    Arcadia_FileHandle_read(thread, fileHandle, p, 5012, &n);
    if (n > 0) {
      Arcadia_ByteBuffer_insertBackBytes(thread, byteBuffer, p, n);
    }
  } while (n > 0);
  Arcadia_FileHandle_close(thread, fileHandle);
  fileHandle = NULL;
  return byteBuffer;
}

void
Arcadia_FileSystem_setFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path,
    Arcadia_ByteBuffer * contents
  )
{
  Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, self);
  Arcadia_FileHandle_openForWriting(thread, fileHandle, path);
  Arcadia_SizeValue bytesToWrite = contents->sz,
              bytesWritten = 0;
  while (bytesToWrite > 0) {
    Arcadia_SizeValue bytesWrittenNow;
    Arcadia_FileHandle_write(thread, fileHandle, contents->p + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  Arcadia_FileHandle_close(thread, fileHandle);
  fileHandle = NULL;
}

Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(thread, path);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(Arcadia_String_getBytes(thread, nativePathString));
  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
         !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(Arcadia_String_getBytes(thread, nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
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
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(thread, path);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(Arcadia_String_getBytes(thread, nativePathString));
  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(Arcadia_String_getBytes(thread, nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
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
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* nativePath = Arcadia_FilePath_toNative(thread, path);
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  if (FALSE == CreateDirectory(Arcadia_String_getBytes(thread, nativePath), NULL)) {
    if (ERROR_ALREADY_EXISTS != GetLastError()) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
      Arcadia_Thread_jump(thread);
    }
  }
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  if (-1 == mkdir(Arcadia_String_getBytes(thread, nativePath), 0777)) {
    if (errno == EEXIST) {
      errno = 0;
      struct stat sb;
      if (-1 == stat(Arcadia_String_getBytes(thread, nativePath), &sb)) {
        errno = 0;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
        Arcadia_Thread_jump(thread);
      }
      if (!S_ISDIR(sb.st_mode)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
        Arcadia_Thread_jump(thread);
      }
    } else {
      errno = 0;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
      Arcadia_Thread_jump(thread);
    }
  }
#else
  #error("operating system not (yet) supported")
#endif
}

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include "Arcadia/Ring2/FileSystem/DirectoryIteratorWindows.h"
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include "Arcadia/Ring2/FileSystem/DirectoryIteratorLinux.h"
#else
  #error("operating system not (yet) supported")
#endif

Arcadia_DirectoryIterator*
Arcadia_FileSystem_createDirectoryIterator
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  return (Arcadia_DirectoryIterator*)Arcadia_DirectoryIteratorWindows_create(thread, path);
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  return (Arcadia_DirectoryIterator*)Arcadia_DirectoryIteratorLinux_create(thread, path);
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_FilePath*
Arcadia_FileSystem_getWorkingDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  DWORD dwBufferSize = GetCurrentDirectory(0, NULL);
  if (0 == dwBufferSize) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  char* pBuffer = NULL;
  if (Arcadia_ARMS_MemoryManager_allocate(Arcadia_ARMS_getSlabMemoryManager(), &pBuffer, dwBufferSize)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!GetCurrentDirectory(dwBufferSize, pBuffer)) {
    Arcadia_ARMS_MemoryManager_deallocate(Arcadia_ARMS_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_String* filePathString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, pBuffer, dwBufferSize - 1)));
    Arcadia_FilePath* filePath = Arcadia_FilePath_parseWindows(thread, filePathString);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_ARMS_MemoryManager_deallocate(Arcadia_ARMS_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    return filePath;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_ARMS_MemoryManager_deallocate(Arcadia_ARMS_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Thread_jump(thread);
  }
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_StaticAssert(PATH_MAX < Arcadia_SizeValue_Maximum, "environment not (yet) supported");
  #define CWD_CAPACITY (PATH_MAX+1)
  char cwd[CWD_CAPACITY];
  if (!getcwd(cwd, CWD_CAPACITY)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* filePathString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, cwd, strlen(cwd))));
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseUnix(thread, filePathString);
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}

#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem

static Arcadia_FilePath*
Arcadia_FileSystem_getHomeFolder
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
  size_t n = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (n == -1) {
    n = 0x4000; // = all zeroes with the 14th bit set (1 << 14)
  }
  char* p = malloc(n);
  if (NULL == p) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  struct passwd pwd;
  struct passwd* ppwd;
  int s = getpwuid_r(getuid(), &pwd, p, n, &ppwd);
  if (ppwd == NULL) {
    // if s is 0 the no entry for this user id was found.
    free(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_FilePath* filePath = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_String* filePathString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, ppwd->pw_dir, strlen(ppwd->pw_dir))));
    filePath = Arcadia_FilePath_parseUnix(thread, filePathString);
    Arcadia_Thread_popJumpTarget(thread);
    free(p);
    p = NULL;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(p);
    p = NULL;
    Arcadia_Thread_jump(thread);
  }
  return filePath;
}

#endif

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

#include <Shlobj.h>

static Arcadia_FilePath*
Arcadia_FileSystem_getLocal
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
  PWSTR p = NULL;
  HRESULT hResult = SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &p);
  if (FAILED(hResult)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  int iResult;
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, NULL, 0, NULL, NULL);
  if (!iResult) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  char *q = malloc(sizeof(char) * iResult);
  if (!q) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, q, iResult, NULL, NULL);
  CoTaskMemFree(p);
  p = NULL;
  if (!iResult) {
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_FilePath* filePath = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    filePath = Arcadia_FilePath_parseWindows(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, q, iResult - 1))));
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    Arcadia_Thread_jump(thread);
  }
  return filePath;
}

static Arcadia_FilePath*
Arcadia_FileSystem_getRoaming
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
  PWSTR p = NULL;
  HRESULT hResult = SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &p);
  if (FAILED(hResult)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  int iResult;
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, NULL, 0, NULL, NULL);
  if (!iResult) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  char* q = malloc(sizeof(char) * iResult);
  if (!q) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, q, iResult, NULL, NULL);
  CoTaskMemFree(p);
  p = NULL;
  if (!iResult) {
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_FilePath* filePath = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    filePath = Arcadia_FilePath_parseWindows(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, q, iResult - 1))));
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    Arcadia_Thread_jump(thread);
  }
  return filePath;
}

#endif

Arcadia_FilePath*
Arcadia_FileSystem_getConfigurationFolder
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  Arcadia_FilePath* filePath = Arcadia_FileSystem_getLocal(thread, self);
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Michael Heilmann's Arcadia", sizeof(u8"Michael Heilmann's Arcadia") - 1));
  return filePath;
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_FilePath* filePath = Arcadia_FileSystem_getHomeFolder(thread, self);
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Michael Heilmann's Arcadia/Configurations", sizeof(u8"Michael Heilmann's Arcadia/Configurations") - 1));
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}

Arcadia_FilePath*
Arcadia_FileSystem_getSaveFolder
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  Arcadia_FilePath* filePath = Arcadia_FileSystem_getRoaming(thread, self);
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Michael Heilmann's Arcadia", sizeof(u8"Michael Heilmann's Arcadia") - 1));
  return filePath;
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_FilePath* filePath  = Arcadia_FileSystem_getHomeFolder(thread, self);
  Arcadia_FilePath_append(thread, filePath, Arcadia_FilePath_parseGeneric(thread, u8"Michael Heilmann's Arcadia/Saves", sizeof(u8"Michael Heilmann's Arcadia/Saves") - 1));
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  // SYSTEM_INFO, GetSystemInfo, MAX_PATH
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  // PATH_MAX
  #include <limits.h>
  // sysconf
  #include <unistd.h>
#else
  #error("environment not (yet) supported")
#endif

Arcadia_FilePath*
Arcadia_FileSystem_getExecutablePath
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  HMODULE module = GetModuleHandleA(NULL);
  if (!module) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue n = MAX_PATH;
  void* p = Arcadia_Memory_allocateUnmanaged(thread, n);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    do {
      DWORD m = GetModuleFileNameA(module, p, n);
      // There are three cases:
      // m = 0: The function failed.
      // m = n: The buffer is too small.
      //        As MAX_PATH is most likely to small for modern file systems,
      //        we resort to dynamic memory allocation.
      // m < n: m denotes the number of characters copied without the zero terminator.
      if (m == 0) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      } else if (m == n) {
        Arcadia_SizeValue hi, lo;
        Arcadia_safeAddSizeValue(thread, 64, MAX_PATH, &hi, &lo);
        if (hi) {
          lo = Arcadia_SizeValue_Maximum;
        }
        if (lo == n) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        n = lo;
        Arcadia_Memory_reallocateUnmanaged(thread, &p, n);
      } else {
        Arcadia_FilePath* path = Arcadia_FilePath_parseWindows(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, n))));
        Arcadia_Memory_deallocateUnmanaged(thread, p);
        p = NULL;
        Arcadia_Thread_popJumpTarget(thread);
        return path;
      }
    } while (true);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (p) {
      Arcadia_Memory_deallocateUnmanaged(thread, p);
      p = NULL;
    }
    Arcadia_Thread_jump(thread);
  }
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  // space for `PATH_MAX` plus 1 character
  char p[PATH_MAX + 1];
  // `readlink` will write up to `PATH_MAX` plus 1 chars and will not append a zero terminator.
  // The path will not be truncated it must be smaller than or equal to `PATH_MAX`.
  ssize_t n = readlink("/proc/self/exe", p, PATH_MAX);
  if (-1 == n) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  // `readlink` returns a string in some encoding.
  // We assume that this encoding is UTF-8 at the moment.
  return Arcadia_FilePath_parseUnix(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, n))));
#else
  #error("environment not (yet) supported")
#endif
}

static Arcadia_FileSystem* g_instance = NULL;

static void
Arcadia_FileSystem_destroyCallback
  (
    void* observer,
    void* observed
  )
{ g_instance = NULL; }

Arcadia_FileSystem*
Arcadia_FileSystem_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_FileSystem* instance = Arcadia_FileSystem_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &Arcadia_FileSystem_destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
