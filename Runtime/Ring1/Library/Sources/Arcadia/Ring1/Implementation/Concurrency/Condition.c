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

#include "Arcadia/Ring1/Implementation/Concurrency/Condition.h"

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
    pthread_cond_t condition;
  #elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    CONDITION_VARIABLE conditionVariable;
    CRITICAL_SECTION criticalSection;
  #else
    #error("environment not (yet) supported")
  #endif
};

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_initialize
  (
    Arcadia_Concurrency_Condition* condition
  )
{
  if (!condition) {
    return Arcadia_Concurrency_Condition_Result_ArgumentInvalid;
  }
  Impl* pimpl = malloc(sizeof(Impl));
  if (!pimpl) {
    return Arcadia_Concurrency_Condition_Result_AllocationFailed;
  }
#if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
    Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
    Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
  if (pthread_cond_init(&pimpl->condition, NULL)) {
    free(pimpl);
    pimpl = NULL;
    return Arcadia_Concurrency_Condition_Result_EnvironmentFailed;
  }
#elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  InitializeConditionVariable(&pimpl->conditionVariable);
#else
  #error("operating system not (yet) supported")
#endif
  Impl* oldValue = Arcadia_Memory_compareAndSwap(&condition->pimpl, NULL, pimpl);
  if (oldValue) {
  #if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
      Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
      Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
    pthread_cond_destroy(&pimpl->condition);
  #elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    /* Intentionally empty. */
  #else
    #error("operating system not (yet) supported")
  #endif
    free(pimpl);
    pimpl = NULL;
    return Arcadia_Concurrency_Condition_Result_Initialized;
  }
  return Arcadia_Concurrency_Condition_Result_Success;
}

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_uninitialize
  (
    Arcadia_Concurrency_Condition* condition
  )
{
  if (!condition) {
    return Arcadia_Concurrency_Condition_Result_ArgumentInvalid;
  }
  Impl* pimpl = Arcadia_Memory_compareAndSwap(&condition->pimpl, condition->pimpl, NULL);
  if (pimpl) {
  #if Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem  || \
      Arcadia_Configuration_OperatingSystem_Cygwin == Arcadia_Configuration_OperatingSystem || \
      Arcadia_Configuration_OperatingSystem_Macos == Arcadia_Configuration_OperatingSystem
    pthread_cond_destroy(&pimpl->condition);
  #elif Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    /* Intentionally empty. */
  #else
    #error("operating system not (yet) supported")
  #endif
    free(pimpl);
    pimpl = NULL;
  }
  return Arcadia_Concurrency_Condition_Result_Success;
}

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_wait
  (
    Arcadia_Concurrency_Condition* condition
  )
{ return Arcadia_Concurrency_Condition_Result_Success; }

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_signalOne
  (
    Arcadia_Concurrency_Condition* condition
  )
{
  if (!condition) {
    return Arcadia_Concurrency_Condition_Result_ArgumentInvalid;
  }
  return Arcadia_Concurrency_Condition_Result_Success;
}

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_signalAll
  (
    Arcadia_Concurrency_Condition* condition
  )
{
  if (!condition) {
    return Arcadia_Concurrency_Condition_Result_ArgumentInvalid;
  }
  return Arcadia_Concurrency_Condition_Result_Success;
}
