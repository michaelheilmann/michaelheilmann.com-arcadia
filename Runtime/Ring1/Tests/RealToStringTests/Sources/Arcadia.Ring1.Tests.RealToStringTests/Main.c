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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"

static void
testFixture32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value v
  )
{
  Arcadia_ImmutableUtf8String* u = Arcadia_ImmutableUtf8String_createFromReal32(thread, v);
  Arcadia_Real32Value w = Arcadia_ImmutableUtf8String_toReal32(thread, u);
  Arcadia_Tests_assertTrue(thread, v == w);
}

static void
testFixture64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value v
  )
{
  Arcadia_ImmutableUtf8String* u = Arcadia_ImmutableUtf8String_createFromReal64(thread, v);
  Arcadia_Real64Value w = Arcadia_ImmutableUtf8String_toReal64(thread, u);
  Arcadia_Tests_assertTrue(thread, v == w);
}

static void
testReal32
  (
    Arcadia_Thread* thread
  )
{
  testFixture32(thread, Arcadia_Real32Value_Minimum);
  testFixture32(thread, Arcadia_Real32Value_Maximum);
  testFixture32(thread, Arcadia_Real32Value_Literal(0.));
}

static void
testReal64
  (
    Arcadia_Thread* thread
  )
{
  testFixture64(thread, Arcadia_Real64Value_Minimum);
  testFixture64(thread, Arcadia_Real64Value_Maximum);
  testFixture64(thread, Arcadia_Real64Value_Literal(0.));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testReal32)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReal64)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
