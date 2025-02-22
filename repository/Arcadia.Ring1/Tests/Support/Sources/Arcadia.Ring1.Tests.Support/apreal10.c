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

#include "Arcadia.Ring1.Tests.Support/apreal10.h"

#include "Arcadia/Ring1/Support/apreal10.h"

// enable faspath standard condition
// values: 0 ~ disabled, 1 ~ enabled
#define FASTPATH1 (1)
// enable fastpath refined condition if fastpath standard condition is enabled as well
// values: 0 ~ disabled, 1 ~ enabled
#define FASTPATH2 (1)

// the fast path
// (1) if the significand is zero, then the result is zero.
// (2.1 - fastpath standard condition)
//     the result can be computed using normal precision arithmetic for apreal10 which are exactly representable by double (float).
//     An apreal10 is exactly representable by a double (float) if both the following criteria are fulfilled:
//     (2.1.1) The significand's magnitude is 15 (7) or fewer decimal digits.
//     (2.2.1) The exponent's magnitude is 10^0 to 10^22 (10^0 to 10^10).
// (2.2 - fastpath refined condition)
//     the result can be computed using normal precision arithmetic for apreal10 which are exactly representable by double (float).
//     An apreal10 is exactly representable by a double (float) if both the following criteria are fulfilled:
//     (2.2.1) The significand's magnitude is 15 (7) or fewer decimal digits.
//     (2.2.2) The exponent is in the range from 0 to 22+n (0 to 10+n) where n is 15 minus the number of significand digits (7 minus the number of significand digits).
// Some references:
// - https://www.exploringbinary.com/fast-path-decimal-to-floating-point-conversion/
// - https://portal.ampl.com/~dmg/netlib/fp/
// - https://en.wikipedia.org/wiki/Double-precision_floating-point_format
// - https://en.wikipedia.org/wiki/Single-precision_floating-point_format
// - https://github.com/openjdk/jdk/blob/5cbd9d1fe19b6d9516233cd1ed8d3ba340b7a1e6/src/java.base/share/classes/jdk/internal/math/FloatingDecimal.java#L1404C22-L1404C32
static bool
apreal10_to_dbl_fast
  (
    apreal10* a,
    double* pResult
  )
{
  static const double POW10[] = {
    1.0e0,  1.0e1,  1.0e2,  1.0e3,
    1.0e4,  1.0e5,  1.0e6,  1.0e7,
    1.0e8,  1.0e9,  1.0e10, 1.0e11,
    1.0e12, 1.0e13, 1.0e14, 1.0e15,
    1.0e16, 1.0e17, 1.0e18, 1.0e19,
    1.0e20, 1.0e21, 1.0e22,
  };
  bool bResult;
  // (1)
  if (apint10_is_zero(&bResult, &a->significand)) {
    *pResult = 0.;
    return true;
  }
  // (2)
#if defined(FASTPATH1) && 1 == FASTPATH1
  if (a->significand.size <= 15) {
    // If the exponent does not fit into an int32_t and the significand does not fit into int64_t,
    // then this path will not work out anyway.
    int32_t e;
    if (apint10_to_int32(&e, &a->exponent)) {
      return false;
    }
    int64_t sigi;
    if (apint10_to_int64(&sigi, &a->significand)) {
      return false;
    }
    double sigf = (double)sigi;
    if (-22 <= e && e <= +22) {
      // 2.1
      if (e < 0) {
        sigf /= POW10[-e];
      } else {
        sigf *= POW10[+e];
      }
      *pResult = sigf;
      return true;
    }
  #if defined(FASTPATH2) && 1 == FASTPATH2
    else if (e >= 0) {
      // 2.2
      int32_t shift = 15 - a->significand.size;
      if (e <= 22 + shift) {
        sigf *= POW10[shift];
        sigf *= POW10[e - shift];
        return true;
      }
    }
  #endif
  }
#endif
  return false;
}

static bool
apreal10_to_flt_fast
  (
    apreal10* a,
    float* pResult
  )
{
  static const float POW10[] = {
    1.0e0f,  1.0e1,  1.0e2,  1.0e3,
    1.0e4f,  1.0e5,  1.0e6,  1.0e7,
    1.0e8f,  1.0e9,  1.0e10,
  };
  bool bResult;
  // (1)
  if (apint10_is_zero(&bResult, &a->significand)) {
    *pResult = 0.f;
    return true;
  }
  // (2)
#if defined(FASTPATH1) && 1 == FASTPATH1
  if (a->significand.size <= 7) {
    // If the exponent does not fit into an int16_t and the significand does not fit into int32_t,
    // then this path will not work out anyway.
    int16_t e;
    if (apint10_to_int16(&e, &a->exponent)) {
      return false;
    }
    int32_t sigi;
    if (apint10_to_int32(&sigi, &a->significand)) {
      return false;
    }
    float sigf = (float)sigi;
    if (e >= -10 && e <= +10) {
      // 2.1
      if (e < 0) {
        sigf /= POW10[-e];
      } else {
        sigf *= POW10[+e];
      }
      *pResult = sigf;
      return true;
    } 
#if defined(FASTPATH2) && 1 == FASTPATH2
    else if (e >= 0) {
      // 2.2
      int32_t shift = 7 - a->significand.size;
      if (e <= 10 + shift) {
        sigf *= POW10[shift];
        sigf *= POW10[e - shift];
        *pResult = sigf;
        return true;
      }
    }
#endif
  }
#endif
  return false;
}

static bool
apreal10_to_dbl
  (
    apreal10* a,
    double* pResult
  )
{
  if (apreal10_to_dbl_fast(a, pResult)) {
    return true;
  }
  return false;
}

static bool
apreal10_to_flt
  (
    apreal10* a,
    float* pResult
  )
{
  if (apreal10_to_flt_fast(a, pResult)) {
    return true;
  }
  return false;
}

#include <stdio.h>

static void check_to_flt(Arcadia_Process* process, const char *literal) {
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apreal10_from_literal(&a, literal, strlen(literal))) {
    goto Error;
  }
  float af;
  if (!apreal10_to_flt(&a, &af)) {
    goto Error;
  }
  float bf;
  if (1 != sscanf(literal, "%f", &bf)) {
    goto Error;
  }
  if (af != bf) {
    goto Error;
  }
Success:
  apreal10_uninitialize(&a);
  return;
Error:
  apreal10_uninitialize(&a);
  Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
  Arcadia_Process_jump(process);
  return;
}

// test
// - from literal
static void
testFromLiteral
  (
    Arcadia_Process* process
  )
{
  float f;
  bool booleanResult;
  apreal10 a; apint10 shiftExp;
  if (apreal10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apint10_initialize(&shiftExp)) {
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    check_to_flt(process, u8"36e-1");  // path 2.1
    check_to_flt(process, u8"36e+1");  // path 2.1
    check_to_flt(process, u8"36e-10"); // path 2.1 (corner case for float)
    check_to_flt(process, u8"36e+10"); // path 2.1 (corner case for float)
    check_to_flt(process, u8"36e+15"); // path 2.2 (corner case for float)
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    goto Error;
  }

  // |a.sign| != 0 hence a < 0 or a > 0.
  // if |a| > 1 then repeatedly divde by 10 until 0 < |a| < 1.
  // We determine if 0 < |a| < 1 by the following rule:
  // if |a.sig|>0 then
  //  a.exp <= -l(a.sig) <=> 0< |a| < 1
  while (true) {
    int64_t threshold = -(int64_t)a.significand.size;
    bool result;
    if (apint10_lower_than_int64(&result, &a.exponent, threshold)) {
      goto Error;
    }
    if (result) {
      break;
    }
    if (apreal10_divide_p10_uint64(&a, 1)) {
      goto Error;
    }
  }
Success:
  apint10_uninitialize(&shiftExp);
  apreal10_uninitialize(&a);
  return;
Error:
  apint10_uninitialize(&shiftExp);
  apreal10_uninitialize(&a);
  Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
  Arcadia_Process_jump(process);
  return;
}

// test
// - initialize and
// - set i64
static void
testFromI64
  (
    Arcadia_Process* process
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  for (size_t i = 0; i < 63; ++i) {
    int64_t v = INT64_C(1) << i;
    if (apreal10_from_uint64(&a, v)) {
      apreal10_uninitialize(&a);
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
  }
  apreal10_uninitialize(&a);
}


// test
// - initialize and
// - set u64
static void
testFromU64
  (
    Arcadia_Process* process
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  for (size_t i = 0; i < 63; ++i) {
    uint64_t v = UINT64_C(1) << i;
    if (apreal10_from_uint64(&a, v)) {
      apreal10_uninitialize(&a);
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
  }
  apreal10_uninitialize(&a);
}

// test
// - 0 << 3 = 0
// - 0 >> 3 = 0
static void
testShift
  (
    Arcadia_Process* process
  )
{
  size_t k = 0;
  apreal10 v[2];
  for (; k < 2; ++k) {
    if (apreal10_initialize(&v[k])) {
      goto Error;
    }
  }
  if (apreal10_from_int64(&v[0], 0)) {
    goto Error;
  }
  if (apreal10_from_int64(&v[1], 0)) {
    goto Error;
  }

  int result;

  // 0 << 3 = 0
  if (apreal10_multiply_p10_uint64(&v[0], 3)) {
    goto Error;
  }
  if (apreal10_compare(&result, &v[0], &v[1])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }

  // 0 >> 3 = 0
  if (apreal10_divide_p10_uint64(&v[0], 3)) {
    goto Error;
  }
  if (apreal10_compare(&result, &v[0], &v[1])) {
    goto Error;
  }
  if (result) {
    goto Error;
  }

Success:
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
  Arcadia_Process_jump(process);
}

// test
// - set i64 and
// - copy
static void
testCopy
  (
    Arcadia_Process* process
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apreal10_from_int64(&a, INT64_MAX)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (apreal10_copy(&b, &a)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  int result;
  if (apreal10_compare(&result, &a, &b)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (result) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}

void
Arcadia_Ring1_Tests_Support_apreal10
  (
    Arcadia_Process* process
  )
{
  testFromU64(process);
  testFromI64(process);
  testFromLiteral(process);
  testCopy(process);
  testShift(process);

}
