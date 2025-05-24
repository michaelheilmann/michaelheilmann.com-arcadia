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
#include "Arcadia/Ring1/Implementation/BigInteger/toNatural.h"

#include "Arcadia/Ring1/Include.h"

#define isZero(thread, self) ((self)->limps[0] == 0 && (self)->numberOfLimps == 1)

Arcadia_Natural16Value
Arcadia_BigInteger_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  Arcadia_Natural64Value v = Arcadia_BigInteger_toNatural64(thread, self);
  if (v > Arcadia_Natural16Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Natural16Value)v;
}

Arcadia_Natural32Value
Arcadia_BigInteger_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  Arcadia_Natural64Value v = Arcadia_BigInteger_toNatural64(thread, self);
  if (v > Arcadia_Natural32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Natural32Value)v;
}

Arcadia_Natural64Value
Arcadia_BigInteger_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (isZero(thread, self)) {
    return Arcadia_Natural64Value_Literal(0);
  }
  if (self->numberOfLimps > 2) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural64Value v = 0;
  for (size_t i = self->numberOfLimps; i > 0; --i) {  // This loop is executed exactly one times or two times.
    v <<= 32;
    v += ((Arcadia_Natural64Value)self->limps[i - 1]);
  }

  if (self->sign == -1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  } else {
    return v;
  }
}

Arcadia_Natural64Value
Arcadia_BigInteger_toNatural64WithTruncation
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BooleanValue* truncated
  )
 {
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (isZero(thread, self)) {
    *truncated = Arcadia_BooleanValue_False;
    return Arcadia_Natural64Value_Literal(0);
  }
  if (self->sign == -1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue truncatedLimps = self->numberOfLimps > 2 ?  self->numberOfLimps - 2 : 0;
  *truncated = truncatedLimps;
  Arcadia_Natural64Value v = 0;
  for (size_t i = self->numberOfLimps; i > truncatedLimps; --i) {  // This loop is executed exactly one times or two times.
    v <<= 32;
    v += ((Arcadia_Natural64Value)self->limps[i - 1]);
  }
  if (self->sign == -1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  } else {
    return v;
  }
}

Arcadia_Natural8Value
Arcadia_BigInteger_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  Arcadia_Natural64Value v = Arcadia_BigInteger_toNatural64(thread, self);
  if (v > Arcadia_Natural8Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Natural8Value)v;
}
