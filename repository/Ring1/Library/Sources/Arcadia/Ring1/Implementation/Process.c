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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Arms/Include.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include "Arcadia/Ring1/Implementation/Atoms.private.h"
#include "Arcadia/Ring1/Implementation/Types.private.h"
#include <stdbool.h>
#include <string.h>

typedef const ModuleInfo* (GetModuleInfo)();
static GetModuleInfo* g_modules[] = {
  &Arcadia_Atoms_getModule,
  &Arcadia_Types_getModule,
};
static size_t g_initializedModules = 0;
static const size_t g_numberOfModules = sizeof(g_modules) / sizeof(const ModuleInfo*);

static void
startupModules
  (
    Arcadia_Process* process
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (size_t i = 0, n = g_numberOfModules; i < n; ++i) {
      g_modules[i]()->onStartUp(thread);
      g_initializedModules++;
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    while (g_initializedModules > 0) {
      Arcadia_Process_runArms(process, true);
      g_modules[--g_initializedModules]()->onShutDown(thread);
    }
    Arcadia_Process_runArms(process, true);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownModules
  (
    Arcadia_Process* process
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  while (g_initializedModules > 0) {
    Arcadia_Process_runArms(process, true);
    g_modules[--g_initializedModules]()->onShutDown(thread);
  }
  Arcadia_Process_runArms(process, true);
}

typedef struct ArmsCallbackNode ArmsCallbackNode;

struct ArmsCallbackNode {
  ArmsCallbackNode* next;
  void (*onPreMark)(Arcadia_Thread*, bool);
  void (*onVisit)(Arcadia_Thread*);
  void (*onFinalize)(Arcadia_Thread*, size_t*);
};

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

/// @brief The type of a reference counter.
typedef uint32_t ReferenceCount;

/// @brief The minimum value of a reference counter.
#define ReferenceCount_Minimum (UINT32_C(0))

/// @brief The maximum value of a reference counter.
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

/// @brief Increment a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return the new reference count value
static inline ReferenceCount ReferenceCount_increment(ReferenceCount* referenceCount) {
  return ++(*referenceCount);
}

/// @brief Decrement a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return the new reference count value
static inline ReferenceCount ReferenceCount_decrement(ReferenceCount* referenceCount) {
  return --(*referenceCount);
}

struct Arcadia_Thread {
  Arcadia_Status status;
  Arcadia_JumpTarget* jumpTarget;
  struct {
    Arcadia_Value* elements;
    Arcadia_SizeValue size;
    Arcadia_SizeValue capacity;
  } stack;
  // Weak reference to the process object which owns this thread object.
  // When the thread is constructed, this is NULL.
  // The constructing process assigns itself to this variable after the thread is constructed.
  Arcadia_Process* process1;
};

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
static void
Arcadia_Thread_initializeValueStack
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
static void
Arcadia_Thread_uninitializeValueStack
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
static void
Arcadia_Thread_initialize
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an initialized Arcadia_Thread object*/
static void
Arcadia_Thread_uninitialize
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an initialized Arcadia_Thread object*/
static void
Arcadia_Thread_increaseValueStackCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue additionalCapacity
  );

static void
Arcadia_Thread_ensureValueStackFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_Thread_initializeValueStack
  (
    Arcadia_Thread* thread
  )
{ 
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &thread->stack.elements, sizeof(Arcadia_Value) * 8)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0; i < 8; ++i) {
    thread->stack.elements[i] = Arcadia_Value_Initializer();
  }
  thread->stack.size = 0;
  thread->stack.capacity = 8;
}

static void
Arcadia_Thread_uninitializeValueStack
  (
    Arcadia_Thread* thread
  )
{
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), thread->stack.elements);
  thread->stack.elements = NULL;
}

static void
Arcadia_Thread_initialize
  (
    Arcadia_Thread* thread
  )
{
  thread->process1 = NULL;
  thread->status = Arcadia_Status_Success;
  thread->jumpTarget = NULL;
  Arcadia_Thread_initializeValueStack(thread);
}

static void
Arcadia_Thread_uninitialize
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Thread_uninitializeValueStack(thread);
  thread->jumpTarget = NULL;
  thread->status = Arcadia_Status_Success;
  thread->process1 = NULL;
}

static void
Arcadia_Thread_increaseValueStackCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue additionalCapacity
  )  
{
  static const Arcadia_SizeValue maximumCapacity = Arcadia_SizeValue_Maximum / sizeof(Arcadia_Value);
  static const Arcadia_SizeValue desiredAdditionalCapacity = 64;
  Arcadia_SizeValue oldCapacity = thread->stack.capacity;
  if (maximumCapacity - oldCapacity < additionalCapacity) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue maximumAdditionalCapacity = maximumCapacity - oldCapacity;
  // We want to grow in steps of desiredAdditionalCapacity.
  if (additionalCapacity < desiredAdditionalCapacity && maximumAdditionalCapacity >= desiredAdditionalCapacity) {
    additionalCapacity = desiredAdditionalCapacity;
  }

  Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
  if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), &thread->stack.elements, newCapacity * sizeof(Arcadia_Value))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = oldCapacity; i < newCapacity; ++i) {
    thread->stack.elements[i] = Arcadia_Value_Initializer();
  }
  thread->stack.capacity = newCapacity;
}

static void
Arcadia_Thread_ensureValueStackFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue availableFreeCapacity = thread->stack.capacity - thread->stack.size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    Arcadia_Thread_increaseValueStackCapacity(thread, requiredFreeCapacity - availableFreeCapacity);
  }
}

Arcadia_SizeValue
Arcadia_Thread_getValueStackSize
  (
    Arcadia_Thread* thread
  )
{ return thread->stack.size; }

void
Arcadia_Thread_pushValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  Arcadia_Thread_ensureValueStackFreeCapacity(thread, 1);
  thread->stack.elements[thread->stack.size] = *value;
  thread->stack.size++;
}

void
Arcadia_Thread_popValues
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue count
  )
{
  if (count < thread->stack.size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  thread->stack.size -= count;
}

void
Arcadia_Thread_pushJumpTarget
  (
    Arcadia_Thread* thread,
    Arcadia_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = thread->jumpTarget;
  thread->jumpTarget = jumpTarget;
}

void
Arcadia_Thread_popJumpTarget
  (
    Arcadia_Thread* thread
  )
{
  thread->jumpTarget = thread->jumpTarget->previous;
}

Arcadia_NoReturn() void
Arcadia_Thread_jump
  (
    Arcadia_Thread* thread
  )
{ 
  longjmp(thread->jumpTarget->environment, -1);
}

Arcadia_Status
Arcadia_Thread_getStatus
  (
    Arcadia_Thread* thread
  )
{ return thread->status; }

void
Arcadia_Thread_setStatus
  (
    Arcadia_Thread* thread,
    Arcadia_Status status
  )
{ thread->status = status; }

Arcadia_Process*
Arcadia_Thread_getProcess
  (
    Arcadia_Thread* thread
  )
{ return thread->process1; }

struct Arcadia_Process {
  ReferenceCount referenceCount;
  Arcadia_Thread thread;
  ArmsCallbackNode* armsCallbackNodes;
};

static Arcadia_Process* g_process = NULL;

Arcadia_Thread*
Arcadia_Process_getThread
  (
    Arcadia_Process* process
  )
{ return &process->thread; }

Arcadia_ProcessStatus
Arcadia_Process_acquire
  (
    Arcadia_Process* process
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
Arcadia_Process_relinquish
  (
    Arcadia_Process* process
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
    shutdownModules(process);
    Arcadia_Thread_uninitialize(&process->thread);
    Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), g_process);
    g_process = NULL;
    if (Arms_shutdown()) {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
    }
  }
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process_get
  (
    Arcadia_Process** process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (!g_process) {
    if (Arms_startup()) {
      return Arcadia_ProcessStatus_EnvironmentFailed;
    }
    if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &g_process, sizeof(Arcadia_Process))) {
      if (Arms_shutdown()) {
        Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    Arcadia_Thread_initialize(&g_process->thread);
    g_process->armsCallbackNodes = NULL;
    g_process->thread.process1 = g_process;
    
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(&g_process->thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      startupModules(g_process);
      Arcadia_Thread_popJumpTarget(&g_process->thread);
    } else {
      Arcadia_Thread_popJumpTarget(&g_process->thread);
      shutdownModules(g_process);
      Arcadia_Thread_uninitialize(&g_process->thread);
      Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), g_process);
      g_process = NULL;
      if (Arms_shutdown()) {
        Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
      return Arcadia_ProcessStatus_AllocationFailed;
    }
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
Arcadia_Process_fillMemory
  (
    Arcadia_Process* process,
    void* p,
    size_t n,
    uint8_t v
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  memset(p, v, n);
}

void
Arcadia_Process_copyMemory
  (
    Arcadia_Process* process,
    void* p,
    const void* q,
    size_t n
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p) || UINTPTR_MAX - n < ((uintptr_t)q)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
                  && (((uintptr_t)q) <= ((uintptr_t)p) + n);
  if (!overlapping) {
    memmove(p, q, n);
  } else {
    memcpy(p, q, n);
  }
}

int
Arcadia_Process_compareMemory
  (
    Arcadia_Process* process,
    const void* p,
    const void* q,
    size_t n
  )
{
  if (!p || !q) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  return memcmp(p, q, n);
}

void
Arcadia_Process_allocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{
  Arms_Status status = Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arms_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_deallocateUnmanaged
  (
    Arcadia_Process* process,
    void* p
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), p);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_reallocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arms_MemoryManager_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  if (object) {
    Arms_visit(object);
  }
}

Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
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
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
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
Arcadia_Process_stepArms
  (
    Arcadia_Process* process
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
Arcadia_Process_runArms
  (
    Arcadia_Process* process,
    bool purgeCaches
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arms_RunStatistics statistics = { .destroyed = 0 };
  do {
    for (ArmsCallbackNode* node = process->armsCallbackNodes; NULL != node; node = node->next) {
      if (node->onPreMark) {
        node->onPreMark(thread, purgeCaches);
      }
    }
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
    for (ArmsCallbackNode* node = process->armsCallbackNodes; NULL != node; node = node->next) {
      if (node->onFinalize) {
        size_t destroyed;
        node->onFinalize(thread, &destroyed);
        if (SIZE_MAX - destroyed < statistics.destroyed) {
          statistics.destroyed = SIZE_MAX;
        } else {
          statistics.destroyed += destroyed;
        }
      }
    }
  } while (statistics.destroyed > 0);
  return Arcadia_Status_Success;
}

void
Arcadia_Process_addArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = NULL;
  armsCallbackNode->onPreMark = callback;
  armsCallbackNode->onVisit = NULL;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onPreMark == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_addArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = NULL;
  armsCallbackNode->onPreMark = NULL;
  armsCallbackNode->onVisit = callback;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onVisit == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_addArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = callback;
  armsCallbackNode->onPreMark = NULL;
  armsCallbackNode->onVisit = NULL;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onFinalize == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_registerType
  (
    Arcadia_Process* process,
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
      case Arms_Status_TypeExists: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
    };
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_allocate
  (
    Arcadia_Process* process,
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arms_Status_AllocationFailed);
      } break;
      case Arms_Status_TypeNotExists: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arms_Status_TypeNotExists);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arms_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arms_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arms_Status_OperationInvalid);
      } break;
    };
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  *p = q;
}
