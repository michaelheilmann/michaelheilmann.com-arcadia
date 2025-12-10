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
#include "Arcadia/Ring1/Implementation/BigInteger/toDecimalString.h"

#include "Arcadia/Ring1/Include.h"

// The maximum number of deciaml digits of which the value can be stored in an uint32_t is 9.
// We can also show this by simply observing its maximum value 4 294 967 295 which are 10 digits.
Arcadia_ImmutableUtf8String*
Arcadia_BigInteger_toDecimalString
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  )
{
  Arcadia_ImmutableUtf8StringValue string = NULL;
  size_t i = 0, n = 2;
  uint8_t* p = malloc(2);
  if (!p) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_BigInteger* quotient = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, quotient, self);
    if (Arcadia_BigInteger_isZero(thread, self)) {
      p[i++] = '0';
    } else {
      if (Arcadia_BigInteger_isNegative(thread, self)) {
        p[i++] = '-';
        Arcadia_BigInteger_multiplyInteger8(thread, quotient, Arcadia_Integer8Value_Literal(-1));
      } else {
        /*Nothing to do here.*/
      }
      Arcadia_SizeValue firstDigitIndex = i;
      Arcadia_BigInteger* TEN = Arcadia_BigInteger_create(thread);
      Arcadia_BigInteger_setNatural8(thread, TEN, Arcadia_Natural8Value_Literal(10));
      Arcadia_BigInteger* remainder = Arcadia_BigInteger_create(thread);
      do {
        Arcadia_BigInteger_divide3(thread, quotient, TEN, quotient, remainder);
        Arcadia_Natural8Value digitValue = Arcadia_BigInteger_toNatural8(thread, remainder) + '0';
        if (i == n) {
          Arcadia_SizeValue a, b;
          if (!Arcadia_safeMultiplySizeValue(thread, n, 2, &a, &b)) {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
            Arcadia_Thread_jump(thread);
          }
          Arcadia_Memory_reallocateUnmanaged(thread, &p, b);
          n = b;
        }
        p[i++] = digitValue;
      } while (!Arcadia_BigInteger_isZero(thread, quotient));
      Arcadia_SizeValue numberOfDigits = i - firstDigitIndex;
      Arcadia_Memory_reverseMemory8(thread, p + firstDigitIndex, numberOfDigits);
    }
    string = Arcadia_ImmutableUtf8String_create(thread, p, i);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(p);
    p = NULL;
    Arcadia_Thread_jump(thread);
  }
  free(p);
  p = NULL;
  return string;
}
