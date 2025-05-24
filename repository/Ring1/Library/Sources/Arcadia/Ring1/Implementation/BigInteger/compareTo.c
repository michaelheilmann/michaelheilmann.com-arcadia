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
#include "Arcadia/Ring1/Implementation/BigInteger/compareTo.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_Integer8Value
Arcadia_BigInteger_compareTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  if (self->sign == other->sign) {
    switch (self->sign) {
      case +1: return Arcadia_BigInteger_compareByMagnitudeTo(thread, self, other);
      case -1: return Arcadia_BigInteger_compareByMagnitudeTo(thread, other, self);
      case  0: return 0;
    };
  }
  if (self->sign < other->sign) {
    // self is negative and other is zero or positive / self is zero and other is positive.
    return Arcadia_Integer8Value_Literal(-1);
  } else /*if (self->sign > other->sign)*/ {
    // other is negative and self is zero or positive / other is zero and self is positive.
    return Arcadia_Integer8Value_Literal(+1);
  }
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger16(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger32(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural16(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural64(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}

Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, otherBigInteger, other);
  return Arcadia_BigInteger_compareTo(thread, self, otherBigInteger);
}
