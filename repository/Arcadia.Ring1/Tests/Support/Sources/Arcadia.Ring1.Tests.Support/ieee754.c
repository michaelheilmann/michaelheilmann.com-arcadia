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
    Arcadia_Process * process
  );

static void
testDoubleConstants
  (
    Arcadia_Process* process
  );

static void
testFloatConstants
  (
    Arcadia_Process * process
  )
{
  Arcadia_Tests_assertTrue(FLT_FRAC_BITS == 23);
  Arcadia_Tests_assertTrue(FLT_FRAC_MASK == 0b11111111111111111111111);
  Arcadia_Tests_assertTrue(FLT_EXP_MASK == 0b1111111100000000000000000000000);
  Arcadia_Tests_assertTrue(FLT_SGN_MASK == 0b10000000000000000000000000000000);
}

static void
testDoubleConstants
  (
    Arcadia_Process* process
  )
{
  Arcadia_Tests_assertTrue(DBL_FRAC_BITS == 52);
  Arcadia_Tests_assertTrue(DBL_FRAC_MASK == 0b1111111111111111111111111111111111111111111111111111);
  Arcadia_Tests_assertTrue(DBL_EXP_MASK == 0b111111111110000000000000000000000000000000000000000000000000000);
  Arcadia_Tests_assertTrue(DBL_SGN_MASK == 0b1000000000000000000000000000000000000000000000000000000000000000);
}

void
Arcadia_Ring1_Tests_Support_ieee754
  (
    Arcadia_Process* process
  )
{
  testFloatConstants(process);
  testDoubleConstants(process);
}
