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

#define EXPECT_SUCCESS(TYPE, FLAVOR, INPUT, OUTPUT) \
  { \
    R_##TYPE##Value x = R_nextPowerOfTwo##FLAVOR##TYPE##Value(INPUT); \
    R_##TYPE##Value y = OUTPUT; \
    if (x != y) { \
      R_setStatus(R_Status_TestFailed); \
      R_jump(); \
    } \
  }

#define EXPECT_FAILURE(TYPE, FLAVOR, INPUT) \
  { \
    R_JumpTarget jumpTarget; \
    R_pushJumpTarget(&jumpTarget); \
    if (R_JumpTarget_save(&jumpTarget)) { \
      R_nextPowerOfTwo##FLAVOR##TYPE##Value(INPUT); \
      R_popJumpTarget(); \
      R_setStatus(R_Status_TestFailed); \
      R_jump(); \
    } else { \
      if (R_getStatus() != R_Status_NotExists) { \
        R_popJumpTarget(); \
        R_setStatus(R_Status_TestFailed); \
        R_jump(); \
      } else { \
        R_setStatus(R_Status_Success); \
      } \
    } \
  }

static void nextPowerOfTwoNatural64ValueTests() {
  EXPECT_SUCCESS(Natural64, Gt, 0, 1);
  EXPECT_SUCCESS(Natural64, Gte, 0, 1);

  EXPECT_SUCCESS(Natural64, Gt, 1, 2);
  EXPECT_SUCCESS(Natural64, Gte, 1, 1);

  EXPECT_SUCCESS(Natural64, Gte, 2, 2);
  EXPECT_SUCCESS(Natural64, Gt, 2, 4);

  EXPECT_SUCCESS(Natural64, Gte, 3, 4);
  EXPECT_SUCCESS(Natural64, Gt, 3, 4);

  EXPECT_SUCCESS(Natural64, Gte, 4, 4);
  EXPECT_SUCCESS(Natural64, Gt, 4, 8);

  EXPECT_SUCCESS(Natural64, Gte, 5, 8);
  EXPECT_SUCCESS(Natural64, Gt, 5, 8);

  EXPECT_SUCCESS(Natural64, Gte, 6, 8);
  EXPECT_SUCCESS(Natural64, Gt, 6, 8);

  EXPECT_SUCCESS(Natural64, Gte, 7, 8);
  EXPECT_SUCCESS(Natural64, Gt, 7, 8);

  EXPECT_SUCCESS(Natural64, Gte, 8, 8);
  EXPECT_SUCCESS(Natural64, Gt, 8, 16);

  // ...

  EXPECT_FAILURE(Natural64, Gte, R_Natural64Value_Maximum - 1);
  EXPECT_FAILURE(Natural64, Gt, R_Natural64Value_Maximum - 1);

  EXPECT_FAILURE(Natural64, Gte, R_Natural64Value_Maximum - 0);
  EXPECT_FAILURE(Natural64, Gt, R_Natural64Value_Maximum - 0);
}

static void nextPowerOfTwoNatural32ValueTests() {
  EXPECT_SUCCESS(Natural32, Gte, 0, 1);
  EXPECT_SUCCESS(Natural32, Gt, 0, 1);

  EXPECT_SUCCESS(Natural32, Gte, 1, 1);
  EXPECT_SUCCESS(Natural32, Gt, 1, 2);

  EXPECT_SUCCESS(Natural32, Gte, 2, 2);
  EXPECT_SUCCESS(Natural32, Gt, 2, 4);

  EXPECT_SUCCESS(Natural32, Gte, 3, 4);
  EXPECT_SUCCESS(Natural32, Gt, 3, 4);

  EXPECT_SUCCESS(Natural32, Gte, 4, 4);
  EXPECT_SUCCESS(Natural32, Gt, 4, 8);

  EXPECT_SUCCESS(Natural32, Gte, 5, 8);
  EXPECT_SUCCESS(Natural32, Gt, 5, 8);

  EXPECT_SUCCESS(Natural32, Gte, 6, 8);
  EXPECT_SUCCESS(Natural32, Gt, 6, 8);

  EXPECT_SUCCESS(Natural32, Gte, 7, 8);
  EXPECT_SUCCESS(Natural32, Gt, 7, 8);

  EXPECT_SUCCESS(Natural32, Gte, 8, 8);
  EXPECT_SUCCESS(Natural32, Gt, 8, 16);

  // ...

  EXPECT_FAILURE(Natural32, Gte, R_Natural32Value_Maximum - 1);
  EXPECT_FAILURE(Natural32, Gt, R_Natural32Value_Maximum - 1);

  EXPECT_FAILURE(Natural32, Gte, R_Natural32Value_Maximum - 0);
  EXPECT_FAILURE(Natural32, Gt, R_Natural32Value_Maximum - 0);
}

static void nextPowerOfTwoNatural16ValueTests() {
  EXPECT_SUCCESS(Natural16, Gte, 0, 1);
  EXPECT_SUCCESS(Natural16, Gt, 0, 1);

  EXPECT_SUCCESS(Natural16, Gte, 1, 1);
  EXPECT_SUCCESS(Natural16, Gt, 1, 2);

  EXPECT_SUCCESS(Natural16, Gte, 2, 2);
  EXPECT_SUCCESS(Natural16, Gt, 2, 4);

  EXPECT_SUCCESS(Natural16, Gte, 3, 4);
  EXPECT_SUCCESS(Natural16, Gt, 3, 4);

  EXPECT_SUCCESS(Natural16, Gte, 4, 4);
  EXPECT_SUCCESS(Natural16, Gt, 4, 8);

  EXPECT_SUCCESS(Natural16, Gte, 5, 8);
  EXPECT_SUCCESS(Natural16, Gt, 5, 8);

  EXPECT_SUCCESS(Natural16, Gte, 6, 8);
  EXPECT_SUCCESS(Natural16, Gt, 6, 8);

  EXPECT_SUCCESS(Natural16, Gte, 7, 8);
  EXPECT_SUCCESS(Natural16, Gt, 7, 8);

  EXPECT_SUCCESS(Natural16, Gte, 8, 8);
  EXPECT_SUCCESS(Natural16, Gt, 8, 16);

  // ...

  EXPECT_FAILURE(Natural16, Gte, R_Natural16Value_Maximum - 1);
  EXPECT_FAILURE(Natural16, Gt, R_Natural16Value_Maximum - 1);

  EXPECT_FAILURE(Natural16, Gte, R_Natural16Value_Maximum - 0);
  EXPECT_FAILURE(Natural16, Gt, R_Natural16Value_Maximum - 0);
}

static void nextPowerOfTwoNatural8ValueTests() {
  EXPECT_SUCCESS(Natural8, Gte, 0, 1);
  EXPECT_SUCCESS(Natural8, Gt, 0, 1);

  EXPECT_SUCCESS(Natural8, Gte, 1, 1);
  EXPECT_SUCCESS(Natural8, Gt, 1, 2);

  EXPECT_SUCCESS(Natural8, Gte, 2, 2);
  EXPECT_SUCCESS(Natural8, Gt, 2, 4);

  EXPECT_SUCCESS(Natural8, Gte, 3, 4);
  EXPECT_SUCCESS(Natural8, Gt, 3, 4);

  EXPECT_SUCCESS(Natural8, Gte, 4, 4);
  EXPECT_SUCCESS(Natural8, Gt, 4, 8);

  EXPECT_SUCCESS(Natural8, Gte, 5, 8);
  EXPECT_SUCCESS(Natural8, Gt, 5, 8);

  EXPECT_SUCCESS(Natural8, Gte, 6, 8);
  EXPECT_SUCCESS(Natural8, Gt, 6, 8);

  EXPECT_SUCCESS(Natural8, Gte, 7, 8);
  EXPECT_SUCCESS(Natural8, Gt, 7, 8);

  EXPECT_SUCCESS(Natural8, Gte, 8, 8);
  EXPECT_SUCCESS(Natural8, Gt, 8, 16);

  // ...

  EXPECT_FAILURE(Natural8, Gte, R_Natural8Value_Maximum - 1);
  EXPECT_FAILURE(Natural8, Gt, R_Natural8Value_Maximum - 1);

  EXPECT_FAILURE(Natural8, Gte, R_Natural8Value_Maximum - 0);
  EXPECT_FAILURE(Natural8, Gt, R_Natural8Value_Maximum - 0);
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
  if (!safeExecute(&nextPowerOfTwoNatural64ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&nextPowerOfTwoNatural32ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&nextPowerOfTwoNatural16ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&nextPowerOfTwoNatural8ValueTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
