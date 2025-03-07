// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-02-17

#include "Arcadia.Ring1.Tests.Support/ieee754.h"

#include <stdlib.h>
#include "Arcadia/Ring1/Support/ieee754.h"

static void
testFloatConstants
  (
    Arcadia_Thread* thread
  );

static void
testDoubleConstants
  (
    Arcadia_Thread* thread
  );

static void
testFloatConstants
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Tests_assertTrue(thread, FLT_SIGNIFICAND_BITS == 23);
  Arcadia_Tests_assertTrue(thread, FLT_SIGNIFICAND_MASK == 0b11111111111111111111111);
  Arcadia_Tests_assertTrue(thread, FLT_EXPONENT_MASK == 0b1111111100000000000000000000000);
  Arcadia_Tests_assertTrue(thread, FLT_SIGN_MASK == 0b10000000000000000000000000000000);
}

static void
testDoubleConstants
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Tests_assertTrue(thread, DBL_SIGNIFICAND_BITS == 52);
  Arcadia_Tests_assertTrue(thread, DBL_SIGNIFICAND_MASK == 0b1111111111111111111111111111111111111111111111111111);
  Arcadia_Tests_assertTrue(thread, DBL_EXPONENT_MASK == 0b111111111110000000000000000000000000000000000000000000000000000);
  Arcadia_Tests_assertTrue(thread, DBL_SIGN_MASK == 0b1000000000000000000000000000000000000000000000000000000000000000);
}

void
Arcadia_Ring1_Tests_Support_ieee754
  (
    Arcadia_Thread* thread
  )
{
  testFloatConstants(thread);
  testDoubleConstants(thread);
}
