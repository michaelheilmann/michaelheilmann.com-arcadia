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
#include "Arcadia/Ring1/Implementation/Memory.h"

#include "Arcadia/Arms/Include.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include "Arcadia/Ring1/Implementation/Thread.private.h"
#include <stdbool.h>
#include <string.h>

void
Arcadia_Memory_fill
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n,
    uint8_t v
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  memset(p, v, n);
}

void
Arcadia_Memory_copy
  (
    Arcadia_Thread* thread,
    void* p,
    const void* q,
    size_t n
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p) || UINTPTR_MAX - n < ((uintptr_t)q)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
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

Arcadia_Integer8Value
Arcadia_Memory_compare
  (
    Arcadia_Thread* thread,
    const void* p,
    const void* q,
    Arcadia_SizeValue n
  )
{
  if (!p || !q) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return memcmp(p, q, n);
}

void*
Arcadia_Memory_allocateUnmanaged
  (
    Arcadia_Thread* thread,
    size_t n
  )
{
  void* q = NULL;
  Arcadia_Arms_MemoryManager_Status status = Arcadia_Arms_MemoryManager_allocate(Arcadia_Arms_getDefaultMemoryManager(), &q, n);
  if (status) {
    if (status == Arcadia_Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arcadia_Arms_MemoryManager_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(thread);
  }
  return q;
}

void
Arcadia_Memory_deallocateUnmanaged
  (
    Arcadia_Thread* thread,
    void* p
  )
{
  Arcadia_Arms_MemoryManager_Status status = Arcadia_Arms_MemoryManager_deallocate(Arcadia_Arms_getDefaultMemoryManager(), p);
  if (status) {
    if (status == Arcadia_Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Memory_reallocateUnmanaged
  (
    Arcadia_Thread* thread,
    void** p,
    size_t n
  )
{
  Arcadia_Arms_MemoryManager_Status status = Arcadia_Arms_MemoryManager_reallocate(Arcadia_Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arcadia_Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arcadia_Arms_MemoryManager_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Memory_reverseMemory16
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural16Value* front = p;
    Arcadia_Natural16Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural16Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Memory_reverseMemory32
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural32Value* front = p;
    Arcadia_Natural32Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural32Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Memory_reverseMemory64
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural64Value* front = p;
    Arcadia_Natural64Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural64Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Memory_reverseMemory8
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural8Value* front = p;
    Arcadia_Natural8Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural8Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Memory_swap
  (
    Arcadia_Thread* thread,
    void* p,
    void* q,
    size_t n
  )
{
  Arcadia_Natural8Value* p0 = (Arcadia_Natural8Value*)p,
                       * q0 = (Arcadia_Natural8Value*)q;
  for (size_t i = 0; i < n; ++i) {
    Arcadia_Natural8Value temporary = *p0;
    *p0 = *q0;
    *q0 = temporary;
    p0++;
    q0++;
  }
}
