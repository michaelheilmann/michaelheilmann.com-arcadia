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

// Last modified: 2024-08-27

#include <stdlib.h>

#include "Arcadia/Ring2/Include.h"
#include "Arcadia.Ring2.Tests.Utf8/read.h"
#include "Arcadia.Ring2.Tests.Utf8/readWrite.h"

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_Tests_Utf8_read1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Tests_Utf8_readWrite1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
