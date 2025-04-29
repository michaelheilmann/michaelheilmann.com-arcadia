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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"
#include "Arcadia.Ring1.Tests.BigInteger/Additive.h"
#include "Arcadia.Ring1.Tests.BigInteger/Multiplicative.h"
#include "Arcadia.Ring1.Tests.BigInteger/PowersOf.h"
#include "Arcadia.Ring1.Tests.BigInteger/QuotientRemainder.h"
#include "Arcadia.Ring1.Tests.BigInteger/Relational.h"

// Regression.
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

// Regression.
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

// Regression.
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

// Regression.
static void
test4
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_BigInteger* a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_addInteger8(thread, a, 3);
  Arcadia_BigInteger_multiplyInteger8(thread, a, 10);
  uint64_t v = Arcadia_BigInteger_toNatural64(thread, a);
  Arcadia_Tests_assertTrue(thread, v == 30);
}

#include <string.h>

static void
test5
  (
    Arcadia_Thread* thread
  )
{
  char const* p = "9007199254740992";
  Arcadia_SizeValue n = strlen(p);
  Arcadia_BigInteger* p10 = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, p10, 10);
  Arcadia_BigInteger* v = Arcadia_BigInteger_create(thread);

  Arcadia_Natural64Value u1 = Arcadia_ImmutableUtf8String_toNatural64(thread, Arcadia_ImmutableUtf8String_create(thread, p, n));
  Arcadia_Natural64Value u2 = 0;
  for (Arcadia_SizeValue i = 0; i < n; ++i) {
    Arcadia_Natural8Value digit = ((Arcadia_Natural64Value)p[i]) - '0';
    u2 *= 10;
    u2 += digit;
    Arcadia_BigInteger_multiply(thread, v, p10);
    Arcadia_BigInteger_addNatural64(thread, v, digit);
  }
  Arcadia_Tests_assertTrue(thread, u1 == u2);
  Arcadia_Tests_assertTrue(thread, u1 == Arcadia_BigInteger_toNatural64(thread, v));
  Arcadia_BigInteger_toStdoutDebug(thread, v);
}

static void
test6
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_BigInteger* v = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, v, 1);
  Arcadia_BigInteger* p10 = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfTenNatural16(thread, p10, 309);
  Arcadia_BigInteger_multiply(thread, v, p10);
  Arcadia_BigInteger_toStdoutDebug(thread, v);
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
  if (!Arcadia_Tests_safeExecute(&test4)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test5)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test6)) {
    return EXIT_FAILURE;
  }
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
