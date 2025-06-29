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

#include "Arcadia.Ring1.Tests.BigInteger/Shift.h"

static void
checkPowerOfTwo
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value v,
    Arcadia_Natural64Value p
  )
{
  Arcadia_BigInteger* temporary = NULL;
  Arcadia_BigInteger* bigIntegerValue = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, bigIntegerValue, v);

  Arcadia_BigInteger* bigIntegerShiftedValue = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, bigIntegerShiftedValue, bigIntegerValue);
  Arcadia_BigInteger_shiftLeftNatural64(thread, bigIntegerShiftedValue, p);

  temporary = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger* bigIntegerMultipliedValue = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfTwoNatural8(thread, temporary, p);
  Arcadia_BigInteger_multiply3(thread, bigIntegerMultipliedValue, bigIntegerValue, temporary);

  Arcadia_Tests_assertTrue(thread, Arcadia_BigInteger_equalTo(thread, bigIntegerShiftedValue, bigIntegerMultipliedValue));

  Arcadia_BigInteger* bigIntegerBackShiftedValue = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, bigIntegerBackShiftedValue, bigIntegerShiftedValue);
  Arcadia_BigInteger_shiftRightNatural64(thread, bigIntegerBackShiftedValue, p);
  Arcadia_Tests_assertTrue(thread, Arcadia_BigInteger_equalTo(thread, bigIntegerBackShiftedValue, bigIntegerValue));
}

void
Arcadia_Ring1_Tests_BigInteger_shiftOperations
  (
    Arcadia_Thread* thread
  )
{
  checkPowerOfTwo(thread, 1, 0);
  checkPowerOfTwo(thread, 1, 1);
  checkPowerOfTwo(thread, 1, 2);
  checkPowerOfTwo(thread, 1, 3);
  checkPowerOfTwo(thread, 1, 4);

  checkPowerOfTwo(thread, 1, 32);
  checkPowerOfTwo(thread, 1, 33);
  checkPowerOfTwo(thread, 1, 34);
  checkPowerOfTwo(thread, 1, 35);
  checkPowerOfTwo(thread, 1, 36);

  checkPowerOfTwo(thread, 1, 62);
  checkPowerOfTwo(thread, 1, 63);
  checkPowerOfTwo(thread, 1, 64);
  checkPowerOfTwo(thread, 1, 65);
  checkPowerOfTwo(thread, 1, 66);
}
