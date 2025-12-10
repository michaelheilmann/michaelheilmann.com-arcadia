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

#include "Arcadia/Ring1/Implementation/Concurrency/Mutex.h"

#include "Arcadia/Ring1/Implementation/Concurrency/CompareAndSwap.h"
#include <malloc.h>

#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
    Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
    Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
  #include <pthread.h>
#elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error("environment not (yet) supported")
#endif

typedef struct Impl Impl;

struct Impl {
#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
    Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
    Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
  pthread_mutex_t mutex;
#elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  HANDLE mutex;
#else
  #error("environment not (yet) supported")
#endif
};

Arcadia_Concurrency_Mutex_Result
Arcadia_Concurrency_Mutex_initialize
  (
    Arcadia_Concurrency_Mutex* mutex
  )
{
  if (!mutex) {
    return Arcadia_Concurrency_Mutex_Result_ArgumentInvalid;
  }
  Impl* pimpl = malloc(sizeof(Impl));
  if (!pimpl) {
    return Arcadia_Concurrency_Mutex_Result_AllocationFailed;
  }
#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
    Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
    Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  int result = pthread_mutex_init(&pimpl->mutex, &attr);
  pthread_mutexattr_destroy(&attr);
  if (result) {
    free(pimpl);
    pimpl = NULL;
    return Arcadia_Concurrency_Mutex_Result_EnvironmentFailed;
  }
#elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  pimpl->mutex = CreateMutex(NULL, FALSE, NULL);
  if (!pimpl->mutex) {
    free(pimpl);
    pimpl = NULL;
    return Arcadia_Concurrency_Mutex_Result_EnvironmentFailed;
  }
#else
  #error("operating system not (yet) supported")
#endif
  Impl* oldValue = Arcadia_Memory_compareAndSwap(&mutex->pimpl, NULL, pimpl);
  if (oldValue) {
  #if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
      Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
      Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
    pthread_mutex_destroy(&pimpl->mutex);
  #elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    CloseHandle(pimpl->mutex);
    pimpl->mutex = NULL;
  #else
    #error("operating system not (yet) supported")
  #endif
    free(pimpl);
    pimpl = NULL;
    return Arcadia_Concurrency_Mutex_Result_Initialized;
  }
  return Arcadia_Concurrency_Mutex_Result_Success;
}

Arcadia_Concurrency_Mutex_Result
Arcadia_Concurrency_Mutex_uninitialize
  (
    Arcadia_Concurrency_Mutex* mutex
  )
{
  if (!mutex) {
    return Arcadia_Concurrency_Mutex_Result_ArgumentInvalid;
  }
  Impl* pimpl = Arcadia_Memory_compareAndSwap(&mutex->pimpl, mutex->pimpl, NULL);
  if (pimpl) {
  #if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
      Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
      Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
    pthread_mutex_destroy(&pimpl->mutex);
  #elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    CloseHandle(pimpl->mutex);
    pimpl->mutex = NULL;
  #else
    #error("operating system not (yet) supported")
  #endif
    free(pimpl);
    pimpl = NULL;
  }
  return Arcadia_Concurrency_Mutex_Result_Success;
}

Arcadia_Concurrency_Mutex_Result
Arcadia_Concurrency_Mutex_lock
  (
    Arcadia_Concurrency_Mutex* mutex
  )
{
  if (!mutex) {
    return Arcadia_Concurrency_Mutex_Result_ArgumentInvalid;
  }
  return Arcadia_Concurrency_Mutex_Result_Success;
}

Arcadia_Concurrency_Mutex_Result
Arcadia_Concurrency_Mutex_unlock
  (
    Arcadia_Concurrency_Mutex* mutex
  )
{
  if (!mutex) {
    return Arcadia_Concurrency_Mutex_Result_ArgumentInvalid;
  }
  return Arcadia_Concurrency_Mutex_Result_Success;
}
