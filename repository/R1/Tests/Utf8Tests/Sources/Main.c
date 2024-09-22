// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R.h"
#include "read.h"
#include "readWrite.h"

static bool safeExecute(void (*f)()) {
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)();
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
  if (status) {
    result = false;
  }
  return result;
}

static void R1_Tests_Utf8_readWrite1() {
  R1_Tests_Utf8_readWrite("abc", sizeof("abc") - 1);
  R1_Tests_Utf8_readWrite("xyz", sizeof("xyz") - 1);
}

int main(int argc, char **argv) {
  if (!safeExecute(&R1_Tests_Utf8_read1)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&R1_Tests_Utf8_readWrite1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
