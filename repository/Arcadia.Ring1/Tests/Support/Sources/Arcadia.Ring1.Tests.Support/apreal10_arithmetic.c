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

#include "Arcadia.Ring1.Tests.Support/apreal10_arithmetic.h"

#include "Arcadia/Ring1/Support/apreal10.h"

static void
multiplicativeTestFixture
  (
    Arcadia_Thread* thread,
    const char* multiplier,
    const char* multiplicand,
    const char* product
  )
{
  size_t k = 0;
  apreal10 v[4];

  for (; k < 4; ++k) {
    if (apreal10_initialize(&v[k])) {
      goto Error;
    }
  }

  if (apreal10_from_literal(&v[0], multiplier, strlen(multiplier)) || apreal10_from_literal(&v[1], multiplicand, strlen(multiplicand)) || apreal10_from_literal(&v[2], product, strlen(product))) {
    goto Error;
  }

  // v[3] := v[0] * v[1]
  if (apreal10_copy(&v[3], &v[0])) {
    goto Error;
  }
  if (apreal10_multiply(&v[3], &v[1])) {
    goto Error;
  }
  int result;
  if (apreal10_compare(&result, &v[3], &v[2])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }

  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

static void
additiveTestFixture
  (
    Arcadia_Thread* thread,
    const char *augend,
    const char *addend,
    const char *sum
  )
{
  size_t k = 0;
  apreal10 v[4];

  for (; k < 4; ++k) {
    if (apreal10_initialize(&v[k])) {
      goto Error;
    }
  }

  if (apreal10_from_literal(&v[0], augend, strlen(augend)) || apreal10_from_literal(&v[1], addend, strlen(addend)) || apreal10_from_literal(&v[2], sum, strlen(sum))) {
    goto Error;
  }

  // v[3] := v[0] + v[1]
  if (apreal10_copy(&v[3], &v[0])) {
    goto Error;
  }
  if (apreal10_add(&v[3], &v[1])) {
    goto Error;
  }
  int result;
  if (apreal10_compare(&result, &v[3], &v[2])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }

  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_Ring1_Tests_Support_apreal10_arithmetic
  (
    Arcadia_Thread* thread
  )
{
  multiplicativeTestFixture(thread, "0", "0",    "0");
  multiplicativeTestFixture(thread, "0", "+1",   "0");
  multiplicativeTestFixture(thread, "+1", "0",   "0");
  multiplicativeTestFixture(thread, "+1", "+1", "+1");

  additiveTestFixture(thread, "+1.0", "+0.2", "+1.2");
  additiveTestFixture(thread, "+1.0", "-0.2", "+0.8");
  additiveTestFixture(thread, "-1.0", "+1.0", "0");
}
