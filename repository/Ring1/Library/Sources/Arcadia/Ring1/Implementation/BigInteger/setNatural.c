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
#include "Arcadia/Ring1/Implementation/BigInteger/setNatural.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_BigInteger_setNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!other) {
    Arcadia_BigInteger_setZero(thread, self);
    return;
  } else {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * 1);
    self->limps[0] = other;
    self->numberOfLimps = 1;
    self->sign = 1;
  }
}

void
Arcadia_BigInteger_setNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!other) {
    Arcadia_BigInteger_setZero(thread, self);
    return;
  } else {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * 1);
    self->limps[0] = other;
    self->numberOfLimps = 1;
    self->sign = 1;
  }
}

void
Arcadia_BigInteger_setNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BigInteger_Limp hi = (other & 0xffffffff0000ffff) >> 32;
  Arcadia_BigInteger_Limp lo = (other & 0x00000000ffffffff) >> 0;
  if (hi) {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * 2);
    self->limps[1] = hi;
    self->limps[0] = lo;
    self->numberOfLimps = 2;
  } else {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * 1);
    self->limps[0] = lo;
    self->numberOfLimps = 1;
  }
  self->sign = other ? +1 : 0;
}

void
Arcadia_BigInteger_setNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!other) {
    Arcadia_BigInteger_setZero(thread, self);
  } else {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * 1);
    self->limps[0] = other;
    self->numberOfLimps = 1;
    self->sign = 1;
  }
}
