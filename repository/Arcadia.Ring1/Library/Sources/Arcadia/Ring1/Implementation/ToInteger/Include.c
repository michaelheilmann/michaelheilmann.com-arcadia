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

// Last modified: 2025-03-07

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ToInteger/Include.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/NumberLiteral.h"

Arcadia_Integer16Value
Arcadia_toInteger16
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  Arcadia_Integer64Value v = Arcadia_toInteger64(thread, p, n);
  if (v < Arcadia_Integer16Value_Minimum && v > Arcadia_Integer16Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Integer16Value)v;
}


Arcadia_Integer32Value
Arcadia_toInteger32
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  Arcadia_Integer64Value v = Arcadia_toInteger64(thread, p, n);
  if (v < Arcadia_Integer32Value_Minimum && v > Arcadia_Integer32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Integer32Value)v;
}

Arcadia_Integer64Value
Arcadia_toInteger64
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  Arcadia_NumberLiteral numberLiteral;
  if (!Arcadia_parseNumberLiteral(thread, &numberLiteral, p, n)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  if (numberLiteral.significand.radixPoint.length != 0 && numberLiteral.exponent.length != 0) {
    // Radix point is not allowed. Exponent is not allowed
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue negative = numberLiteral.significand.sign.length ? '-' == p[numberLiteral.significand.sign.start] : Arcadia_BooleanValue_False;
  Arcadia_Natural64Value v = Arcadia_Natural64Value_Literal(0);
  Arcadia_SizeValue i = Arcadia_SizeValue_Literal(0),
                    m = Arcadia_SizeValue_Literal(0);
  for (;
       m < 19 && i < numberLiteral.significand.integral.length - numberLiteral.significand.integral.leadingZeroes.length;
       ++i, ++m) {
    v = v * Arcadia_Natural64Value_Literal(10) + (p[numberLiteral.significand.integral.start + numberLiteral.significand.integral.leadingZeroes.length + i] - '0');
  }
  if (i < numberLiteral.significand.integral.length - numberLiteral.significand.integral.leadingZeroes.length) {
    // This loop is unlikely to be reached and is not supposed to be executed frequently unless in adversary cases.
    for (;
         i < numberLiteral.significand.integral.length - numberLiteral.significand.integral.leadingZeroes.length;
         ++i, ++m) {
      Arcadia_Natural64Value high;
      Arcadia_safeMultiplyNatural64Value(thread, v, 10, &high, &v);
      if (high) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_safeAddNatural64Value(thread, v, (p[numberLiteral.significand.integral.start + numberLiteral.significand.integral.leadingZeroes.length + i] - '0'), &high, &v);
      if (high) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
    }
  }
  if (negative && v == ((Arcadia_Natural64Value)Arcadia_Integer64Value_Maximum) + Arcadia_Natural64Value_Literal(1)) {
    // The magnitude of Arcadia_Integer64Value_Minimum is not representable by an Arcadia_Integer64Value.
    // Consequently, we cannot simply do ((Arcadia_Integer64Value)v) Arcadia_Integer64Value_Literal(-1).
    return Arcadia_Integer64Value_Minimum;
  }
  if (v > ((Arcadia_Natural64Value)Arcadia_Integer64Value_Maximum)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer64Value w = (Arcadia_Integer64Value)v;
  if (negative) {
    w *= Arcadia_Integer64Value_Literal(-1);
  }
  return w;
}

Arcadia_Integer8Value
Arcadia_toInteger8
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  Arcadia_Integer64Value v = Arcadia_toInteger64(thread, p, n);
  if (v < Arcadia_Integer8Value_Minimum && v > Arcadia_Integer8Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Integer8Value)v;
}
