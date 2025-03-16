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
  self->limps[0] = other;
  self->numberOfLimps = 1;
  self->sign = other ? +1 : 0;
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
  self->limps[0] = other;
  self->numberOfLimps = 1;
  self->sign = other ? +1 : 0;
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
  Hidden(BigInteger_Limp) hi = (other & 0xffffffff0000ffff) >> 32;
  Hidden(BigInteger_Limp) lo = (other & 0x00000000ffffffff) >> 0;
  if (hi) {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Hidden(BigInteger_Limp)) * 2);
    self->limps[1] = hi;
    self->limps[0] = lo;
    self->numberOfLimps = 2;
  } else {
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
  self->limps[0] = other;
  self->numberOfLimps = 1;
  self->sign = other ? +1 : 0;
}
