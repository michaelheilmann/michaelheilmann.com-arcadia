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

#include "Arcadia.Ring1.Tests.RealTypes/realTypes.h"

void
Arcadia_Ring1_Tests_RealTypes_real32
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Tests_assertTrue(thread, Arcadia_Real32Value_NumberOfExplicitSignificandBits == 23);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real32Value_SignificandBitsMask == 0b11111111111111111111111);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real32Value_ExponentBitsMask == 0b1111111100000000000000000000000);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real32Value_SignBitsMask == 0b10000000000000000000000000000000);
}

void
Arcadia_Ring1_Tests_RealTypes_real64
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Tests_assertTrue(thread, Arcadia_Real64Value_NumberOfExplicitSignificandBits == 52);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real64Value_SignificandBitsMask == 0b1111111111111111111111111111111111111111111111111111);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real64Value_ExponentBitsMask == 0b111111111110000000000000000000000000000000000000000000000000000);
  Arcadia_Tests_assertTrue(thread, Arcadia_Real64Value_SignBitsMask == 0b1000000000000000000000000000000000000000000000000000000000000000);
}
