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
#include "Arcadia.Ring1.Tests.Support/ieee754.h"
#include "Arcadia.Ring1.Tests.Support/apint10.h"
#include "Arcadia/Ring1/Implementation/Utf8ToIeee754/Include.h"
#include "Arcadia/Ring1/Support/apint10.h"
#include "Arcadia/Ring1/Support/ieee754.h"

#if 0
static void
test_apint10_multiply_fixture
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
#endif

#if 0
static void
test_apint10
  (
    Arcadia_Process* process
  )
{
  test_apint10_multiply_fixture(process, 0,  0, 0);
  test_apint10_multiply_fixture(process, 0, +1, 0);
  test_apint10_multiply_fixture(process, 0, -1, 0);
  test_apint10_multiply_fixture(process, +1, 0, 0);
  test_apint10_multiply_fixture(process, -1, 0, 0);
  test_apint10_multiply_fixture(process, -1, -1, +1);
  test_apint10_multiply_fixture(process, -1, +1, -1);
  test_apint10_multiply_fixture(process, +1, -1, -1);
  test_apint10_multiply_fixture(process, +1, +1, +1);

  test_apint10_multiply_fixture(process, +3, +7, +21);
  test_apint10_multiply_fixture(process, +3, -7, -21);
  test_apint10_multiply_fixture(process, -3, +7, -21);
  test_apint10_multiply_fixture(process, -3, -7, +21);
}
#endif

#if 0
static void
testBigDecimal3
  (
    Arcadia_Process* process
  )
{
  big_decimal_t a, b;
  if (big_decimal_init(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_init(&b)) {
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  for (size_t i = 0; i < 63; ++i) {
    uint64_t v = 1 << i;
    if (big_decimal_set_u64(&a, v)) {
      big_decimal_uninit(&b);
      big_decimal_uninit(&a);
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    if (big_decimal_set_u64(&b, i)) {
      big_decimal_uninit(&b);
      big_decimal_uninit(&a);
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
  }

  big_decimal_uninit(&b);
  big_decimal_uninit(&a);
}
#endif

#if 0
// 0 << n = 0
// 0 >> n = 0
static void
testBigDecimal2
  (
    Arcadia_Process* process
  )
{
  big_decimal_t a, b;
  if (big_decimal_init(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_init(&b)) {
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_set_i64(&a, 0)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_set_i64(&b, 0)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  int result;

  // 0 << 3 = 0
  if (big_decimal_multiply_p10(&a, 3)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_compare(&result, &a, &b)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  // 0 >> 3 = 0
  if (big_decimal_divide_p10(&a, 3)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_compare(&result, &a, &b)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  big_decimal_uninit(&b);
  big_decimal_uninit(&a);
}
#endif

#if 0
// test "init", "set i64", and "copy"
static void
testBigDecimal1
  (
    Arcadia_Process* process
  )
{
  big_decimal_t a, b;
  if (big_decimal_init(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_init(&b)) {
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (big_decimal_set_i64(&a, INT64_MAX)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  } 
  if (big_decimal_copy(&b, &a)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  int result;
  if (big_decimal_compare(&result, &a, &b)) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    big_decimal_uninit(&b);
    big_decimal_uninit(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  big_decimal_uninit(&b);
  big_decimal_uninit(&a);
}
#endif

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_Support_ieee754)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_Ring1_Tests_Support_apint10)) {
    return EXIT_FAILURE;
  }
#if 0
  if (!Arcadia_Tests_safeExecute(&testBigDecimal1)) {
    return EXIT_FAILURE;
  }
#endif
#if 0
  if (!Arcadia_Tests_safeExecute(&testBigDecimal2)) {
    return EXIT_FAILURE;
  }
#endif
  return EXIT_SUCCESS;
}
