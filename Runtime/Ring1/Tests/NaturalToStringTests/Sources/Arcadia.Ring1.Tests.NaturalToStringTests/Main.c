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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"

static void
testFixture
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value v
  )
{
  Arcadia_ImmutableUtf8String* u = Arcadia_ImmutableUtf8String_createFromNatural64(thread, v);
  Arcadia_Natural64Value w = Arcadia_ImmutableUtf8String_toNatural64(thread, u);
  Arcadia_Tests_assertTrue(thread, v == w);
}

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  testFixture(thread, Arcadia_Natural64Value_Minimum);
  testFixture(thread, Arcadia_Natural64Value_Maximum);
  testFixture(thread, Arcadia_Natural64Value_Literal(0));
  testFixture(thread, Arcadia_Natural64Value_Literal(1));
  testFixture(thread, Arcadia_Natural64Value_Literal(123));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
