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

#define EXPECT_SUCCESS(TYPE, SUFFIX, FLAVOR, INPUT, OUTPUT) \
  { \
    TYPE##Value x = Arcadia_nextPowerOfTwo##FLAVOR##SUFFIX##Value(process, INPUT); \
    TYPE##Value y = OUTPUT; \
    if (x != y) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
      Arcadia_Process_jump(process); \
    } \
  }

#define EXPECT_FAILURE(TYPE, SUFFIX, FLAVOR, INPUT) \
  { \
    Arcadia_JumpTarget jumpTarget; \
    Arcadia_Process_pushJumpTarget(process, &jumpTarget); \
    if (Arcadia_JumpTarget_save(&jumpTarget)) { \
      Arcadia_nextPowerOfTwo##FLAVOR##SUFFIX##Value(process, INPUT); \
      Arcadia_Process_popJumpTarget(process); \
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
      Arcadia_Process_jump(process); \
    } else { \
      if (Arcadia_Process_getStatus(process) != Arcadia_Status_NotExists) { \
        Arcadia_Process_popJumpTarget(process); \
        Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
        Arcadia_Process_jump(process); \
      } else { \
        Arcadia_Process_setStatus(process, Arcadia_Status_Success); \
      } \
    } \
  }

static void
nextPowerOfTwoNatural64ValueTests
  (
    Arcadia_Process * process
  )
{
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 0, 1);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 0, 1);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 1, 2);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 1, 1);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 2, 2);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 2, 4);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 3, 4);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 3, 4);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 4, 4);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 4, 8);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 5, 8);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 5, 8);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 6, 8);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 6, 8);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 7, 8);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 7, 8);

  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, 8, 8);
  EXPECT_SUCCESS(Arcadia_Natural64, Natural64, GreaterThan, 8, 16);

  // ...

  EXPECT_FAILURE(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, Arcadia_Natural64Value_Maximum - 1);
  EXPECT_FAILURE(Arcadia_Natural64, Natural64, GreaterThan, Arcadia_Natural64Value_Maximum - 1);

  EXPECT_FAILURE(Arcadia_Natural64, Natural64, GreaterThanOrEqualTo, Arcadia_Natural64Value_Maximum - 0);
  EXPECT_FAILURE(Arcadia_Natural64, Natural64, GreaterThan, Arcadia_Natural64Value_Maximum - 0);
}

static void
nextPowerOfTwoNatural32ValueTests
  (
    Arcadia_Process* process
  )
{
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 0, 1);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 0, 1);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 1, 1);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 1, 2);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 2, 2);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 2, 4);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 3, 4);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 3, 4);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 4, 4);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 4, 8);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 5, 8);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 5, 8);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 6, 8);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 6, 8);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 7, 8);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 7, 8);

  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, 8, 8);
  EXPECT_SUCCESS(Arcadia_Natural32, Natural32, GreaterThan, 8, 16);

  // ...

  EXPECT_FAILURE(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, Arcadia_Natural32Value_Maximum - 1);
  EXPECT_FAILURE(Arcadia_Natural32, Natural32, GreaterThan, Arcadia_Natural32Value_Maximum - 1);

  EXPECT_FAILURE(Arcadia_Natural32, Natural32, GreaterThanOrEqualTo, Arcadia_Natural32Value_Maximum - 0);
  EXPECT_FAILURE(Arcadia_Natural32, Natural32, GreaterThan, Arcadia_Natural32Value_Maximum - 0);
}

static void
nextPowerOfTwoNatural16ValueTests
  (
    Arcadia_Process* process
  )
{
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 0, 1);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 0, 1);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 1, 1);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 1, 2);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 2, 2);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 2, 4);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 3, 4);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 3, 4);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 4, 4);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 4, 8);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 5, 8);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 5, 8);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 6, 8);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 6, 8);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 7, 8);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 7, 8);

  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, 8, 8);
  EXPECT_SUCCESS(Arcadia_Natural16, Natural16, GreaterThan, 8, 16);

  // ...

  EXPECT_FAILURE(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, Arcadia_Natural16Value_Maximum - 1);
  EXPECT_FAILURE(Arcadia_Natural16, Natural16, GreaterThan, Arcadia_Natural16Value_Maximum - 1);

  EXPECT_FAILURE(Arcadia_Natural16, Natural16, GreaterThanOrEqualTo, Arcadia_Natural16Value_Maximum - 0);
  EXPECT_FAILURE(Arcadia_Natural16, Natural16, GreaterThan, Arcadia_Natural16Value_Maximum - 0);
}

static void
nextPowerOfTwoNatural8ValueTests
  (
    Arcadia_Process* process
  )
{
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 0, 1);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 0, 1);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 1, 1);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 1, 2);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 2, 2);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 2, 4);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 3, 4);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 3, 4);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 4, 4);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 4, 8);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 5, 8);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 5, 8);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 6, 8);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 6, 8);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 7, 8);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 7, 8);

  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, 8, 8);
  EXPECT_SUCCESS(Arcadia_Natural8, Natural8, GreaterThan, 8, 16);

  // ...

  EXPECT_FAILURE(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, Arcadia_Natural8Value_Maximum - 1);
  EXPECT_FAILURE(Arcadia_Natural8, Natural8, GreaterThan, Arcadia_Natural8Value_Maximum - 1);

  EXPECT_FAILURE(Arcadia_Natural8, Natural8, GreaterThanOrEqualTo, Arcadia_Natural8Value_Maximum - 0);
  EXPECT_FAILURE(Arcadia_Natural8, Natural8, GreaterThan, Arcadia_Natural8Value_Maximum - 0);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&nextPowerOfTwoNatural64ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&nextPowerOfTwoNatural32ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&nextPowerOfTwoNatural16ValueTests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&nextPowerOfTwoNatural8ValueTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
