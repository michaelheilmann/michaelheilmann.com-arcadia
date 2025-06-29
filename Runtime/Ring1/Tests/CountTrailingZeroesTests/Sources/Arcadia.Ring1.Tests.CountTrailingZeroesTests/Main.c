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

#include "Arcadia/Ring1/Include.h"

static void
countTrailingZeroesTests
  (
    Arcadia_Thread* thread
  )
{
#define Do(Type, VALUE, EXPECTED) \
  { \
    Arcadia_SizeValue expected = EXPECTED; \
    Arcadia_SizeValue received = Arcadia_countTrailingZeroes##Type##Value(thread, VALUE); \
    Arcadia_Tests_assertTrue(thread, received == expected); \
  }
  Do(Natural64, Arcadia_Natural64Value_Literal(0), Arcadia_SizeValue_Literal(64));
  Do(Natural64, Arcadia_Natural64Value_Literal(1), Arcadia_SizeValue_Literal(0));
  Do(Natural64, Arcadia_Natural64Value_Literal(2), Arcadia_SizeValue_Literal(1));
  Do(Natural64, Arcadia_Natural64Value_Literal(3), Arcadia_SizeValue_Literal(0));
  Do(Natural64, Arcadia_Natural64Value_Literal(4), Arcadia_SizeValue_Literal(2));
  Do(Natural64, Arcadia_Natural64Value_Maximum,    Arcadia_SizeValue_Literal(0));

  Do(Natural32, Arcadia_Natural32Value_Literal(0), Arcadia_SizeValue_Literal(32));
  Do(Natural32, Arcadia_Natural32Value_Literal(1), Arcadia_SizeValue_Literal(0));
  Do(Natural32, Arcadia_Natural32Value_Literal(2), Arcadia_SizeValue_Literal(1));
  Do(Natural32, Arcadia_Natural32Value_Literal(3), Arcadia_SizeValue_Literal(0));
  Do(Natural32, Arcadia_Natural32Value_Literal(4), Arcadia_SizeValue_Literal(2));
  Do(Natural32, Arcadia_Natural32Value_Maximum,    Arcadia_SizeValue_Literal(0));

  Do(Natural16, Arcadia_Natural16Value_Literal(0), Arcadia_SizeValue_Literal(16));
  Do(Natural16, Arcadia_Natural16Value_Literal(1), Arcadia_SizeValue_Literal(0));
  Do(Natural16, Arcadia_Natural16Value_Literal(2), Arcadia_SizeValue_Literal(1));
  Do(Natural16, Arcadia_Natural16Value_Literal(3), Arcadia_SizeValue_Literal(0));
  Do(Natural16, Arcadia_Natural16Value_Literal(4), Arcadia_SizeValue_Literal(2));
  Do(Natural16, Arcadia_Natural16Value_Maximum,    Arcadia_SizeValue_Literal(0));

  Do(Natural8, Arcadia_Natural8Value_Literal(0),   Arcadia_SizeValue_Literal(8));
  Do(Natural8, Arcadia_Natural8Value_Literal(1),   Arcadia_SizeValue_Literal(0));
  Do(Natural8, Arcadia_Natural8Value_Literal(2),   Arcadia_SizeValue_Literal(1));
  Do(Natural8, Arcadia_Natural8Value_Literal(3),   Arcadia_SizeValue_Literal(0));
  Do(Natural8, Arcadia_Natural8Value_Literal(4),   Arcadia_SizeValue_Literal(2));
  Do(Natural8, Arcadia_Natural8Value_Maximum,      Arcadia_SizeValue_Literal(0));

#undef Do
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&countTrailingZeroesTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
