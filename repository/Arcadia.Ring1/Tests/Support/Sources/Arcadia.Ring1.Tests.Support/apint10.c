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

#include "Arcadia.Ring1.Tests.Support/apint10.h"

#include <stdlib.h>
#include "Arcadia/Ring1/Support/apint10.h"

static void
additionTestFixture
  (
    Arcadia_Process* process,
    int64_t x,
    int64_t y,
    int64_t z
  )
{
  apint10 a, b, c;
  if (apint10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_initialize(&b)) {
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_initialize(&c)) {
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  if (apint10_from_int64(&a, x) || apint10_from_int64(&b, y) || apint10_from_int64(&c, z)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_add(&a, &b)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  int result;
  if (apint10_compare(&result, &a, &c)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  apint10_uninitialize(&c);
  apint10_uninitialize(&b);
  apint10_uninitialize(&a);
}

static void
multiplicationTestFixture
  (
    Arcadia_Process* process,
    int64_t x,
    int64_t y,
    int64_t z
  ) 
{
  apint10 a, b, c;
  if (apint10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_initialize(&b)) {
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_initialize(&c)) {
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  if (apint10_from_int64(&a, x) || apint10_from_int64(&b, y) || apint10_from_int64(&c, z)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_multiply(&a, &b)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  int result;
  if (apint10_compare(&result, &a, &c)) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    apint10_uninitialize(&c);
    apint10_uninitialize(&b);
    apint10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  apint10_uninitialize(&c);
  apint10_uninitialize(&b);
  apint10_uninitialize(&a);
}

static void
testAddition
  (
    Arcadia_Process* process
  )
{
  additionTestFixture(process,  0,  0,  0); // TODO: Test negative zero and positive zero combinations.

  additionTestFixture(process,  0, +1, +1);
  additionTestFixture(process, +1,  0, +1);
  additionTestFixture(process, +1, +1, +2);

  additionTestFixture(process,  0, -1, -1);
  additionTestFixture(process, -1,- 0, -1);
  additionTestFixture(process, -1, -1, -2);
}

static void
testMultiplication
  (
    Arcadia_Process* process
  )
{
  multiplicationTestFixture(process, 0, 0, 0); // TODO: Test negative zero and positive zero combinations.
  multiplicationTestFixture(process, 0, +1, 0);
  multiplicationTestFixture(process, 0, -1, 0);
  multiplicationTestFixture(process, +1, 0, 0);
  multiplicationTestFixture(process, -1, 0, 0);
  multiplicationTestFixture(process, -1, -1, +1);
  multiplicationTestFixture(process, -1, +1, -1);
  multiplicationTestFixture(process, +1, -1, -1);
  multiplicationTestFixture(process, +1, +1, +1);

  multiplicationTestFixture(process, +3, +7, +21);
  multiplicationTestFixture(process, +3, -7, -21);
  multiplicationTestFixture(process, -3, +7, -21);
  multiplicationTestFixture(process, -3, -7, +21);
}

void
Arcadia_Ring1_Tests_Support_apint10
  (
    Arcadia_Process* process
  )
{
  testAddition(process);
  testMultiplication(process);
}
