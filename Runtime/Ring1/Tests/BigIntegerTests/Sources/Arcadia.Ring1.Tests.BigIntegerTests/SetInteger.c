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

#include "Arcadia.Ring1.Tests.BigIntegerTests/SetInteger.h"

// Regression
static void
regressionTest1
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value value
  )
{
  Arcadia_BigInteger* a = Arcadia_BigInteger_create(thread),
                    * b = Arcadia_BigInteger_create(thread);
  if (Arcadia_Integer8Value_Minimum <= value && value <= Arcadia_Integer8Value_Maximum) {
    Arcadia_BigInteger_setInteger8(thread, a, (Arcadia_Integer8Value)value);
  } else if (Arcadia_Integer16Value_Minimum <= value && value <= Arcadia_Integer16Value_Maximum) {
    Arcadia_BigInteger_setInteger16(thread, a, (Arcadia_Integer16Value)value);
  } else if (Arcadia_Integer32Value_Minimum <= value && value <= Arcadia_Integer32Value_Maximum) {
    Arcadia_BigInteger_setInteger32(thread, a, (Arcadia_Integer32Value)value);
  } else {
    Arcadia_BigInteger_setInteger64(thread, a, (Arcadia_Integer64Value)value);
  }
  Arcadia_BigInteger_setInteger64(thread, b, value);
  Arcadia_Tests_assertTrue(thread, value == Arcadia_BigInteger_toInteger64(thread, a) && value == Arcadia_BigInteger_toInteger64(thread, b));
}

void
Arcadia_Ring1_Tests_BigInteger_setIntegerOperations
  (
    Arcadia_Thread* thread
  )
{
  regressionTest1(thread,  0);

  regressionTest1(thread, +1);
  regressionTest1(thread, -1);

  regressionTest1(thread, +2);
  regressionTest1(thread, -2);

  regressionTest1(thread, Arcadia_Integer8Value_Minimum);
  regressionTest1(thread, Arcadia_Integer8Value_Maximum);

  regressionTest1(thread, Arcadia_Integer16Value_Minimum);
  regressionTest1(thread, Arcadia_Integer16Value_Maximum);

  regressionTest1(thread, Arcadia_Integer32Value_Minimum);
  regressionTest1(thread, Arcadia_Integer32Value_Maximum);

  regressionTest1(thread, Arcadia_Integer64Value_Minimum);
  regressionTest1(thread, Arcadia_Integer64Value_Maximum);
}
