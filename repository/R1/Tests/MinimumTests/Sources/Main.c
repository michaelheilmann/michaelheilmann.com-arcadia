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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "R.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

static void
minimumTests
  (
  )
{
#define Do(Type) \
  R_Test_assert(R_##Type##Value_Minimum == R_minimum##Type##Value(R_##Type##Value_Minimum, R_##Type##Value_Maximum)); \
  R_Test_assert(R_##Type##Value_Minimum == R_minimum##Type##Value(R_##Type##Value_Maximum, R_##Type##Value_Minimum)); \
  R_Test_assert(R_##Type##Value_Minimum == R_minimum##Type##Value(R_##Type##Value_Literal(0), R_##Type##Value_Minimum)); \
  R_Test_assert(R_##Type##Value_Minimum == R_minimum##Type##Value(R_##Type##Value_Minimum, R_##Type##Value_Literal(0)));

  Do(Integer8);
  Do(Integer16);
  Do(Integer32);
  Do(Integer64);

  Do(Natural8);
  Do(Natural16);
  Do(Natural32);
  Do(Natural64);

  Do(Size);

#undef Do
}

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

int main(int argc, char **argv) {
  if (!safeExecute(&minimumTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
