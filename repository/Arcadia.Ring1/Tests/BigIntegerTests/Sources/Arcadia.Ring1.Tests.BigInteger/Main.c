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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"
#include "Arcadia.Ring1.Tests.BigInteger/Additive.h"
#include "Arcadia.Ring1.Tests.BigInteger/Multiplicative.h"
#include "Arcadia.Ring1.Tests.BigInteger/PowersOf.h"
#include "Arcadia.Ring1.Tests.BigInteger/QuotientRemainder.h"
#include "Arcadia.Ring1.Tests.BigInteger/Relational.h"

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_BigInteger_additiveOperations)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_BigInteger_multiplicativeOperations)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_BigInteger_powersOfOperations)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_BigInteger_relationalOperations)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_BigInteger_quotientRemainderOperations)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
