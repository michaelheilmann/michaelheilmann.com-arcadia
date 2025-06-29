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

#include "Arcadia.Ring1.Tests.BigInteger/And.h"

static void
testFixture
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value x,
    Arcadia_Integer64Value y,
    Arcadia_Integer64Value z
  )
{
  Arcadia_BigInteger* px = Arcadia_BigInteger_create(thread),
                    * py = Arcadia_BigInteger_create(thread),
                    * pz = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, px, x);
  Arcadia_BigInteger_setInteger64(thread, py, y);
  Arcadia_BigInteger_and3(thread, pz, px, py);
  Arcadia_Tests_assertTrue(thread, z == Arcadia_BigInteger_toInteger64(thread, pz));
}

void
Arcadia_Ring1_Tests_BigInteger_andOperations
  (
    Arcadia_Thread* thread
  )
{
#define Define(x,y, z) \
  testFixture(thread, Arcadia_Integer64Value_Literal(x), Arcadia_Integer64Value_Literal(y), Arcadia_Integer64Value_Literal(z));

  Define(0, 0, 0);
  Define(1, 0, 0);
  Define(0, 1, 0);
  Define(1, 1, 1);

  Define(2, 3, 2); // 2 ~ 10, 3 ~~ 11 => 2 & 3 ~ 2 
  Define(3, 2, 2);

#undef Define
}
