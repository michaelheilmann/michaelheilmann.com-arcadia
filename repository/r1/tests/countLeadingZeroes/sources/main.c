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

#include "r.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

static void countLeadingZeroesTests() {
#define Do(SUFFIX, TYPE, VALUE, EXPECTED) \
  { \
    R_SizeValue expected = EXPECTED; \
    R_SizeValue received = R_countLeadingZeroes_##SUFFIX(VALUE); \
    R_Test_assert(received == expected); \
  }
  Do(n64, R_Natural64, R_Natural64Value_Literal(0), R_SizeValue_Literal(56) + R_SizeValue_Literal(8));
  Do(n64, R_Natural64, R_Natural64Value_Literal(1), R_SizeValue_Literal(56) + R_SizeValue_Literal(7));
  Do(n64, R_Natural64, R_Natural64Value_Literal(2), R_SizeValue_Literal(56) + R_SizeValue_Literal(6));
  Do(n64, R_Natural64, R_Natural64Value_Literal(3), R_SizeValue_Literal(56) + R_SizeValue_Literal(6));
  Do(n64, R_Natural64, R_Natural64Value_Literal(4), R_SizeValue_Literal(56) + R_SizeValue_Literal(5));
  Do(n64, R_Natural64, R_Natural64Value_Maximum,    R_SizeValue_Literal(0));

  Do(n32, R_Natural32, R_Natural32Value_Literal(0), R_SizeValue_Literal(24) + R_SizeValue_Literal(8));
  Do(n32, R_Natural32, R_Natural32Value_Literal(1), R_SizeValue_Literal(24) + R_SizeValue_Literal(7));
  Do(n32, R_Natural32, R_Natural32Value_Literal(2), R_SizeValue_Literal(24) + R_SizeValue_Literal(6));
  Do(n32, R_Natural32, R_Natural32Value_Literal(3), R_SizeValue_Literal(24) + R_SizeValue_Literal(6));
  Do(n32, R_Natural32, R_Natural32Value_Literal(4), R_SizeValue_Literal(24) + R_SizeValue_Literal(5));
  Do(n32, R_Natural32, R_Natural32Value_Maximum,    R_SizeValue_Literal(0));

  Do(n16, R_Natural16, R_Natural16Value_Literal(0), R_SizeValue_Literal(8) + R_SizeValue_Literal(8));
  Do(n16, R_Natural16, R_Natural16Value_Literal(1), R_SizeValue_Literal(8) + R_SizeValue_Literal(7));
  Do(n16, R_Natural16, R_Natural16Value_Literal(2), R_SizeValue_Literal(8) + R_SizeValue_Literal(6));
  Do(n16, R_Natural16, R_Natural16Value_Literal(3), R_SizeValue_Literal(8) + R_SizeValue_Literal(6));
  Do(n16, R_Natural16, R_Natural16Value_Literal(4), R_SizeValue_Literal(8) + R_SizeValue_Literal(5));
  Do(n16, R_Natural32, R_Natural16Value_Maximum,    R_SizeValue_Literal(0));

  Do(n8, R_Natural8, R_Natural8Value_Literal(0),    R_SizeValue_Literal(8));
  Do(n8, R_Natural8, R_Natural8Value_Literal(1),    R_SizeValue_Literal(7));
  Do(n8, R_Natural8, R_Natural8Value_Literal(2),    R_SizeValue_Literal(6));
  Do(n8, R_Natural8, R_Natural8Value_Literal(3),    R_SizeValue_Literal(6));
  Do(n8, R_Natural8, R_Natural8Value_Literal(4),    R_SizeValue_Literal(5));
  Do(n8, R_Natural8, R_Natural8Value_Maximum,       R_SizeValue_Literal(0));

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
  if (!safeExecute(&countLeadingZeroesTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
