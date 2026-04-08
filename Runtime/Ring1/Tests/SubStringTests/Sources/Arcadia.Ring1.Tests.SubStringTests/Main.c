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

#include "Arcadia/Ring1/Include.h"
#include "Arcadia.Ring1.Tests.SubStringTests/findFirstOccurrenceTests.h"
#include "Arcadia.Ring1.Tests.SubStringTests/findLastOccurrenceTests.h"
#include "Arcadia.Ring1.Tests.SubStringTests/SubStringTests.h"

int
main
  (
    int argc,
    char **argv
  )
{
  //
  if (!Arcadia_Tests_safeExecute(&findFirstOccurrenceTests1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&findFirstOccurrenceTests2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&findFirstOccurrenceTests3)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&findLastOccurrenceTests1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&findLastOccurrenceTests2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&findLastOccurrenceTests3)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&subStringTests1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&subStringTests2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&subStringTests3)) {
    return EXIT_FAILURE;
  }
  //
  return EXIT_SUCCESS;
}
