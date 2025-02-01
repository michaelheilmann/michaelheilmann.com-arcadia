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

// Last modified: 2025-01-01

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Process1.h"

#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include <stdbool.h>
#include <malloc.h>
#include "Arms.h"

static Arcadia_Status
startupArms
  (
  );

static Arcadia_Status
shutdownArms
  (
  );

static Arcadia_Status
startupArms
  (
  )
{
  Arms_Status status = Arms_startup();
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

static Arcadia_Status
shutdownArms
  (
  )
{
  Arms_Status status = Arms_shutdown();
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}


typedef uint32_t ReferenceCount;

#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

struct Arcadia_Process1 {
  ReferenceCount referenceCount;
  Arcadia_Status status;
  Arcadia_JumpTarget* jumpTarget;
};

static Arcadia_Process1* g_process = NULL;

Arcadia_ProcessStatus
Arcadia_Process1_acquire
  (
    Arcadia_Process1* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || ReferenceCount_Maximum == process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  process->referenceCount++;
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process1_relinquish
  (
    Arcadia_Process1* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || !g_process) {
    /* This is, actually, undefined behavior. */
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  if (ReferenceCount_Minimum == --process->referenceCount) {
    if (Arms_shutdown()) {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
    }
    free(g_process);
    g_process = NULL;
  }
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process1_get
  (
    Arcadia_Process1** process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (!g_process) {
    if (Arms_startup()) {
      return Arcadia_ProcessStatus_EnvironmentFailed;
    }
    g_process = malloc(sizeof(Arcadia_Process1));
    if (!g_process) {
      if (Arms_shutdown()) {
        Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    g_process->status = Arcadia_Status_Success;
    g_process->jumpTarget = NULL;
    *process = g_process;
    return Arcadia_ProcessStatus_Success;
  }
  if (ReferenceCount_Maximum == g_process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  g_process->referenceCount++;
  *process = g_process;
  return Arcadia_ProcessStatus_Success;
}

void
Arcadia_Process1_pushJumpTarget
  (
    Arcadia_Process1* process,
    Arcadia_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = process->jumpTarget;
  process->jumpTarget = jumpTarget;
}

void
Arcadia_Process1_popJumpTarget
  (
    Arcadia_Process1* process
  )
{
  process->jumpTarget = process->jumpTarget->previous;
}

Arcadia_NoReturn() void
Arcadia_Process1_jump
  (
    Arcadia_Process1* process
  )
{ 
  longjmp(process->jumpTarget->environment, -1);
}

Arcadia_Status
Arcadia_Process1_getStatus
  (
    Arcadia_Process1* process
  )
{ return process->status; }

void
Arcadia_Process1_setStatus
  (
    Arcadia_Process1* process,
    Arcadia_Status status
  )
{
  process->status = status;
}

#include <string.h>

void
Arcadia_Process1_fillMemory
  (
    Arcadia_Process1* process,
    void* p,
    size_t n,
    uint8_t v
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p)) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  memset(p, v, n);
}

void
Arcadia_Process1_copyMemory
  (
    Arcadia_Process1* process,
    void* p,
    const void* q,
    size_t n
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p) || UINTPTR_MAX - n < ((uintptr_t)q)) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  // Determine if the intervals a = [a.start, a.end] and b = [b.start, b.end] DO overlap.
  //
  // They do NOT overlap if condition [1] or condition [2] is fulfilled:
  // [1] a is completely behind b that is a.start > b.end.
  // [2] b is completely behind a that is b.start > a.end
  // That is, they do not overlap if
  // ([1] OR [1])
  // holds.
  // Consequently, a and b overlap if
  // NOT ([1] OR [2])
  // holds which can be rewritten
  //     NOT ([1] OR [2])
  // <=> NOT [1] AND NOT [2]
  // <=> NOT (a.start > b.end) AND NOT (b.start > a.end)
  // <=> a.start <= b.end AND b.start <= a.end
  //
  // Now let s.start = ((uintptr_t)p), a.end = ((uintptr_t)p) + n, b.start = ((uintptr_t)q), b.end = ((uintptr_t)q) + n to obtain
  bool overlapping = (((uintptr_t)p) <= ((uintptr_t)q) + n)
                  || (((uintptr_t)q) <= ((uintptr_t)p) + n);
  if (overlapping) {
    memmove(p, q, n);
  } else {
    memcpy(p, q, n);
  }
}

void
Arcadia_Process1_allocateUnmanaged
  (
    Arcadia_Process1* process,
    void** p,
    size_t n
  )
{
  Arms_Status status = Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arms_Status_AllocationFailed) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Process1_jump(process);
  }
}

void
Arcadia_Process1_deallocateUnmanaged
  (
    Arcadia_Process1* process,
    void* p
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), p);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    } else {
      Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Process1_jump(process);
  }
}

void
Arcadia_Process1_reallocateUnmanaged
  (
    Arcadia_Process1* process,
    void** p,
    size_t n
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arms_MemoryManager_Status_AllocationFailed) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Process1_jump(process);
  }
}

void
Arcadia_Process1_visitObject
  (
    Arcadia_Process1* process,
    void* object
  )
{
  if (object) {
    Arms_visit(object);
  }
}

Arcadia_Status
Arcadia_Process1_lockObject
  (
    Arcadia_Process1* process,
    void* object
  )
{
  Arms_Status status = Arms_lock(object);
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid: {
      return Arcadia_Status_OperationInvalid;
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process1_unlockObject
  (
    Arcadia_Process1* process,
    void* object
  )
{
  Arms_Status status = Arms_unlock(object);
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid: {
      return Arcadia_Status_OperationInvalid;
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process1_stepArms
  (
    Arcadia_Process1* process
  )
{
  Arms_RunStatistics statistics = { .destroyed = 0 };
  Arms_Status status = Arms_run(&statistics);
  switch (status) {
    case Arms_Status_Success:
    { return Arcadia_Status_Success; }
    break;
    case Arms_Status_AllocationFailed:
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process1_runArms
  (
    Arcadia_Process1* process
  )
{
  Arms_RunStatistics statistics = { .destroyed = 0 };
  do {
    Arms_Status status = Arms_run(&statistics);
    switch (status) {
      case Arms_Status_Success:
      {/*Intentionally empty.*/ }
      break;
      case Arms_Status_AllocationFailed:
      case Arms_Status_OperationInvalid:
      case Arms_Status_ArgumentValueInvalid:
      case Arms_Status_TypeExists:
      case Arms_Status_TypeNotExists:
      default: {
        // This should not happen.
        // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
        // Suggestion is Arcadia_Status_EnvironmentInvalid.
        return Arcadia_Status_OperationInvalid;
      } break;
    };
  } while (statistics.destroyed > 0);
  return Arcadia_Status_Success;
}

void
Arcadia_Process1_registerType
  (
    Arcadia_Process1* process,
    const char* name,
    size_t nameLength,
    void* context,
    void (*typeRemoved)(void*, uint8_t const*, size_t),
    void (*visit)(void*, void*),
    void (*finalize)(void*, void*)
  )
{
  Arms_Status status = Arms_addType(name, nameLength, context, typeRemoved, visit, finalize);
  if (status) {
    switch (status) {
      case Arms_Status_AllocationFailed: {
        Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        Arcadia_Process1_setStatus(process, Arcadia_Status_OperationInvalid);
      } break;
      case Arms_Status_TypeExists: {
        Arcadia_Process1_setStatus(process, Arcadia_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Process1_setStatus(process, Arcadia_Status_OperationInvalid);
      } break;
    };
    Arcadia_Process1_jump(process);
  }
}

void
Arcadia_Process1_allocate
  (
    Arcadia_Process1* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  ) 
{
  void* q = NULL;
  Arms_Status status = Arms_allocate(&q, name, nameLength, size);
  if (status) {
    switch (status) {
      case Arms_Status_AllocationFailed: {
        Arcadia_Process1_setStatus(process, Arms_Status_AllocationFailed);
      } break;
      case Arms_Status_TypeNotExists: {
        Arcadia_Process1_setStatus(process, Arms_Status_TypeNotExists);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        Arcadia_Process1_setStatus(process, Arms_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        Arcadia_Process1_setStatus(process, Arms_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Process1_setStatus(process, Arms_Status_OperationInvalid);
      } break;
    };
    Arcadia_Process1_jump(process);
  }
  *p = q;
}
