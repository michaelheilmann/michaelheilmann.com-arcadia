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
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"

// integers from -2^53 to +2^53 can be exactly represented.
static void
testFixtureInteger64ToStringToReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value value
  )
{
  char buffer[19 + 2];
  snprintf(buffer, 19 + 1, "%"PRId64, value);
  Arcadia_Real64Value v = Arcadia_toReal64(thread, buffer, strlen(buffer));
  Arcadia_Tests_assertTrue(thread, value == v);
}

// integers from -2^53 to +2^53 can be exactly represented.
static void
safeRangeTests
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Integer64Value minimum = -9007199254740992;
  Arcadia_Integer64Value maximum = +9007199254740992;

  testFixtureInteger64ToStringToReal64(thread, minimum);
  testFixtureInteger64ToStringToReal64(thread, maximum);
  testFixtureInteger64ToStringToReal64(thread, Arcadia_Integer64Value_Literal(0));
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
#define On(Text) \
  testFixtureStringToReal64(thread, Text); \

  On(u8"0");
  On(u8"00");
  On(u8"0.5e-20");
  On(u8"1"); // works with gay if clinger & lemire disabled
  On(u8"+1e+309"); // works with gay if clinger & lemire disabled, infinity
  On(u8"-1e+309"); // works with gay if clinger & lemire disabled, infinity
  On(u8"-1.0"); // works with gay if clinger & lemire disabled, -1.0
  On(u8"0e-325"); // works with gay if clinger & lemire disabled
  On(u8"1e-309"); // slow path
  On(u8"9007199254740992"); // works with gay if clinger & lemire disabled
  On(u8"1.e1000"); // works with gay if clinger & lemire disabled, infinity
  On(u8"5.4e-309");
  On(u8"5.4702222260027245111818947e-309");
  On(u8"2.2250738585072013e-308"); // fast path
  On(u8"1.00000000000000188558920870223463870174566020691753515394643550663070558368373221972569761144603605635692374830246134201063722058e-309"); // slow path

  // Typical values from data files.
  On(u8"0.5"); On(u8"-0.5"); On(u8"+0.5");

#undef On
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&safeRangeTests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
