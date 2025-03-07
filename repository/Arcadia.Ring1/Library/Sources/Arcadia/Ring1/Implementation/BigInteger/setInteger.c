#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setInteger.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_BigInteger_setInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->limps[0] = other < 0 ? -(Arcadia_Integer32Value)other : other;
  self->numberOfLimps = 1;
  self->sign = other ? (other < 0 ? -1 : +1) : 0;
}

void
Arcadia_BigInteger_setInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->limps[0] = other < 0 ? -(Arcadia_Integer64Value)other : other;
  self->numberOfLimps = 1;
  self->sign = other ? (other < 0 ? -1 : +1) : 0;
}

void
Arcadia_BigInteger_setInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural64Value a;
  if (other < Arcadia_Integer64Value_Literal(0)) {
    if (other == Arcadia_Integer64Value_Minimum) {
      // We cannot just negate other as |INT64_MIN| = |INT64_MAX| - 1.
      // What we do is we take INT64_MAX as a natural64 value and add 1 to it.
      a = ((Arcadia_Natural64Value)Arcadia_Integer64Value_Maximum) + 1;
    } else {
      a = (Arcadia_Natural64Value)(-other);
    }
  } else {
    a = (Arcadia_Natural64Value)other;
  }
  Hidden(BigInteger_Limp) hi = (a & 0xffffffff0000ffff) >> 32;
  Hidden(BigInteger_Limp) lo = (a & 0x00000000ffffffff) >> 0;
  if (hi) {
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Hidden(BigInteger_Limp)) * 2);
    self->limps[1] = hi;
    self->limps[0] = lo;
    self->numberOfLimps = 2;
  } else {
    self->limps[0] = lo;
    self->numberOfLimps = 1;
  }
  self->sign = other ? (other < 0 ? -1 : +1) : 0;
}

void
Arcadia_BigInteger_setInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->limps[0] = other < 0 ? -(Arcadia_Integer16Value)other : other;
  self->numberOfLimps = 1;
  self->sign = other ? (other < 0 ? -1 : +1) : 0;
}
