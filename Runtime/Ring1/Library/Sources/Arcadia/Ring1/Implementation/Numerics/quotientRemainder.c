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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Numerics/quotientRemainder.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_quotientRemainderInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value dividend,
    Arcadia_Integer16Value divisor,
    Arcadia_Integer16Value* quotient,
    Arcadia_Integer16Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
     Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderIntegerl32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value dividend,
    Arcadia_Integer32Value divisor,
    Arcadia_Integer32Value* quotient,
    Arcadia_Integer32Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value dividend,
    Arcadia_Integer64Value divisor,
    Arcadia_Integer64Value* quotient,
    Arcadia_Integer64Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value dividend,
    Arcadia_Integer8Value divisor,
    Arcadia_Integer8Value* quotient,
    Arcadia_Integer8Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value dividend,
    Arcadia_Natural16Value divisor,
    Arcadia_Natural16Value* quotient,
    Arcadia_Natural16Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value dividend,
    Arcadia_Natural32Value divisor,
    Arcadia_Natural32Value* quotient,
    Arcadia_Natural32Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value dividend,
    Arcadia_Natural64Value divisor,
    Arcadia_Natural64Value* quotient,
    Arcadia_Natural64Value* remainder
  )
{
  if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!divisor) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}

void
Arcadia_quotientRemainderNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value dividend,
    Arcadia_Natural8Value divisor,
    Arcadia_Natural8Value* quotient,
    Arcadia_Natural8Value* remainder
  )
{
 if (!quotient || !remainder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
 if (!divisor) {
   Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  *quotient = dividend / divisor;
  *remainder = dividend - (*quotient) * divisor;
}
