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
#include "Arcadia/Ring1/Implementation/Thread.private.h"

#include "Arcadia/ARMS/Include.h"

void
Arcadia_Thread_initializeValueStack
  (
    Arcadia_Thread* thread
  )
{
  if (Arcadia_ARMS_MemoryManager_allocate(Arcadia_ARMS_getDefaultMemoryManager(), &thread->stack.elements, sizeof(Arcadia_Value) * 8)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0; i < 8; ++i) {
    thread->stack.elements[i] = Arcadia_Value_Initializer();
  }
  thread->stack.size = 0;
  thread->stack.capacity = 8;
}

void
Arcadia_Thread_uninitializeValueStack
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ARMS_MemoryManager_deallocate(Arcadia_ARMS_getDefaultMemoryManager(), thread->stack.elements);
  thread->stack.elements = NULL;
}

void
Arcadia_Thread_initialize
  (
    Arcadia_Thread* thread
  )
{
  thread->process = NULL;
  thread->status = Arcadia_Status_Success;
  thread->jumpTarget = NULL;
  Arcadia_Thread_initializeValueStack(thread);
}

void
Arcadia_Thread_uninitialize
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Thread_uninitializeValueStack(thread);
  thread->jumpTarget = NULL;
  thread->status = Arcadia_Status_Success;
  thread->process = NULL;
}

void
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
  if (Arcadia_ARMS_MemoryManager_reallocate(Arcadia_ARMS_getDefaultMemoryManager(), &thread->stack.elements, newCapacity * sizeof(Arcadia_Value))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = oldCapacity; i < newCapacity; ++i) {
    thread->stack.elements[i] = Arcadia_Value_Initializer();
  }
  thread->stack.capacity = newCapacity;
}

void
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
