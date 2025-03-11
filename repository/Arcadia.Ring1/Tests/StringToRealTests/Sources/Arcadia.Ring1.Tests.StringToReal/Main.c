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

#include <math.h>
#include <stdio.h>
#include <string.h>

// TODO: Move to big integer tests.
static void
test1
  (
    Arcadia_Thread* thread
  )
{
  int64_t u = INT64_C(9007199254740992);
  Arcadia_Tests_assertTrue(thread, u <= UINT64_MAX);
  Arcadia_Tests_assertTrue(thread, u <= INT64_MAX);
  Arcadia_BigInteger* bigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setDecimalDigits(thread, bigInteger, u8"9007199254740992", sizeof(u8"9007199254740992") - 1);
  int64_t v = Arcadia_BigInteger_toInteger64(thread, bigInteger);
  Arcadia_Tests_assertTrue(thread, u == v);
}

// TODO: Move to big integer tests.
static void
test2
  (
    Arcadia_Thread* thread
  )
{
  uint64_t u = UINT64_C(9007199254740992);
  Arcadia_Tests_assertTrue(thread, u <= UINT64_MAX);
  Arcadia_Tests_assertTrue(thread, u <= INT64_MAX);
  Arcadia_BigInteger* bigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setDecimalDigits(thread, bigInteger, u8"9007199254740992", sizeof(u8"9007199254740992") - 1);
  uint64_t v = Arcadia_BigInteger_toNatural64(thread, bigInteger);
  Arcadia_Tests_assertTrue(thread, u == v);
}

// TODO: Move to big integer tests.
static void
test3
  (
    Arcadia_Thread* thread
  )
{
  uint64_t u = UINT64_C(9007199254740992);
  Arcadia_Tests_assertTrue(thread, u <= UINT64_MAX);
  Arcadia_Tests_assertTrue(thread, u <= INT64_MAX);
  Arcadia_BigInteger* bigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setDecimalDigits(thread, bigInteger, u8"9007199254740992", sizeof(u8"9007199254740992") - 1);
  Arcadia_BooleanValue w;
  uint64_t v = Arcadia_BigInteger_toNatural64WithTruncation(thread, bigInteger, &w);
  Arcadia_Tests_assertTrue(thread, !w && u == v);
}

// Parses a strig into a real64 value using Arcadia.Ring1 functionality.
// Parses the same string into a real64 using sscanf.
// If both operations are successful and the results are equal, the test terminates with success. Otherwise it terminates with failure.
static void
testFixtureStringToReal64
  (
    Arcadia_Thread* thread,
    const char* p
  )
{
  Arcadia_Real64Value expected;
  if (1 != sscanf(p, "%lg", &expected)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Real64Value received = Arcadia_toReal64(thread, p, strlen(p));
  Arcadia_Tests_assertTrue(thread, expected == received);
}

static void
test
  (
    Arcadia_Thread* thread
  )
{
#define On(Text, Number) \
  testFixtureStringToReal64(thread, Text); \
  
  On(u8"0", 0.);
  On(u8"00", 0.);
  On(u8"9007199254740992", 9007199254740992.);
  On(u8"0e-325", 0.);
  On(u8"+1e+309", Arcadia_Real64Value_PositiveInfinity);
  On(u8"-1e+309", Arcadia_Real64Value_NegativeInfinity);
  On(u8"-1.0", -1.);
  On(u8"1.e1000", 1.e1000);

#undef On
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test3)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
