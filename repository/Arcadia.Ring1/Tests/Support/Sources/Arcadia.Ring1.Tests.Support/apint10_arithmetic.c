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

// Last modified: 2025-02-17

#include "Arcadia.Ring1.Tests.Support/apint10_arithmetic.h"

#include <stdlib.h>
#include "Arcadia/Ring1/Support/apint10.h"

static void
additionTestFixture
  (
    Arcadia_Thread* thread,
    int64_t x,
    int64_t y,
    int64_t z
  )
{
  size_t k = 0;
  apint10 v[3];
  for (; k < 3; ++k) {
    if (apint10_initialize(&v[k])) {
      goto Error;
    }
  }
  if (apint10_from_int64(&v[0], x) || apint10_from_int64(&v[1], y) || apint10_from_int64(&v[2], z)) {
    goto Error;
  }
  if (apint10_add(&v[0], &v[1])) {
    goto Error;
  }
  int result;
  if (apint10_compare(&result, &v[0], &v[2])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }
Success:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

static void
multiplicationTestFixture
  (
    Arcadia_Thread* thread,
    int64_t x,
    int64_t y,
    int64_t z
  ) 
{
  size_t k = 0;
  apint10 v[3];
  for (; k < 3; ++k) {
    if (apint10_initialize(&v[k])) {
      goto Error;
    }
  }
  if (apint10_from_int64(&v[0], x) || apint10_from_int64(&v[1], y) || apint10_from_int64(&v[2], z)) {
    goto Error;
  }
  if (apint10_multiply(&v[0], &v[1])) {
    goto Error;
  }
  int result;
  if (apint10_compare(&result, &v[0], &v[2])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }
Success:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

static void
testAddition
  (
    Arcadia_Thread* thread
  )
{
  additionTestFixture(thread,  0,  0,  0); // TODO: Test negative zero and positive zero combinations.

  additionTestFixture(thread,  0, +1, +1);
  additionTestFixture(thread, +1,  0, +1);
  additionTestFixture(thread, +1, +1, +2);

  additionTestFixture(thread,  0, -1, -1);
  additionTestFixture(thread, -1,- 0, -1);
  additionTestFixture(thread, -1, -1, -2);

  additionTestFixture(thread, 10, -2, +8);
}

static void
testMultiplication
  (
    Arcadia_Thread* thread
  )
{
  multiplicationTestFixture(thread, 0, 0, 0); // TODO: Test negative zero and positive zero combinations.
  multiplicationTestFixture(thread, 0, +1, 0);
  multiplicationTestFixture(thread, 0, -1, 0);
  multiplicationTestFixture(thread, +1, 0, 0);
  multiplicationTestFixture(thread, -1, 0, 0);
  multiplicationTestFixture(thread, -1, -1, +1);
  multiplicationTestFixture(thread, -1, +1, -1);
  multiplicationTestFixture(thread, +1, -1, -1);
  multiplicationTestFixture(thread, +1, +1, +1);

  multiplicationTestFixture(thread, +3, +7, +21);
  multiplicationTestFixture(thread, +3, -7, -21);
  multiplicationTestFixture(thread, -3, +7, -21);
  multiplicationTestFixture(thread, -3, -7, +21);
}

void
Arcadia_Ring1_Tests_Support_apint10_arithmetic
  (
    Arcadia_Thread* thread
  )
{
  testAddition(thread);
  testMultiplication(thread);
}
