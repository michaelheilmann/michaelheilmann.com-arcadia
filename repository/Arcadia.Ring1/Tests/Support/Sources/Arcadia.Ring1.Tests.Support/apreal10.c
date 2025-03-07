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

#include <stdio.h>
#include <math.h>

// exact powers of ten, range from 0 to 23
static const double DBL_EXACT_POW10[] = {
  1.0e0,  1.0e1,  1.0e2,  1.0e3,
  1.0e4,  1.0e5,  1.0e6,  1.0e7,
  1.0e8,  1.0e9,  1.0e10, 1.0e11,
  1.0e12, 1.0e13, 1.0e14, 1.0e15,
  1.0e16, 1.0e17, 1.0e18, 1.0e19,
  1.0e20, 1.0e21, 1.0e22,
};

// exact powers of ten, range from 0 11
static const float FLT_EXACT_POW10[] = {
  1.0e0f,  1.0e1,  1.0e2,  1.0e3,
  1.0e4f,  1.0e5,  1.0e6,  1.0e7,
  1.0e8f,  1.0e9,  1.0e10,
};

// If we map a decimal float to a binary float then we map from x * 10^q to y * 2^p.
// But we have 10^q = 5^q * 2^q so effectively we are trying to match x * 2^q * 5^q to y * 2^p.
// The powers of two are not of our concern as they can be represented exactly using binary notation, only powers of five affect the binary significand.

// enable fastpath standard condition for IEEE754 double precision floating point values
// values: 0 ~ disabled, 1 ~ enabled
#define F64_FASTPATH1 (1)
// enable fastpath refined condition for IEEE754 double precision floating point values
// if fastpath standard condition is enabled as well
// values: 0 ~ disabled, 1 ~ enabled
#define F64_FASTPATH2 (1)
// the fastpath can be attempted if the number of decimal digits of the significand does not exceed this value
#define F64_FASTPATH_MAX_DECIMAL_DIGITS 15
// enable logic for "fast" testing of very long input strings.
#define F64_TRUNCATE_MANY_DIGITS (1)

// enable fastpath standard condition for IEEE754 single precision floating point values
// values: 0 ~ disabled, 1 ~ enabled
#define F32_FASTPATH1 (1)
// enable fastpath refined condition for IEEE754 single precision floating point values
// if fastpath standard condition is enabled as well
// values: 0 ~ disabled, 1 ~ enabled
#define F32_FASTPATH2 (1)
// the fastpath can be attempted if the number of decimal digits of the significand does not exceed this value
#define F32_FASTPATH_MAX_DECIMAL_DIGITS 7 
// enable logic for "fast" testing of very long input strings.
#define F32_TRUNCATE_MANY_DIGITS (1)

// (1) ~~~~~~~~~~ sanity check ~~~~~~~~~~
// (1.1) if the significand is zero, then the result is zero.
// (1.2) otherwise: if the exponent is smaller than -324 (-45) for double (float), then the result is zero.
//       -324 and -45 are the least decimal exponent values as specified at as described in [6].
//       WARNING: -324 and -45 can only be attained by denormalized numbers. These values are not provided by DBL_MIN_10_EXP and FLT_MIN_10_EXP as these symbolic constants pertain to normalized values.
// (1.3) otherwise: if the exponent is greater than +308 (+38) for double (float), then the result is infinity.
//       +308 and +38 are the greatest decimal exponent values as specified as described in [6].
//       These values are usually given by DBL_MAX_10_EXP and FLT_MAX_10_EXP.
// (2) ~~~~~~~~~~ the fast path ~~~~~~~~~~
// (2.1 - fastpath standard condition)
//     the result can be computed using normal precision arithmetic for apreal10 which are exactly representable by double (float).
//     An apreal10 is exactly representable by a double (float) if both the following criteria are fulfilled:
//     (2.1.1) The significand's magnitude is 15 (7) or fewer decimal digits.
//     (2.1.2) The exponent's magnitude is 10^0 to 10^22 (10^0 to 10^10).
//     This was described in [1].
// (2.2 - fastpath refined condition)
//     the result can be computed using normal precision arithmetic for apreal10 which are exactly representable by double (float).
//     An apreal10 is exactly representable by a double (float) if both the following criteria are fulfilled:
//     (2.2.1) The significand's magnitude is 15 (7) or fewer decimal digits.
//     (2.2.2) The exponent is in the range from 0 to 22+n (0 to 10+n) where n is 15 minus the number of significand digits (7 minus the number of significand digits).
//     This was described in [2].
// (3) ~~~~~~~~~~ the slow path ~~~~~~~~~~
// all your fears end up here
// 
// [1] William D. Clinger; 1990; "How to read floating point numbers accurately."; https://michaelheilmann.com/assets/references/clinger;1990.pdf
// [2] David M. Gay; 1990; "Correctly rounded binary-decimal and decimal-binary conversions."; https://michaelheilmann.com/assets/references/gay;1990.pdf
// [3] https://portal.ampl.com/~dmg/netlib/fp/
// [4] https://en.wikipedia.org/wiki/Double-precision_floating-point_format
// [5] https://en.wikipedia.org/wiki/Single-precision_floating-point_format
// [6] https://en.wikipedia.org/wiki/IEEE_754-1985#Range_and_precision
static bool
apreal10_to_dbl_fast
  (
    Arcadia_Thread* thread,
    apreal10* a,
    double* pResult
  )
{
  bool bResult;
  // (1)
  // (1.1)
  if (apint10_is_zero(&bResult, &a->significand)) {
    *pResult = 0.;
    return true;
  }
  // (1.2) (1.3)
  // A decimal exponent above 308 already yields infinity.
  // A decimal exponent below -324 already yields infinity.
  // Hence any valid exponent must fit into an int32_t anyway.
  int32_t e;
  if (apint10_to_int32(&e, &a->exponent)) {
    return false;
  }
  if (e < -324) {
    *pResult = a->significand.negative ? -0. : 0.;
    return true;
  } else if (e > 308) {
    *pResult = a->significand.negative ? -INFINITY : +INFINITY;
    return true;
  }

  // (2)
#if defined(F64_FASTPATH1) && 1 == F64_FASTPATH1
  if (a->significand.size <= F64_FASTPATH_MAX_DECIMAL_DIGITS) {
    int64_t sigi;
    if (apint10_to_int64(&sigi, &a->significand)) {
      return false;
    }
    double sigf = (double)sigi;
    if (-22 <= e && e <= +22) {
      // 2.1
      if (e < 0) {
        sigf /= DBL_EXACT_POW10[-e];
      } else {
        sigf *= DBL_EXACT_POW10[+e];
      }
      *pResult = sigf;
      return true;
    }
  #if defined(F64_FASTPATH2) && 1 == F64_FASTPATH2
    else if (e >= 0) {
      // 2.2
      int32_t shift = F64_FASTPATH_MAX_DECIMAL_DIGITS - a->significand.size;
      if (e <= 22 + shift) {
        sigf *= DBL_EXACT_POW10[shift];
        sigf *= DBL_EXACT_POW10[e - shift];
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
    Arcadia_Thread* thread,
    apreal10* a,
    float* pResult
  )
{

  bool bResult;
  // (1)
  if (apint10_is_zero(&bResult, &a->significand)) {
    *pResult = 0.f;
    return true;
  }
  // (1.2) (1.3)
  // A decimal exponent above -45 already yields infinity.
  // A decimal exponent below +38 already yields infinity.
  // Hence any valid exponent must fit into an int32_t anyway.
  int32_t e;
  if (apint10_to_int32(&e, &a->exponent)) {
    return false;
  }
  if (e < -45) {
    *pResult = a->significand.negative ? -0.f : +0.f;
    return true;
  } else if (e > 38) {
    *pResult = a->significand.negative ? -INFINITY : +INFINITY;
    return true;
  }

  // (2)
#if defined(F32_FASTPATH1) && 1 == F32_FASTPATH1
  if (a->significand.size <= F32_FASTPATH_MAX_DECIMAL_DIGITS) {
    // If the exponent does not fit into an int16_t and the significand does not fit into int32_t,
    // then this path will not work out anyway.
    int32_t sigi;
    if (apint10_to_int32(&sigi, &a->significand)) {
      return false;
    }
    float sigf = (float)sigi;
    if (e >= -10 && e <= +10) {
      // 2.1
      if (e < 0) {
        sigf /= FLT_EXACT_POW10[-e];
      } else {
        sigf *= FLT_EXACT_POW10[+e];
      }
      *pResult = sigf;
      return true;
    } 
#if defined(F32_FASTPATH2) && 1 == F32_FASTPATH2
    else if (e >= 0) {
      // 2.2
      int32_t shift = F32_FASTPATH_MAX_DECIMAL_DIGITS - a->significand.size;
      if (e <= 10 + shift) {
        sigf *= FLT_EXACT_POW10[shift];
        sigf *= FLT_EXACT_POW10[e - shift];
        *pResult = sigf;
        return true;
      }
      // We have the hard case.
    }
#endif
  }
#endif
  return false;
}

static bool
apreal10_to_dbl_slow
  (
    Arcadia_Thread* thread,
    apreal10* a,
    double* pResult
  )
{
  // A decimal exponent above 308 already yields infinity.
  // A decimal exponent below -324 already yields infinity.
  // so any valid exponent must fit into an int32_t anyway.
  int32_t exp;
  if (apint10_to_int32(&exp, &a->exponent)) {
    return false;
  }
  const int32_t dexp = exp;
  if (exp < -324) {
    *pResult = a->significand.negative ? -0. : 0.;
    return true;
  } else if (exp > 308) {
    *pResult = a->significand.negative ? -INFINITY : +INFINITY;
    return true;
  }

  double fval;
  {
    int64_t temporary;
    if (apint10_to_int64(&temporary, &a->significand)) {
      return false;
    }
    fval = (double)temporary;
  }

  // For now simply compute some kind of approximation in sigbf by simply scaling by powers of 10 until.
  if (exp > 0) {
    // & 15 is nothing else but a speedy mod 16
    // >>= 4 is nothing else but a speedy / 16
    // we use 16 here because it is the largest power of two smaller than or equal to number of table entries in DBL_EXACT_POW10
    while (0 != (exp & 15)) {
      fval *= DBL_EXACT_POW10[exp & 15];
      exp >>= 4;
    }
    if (isinf(fval)) {
      *pResult = fval;
      return true;
    }
  } else if (exp < 0) {
    exp = -exp;
    while (0 != (exp & 15)) {
      fval /= DBL_EXACT_POW10[exp & 15];
      exp >>= 4;
    }
    if (0.0f == fval) {
      *pResult = fval;
      return true;
    }
  }

  // bigb represents the big binary value and bigd represents the big decimal value
  apint10 bigb, bigd;
  if (apint10_initialize(&bigb)) {
    return false;
  }
  if (apint10_initialize(&bigd)) {
    apint10_uninitialize(&bigb);
    return false;
  }
  if (apint10_copy(&bigd, &a->significand)) {
    apint10_uninitialize(&bigd);
    apint10_uninitialize(&bigb);
    return false;
  }
#if F64_TRUNCATE_MANY_DIGITS
  {
    // The maximum number of digits we use.
    // Note that DBL_DECIMAL_DIG is so small that a DBL_DECIMAL_DIG nines fit into an uint64_t. 
    size_t temporary = DBL_DECIMAL_DIG < a->significand.size ? DBL_DECIMAL_DIG : a->significand.size;
    // If the number n of digits exceeds the threshold by d, then we
    // - replace the last d digits by a single 1 and
    // - increase the exponent by d - 1.
    // Example:
    // Given the number 15012 * 10^1 (which is 150120) and a threshold of 3 then that number of digits in that number exceeds the treshold by 2.
    // Hence we replace the last 2 digits by a 1 and multiply by 10^1 to obtain 1501 * 10^2 (which is 150100).
    if (bigd.size > temporary) {
      size_t delta = bigd.size - temporary;
      apint10_divide_p10_uint64(&bigd, delta);
      apint10_multiply_p10_uint64(&bigd, 1);
      apint10_add_uint16(&bigd, 1);
    }
  }
#endif
  // Important: Recompute now the actual exponent.
  exp = dexp - bigd.size;

  uint64_t fbits = dbl_to_uint64(fval);

  // Let us consider e.
  // First of all, it is obvious that 10^e can be rewritten to 10^e = 5^e * 2^e.
  // Secondly, bigd * 10^e is the precise representation of our foat.
  // sigbf
  // We store the number of values
  // Note that one of the three conditions hold:
  // if bd5 is |e| then bb5 is 0 and e is non-negative
  // if bb5 is |e| then bd5 is 0 and e is negative
  // both bb5 and bd5 are 0
  const int64_t bb5 = exp < 0 ? -exp : 0; // bb5 = Math.max(0, -e)
  const int64_t bd5 = exp >= 0 ? +exp : 0; // bd5 = Math.max(0, +e)

  // The correction loop.
  while (true) {
    int64_t fexp = (int64_t)(fbits >> DBL_EXPONENT_SHIFT);
    int64_t fsig = (int64_t)(fbits & DBL_SIGNIFICAND_MASK);
    if (fexp > 0) {
      // Add the implicit one bit.
      fexp |= INT64_C(1) << DBL_EXPONENT_SHIFT;
    } else {
      // The biased exponent is 0. As fbits is not "not a number" or "infinity", this suggests a denormalized number.
      // First we compute the number of leading zeroes of the binsig and from that number
      // - we subtract 1 for the sign bit
      // - we subtract 11 for the exponent bits
      // - we add 1 for the implicit 0 bit
      size_t leadingZeroes = Arcadia_countLeadingZeroesNatural64Value(thread, fsig);
      leadingZeroes -= DBL_SIGN_BITS + DBL_EXPONENT_BITS - 1; // rhs is 11 as DBL_SIGN_BITS = 1 and DBL_EXPONENT_BITS = 11 hence 1 + 11 - 1 := 11
      // An alternative is
      // - we subtract 64
      // - we add the number of sign bits
      // - we add the exponent shift
      //leadingZeroes -= 64 - DBL_SIGN_BITS - DBL_EXPONENT_SHIFT; // rhs is 11 as DBL_SIGN_BITS = 1 and DBL_EXPONENT_SHIFT = 52 hence 64 - 1 - 52 := 11
      fsig <<= leadingZeroes;
      // The minimum biased exponent for a normalized number is 1.
      // So set the exponent to 1 - leadingZeroes (which is not a valid biased exponent value anymore, however, we do not care at this point yet).
      fexp = INT64_C(1) - (int64_t)leadingZeroes;
    }
    // Unbias binexp.
    fexp -= Arcadia_Real64Value_ExponentBias;
    // If binsig has |# trailing zeroes| trailing zeroes, we divide it by 2^|# trailing zeroes| and increment binexp by |# trailing zeroes|.
    size_t trailingZeroes = Arcadia_countTrailingZeroesInteger64Value(thread, fsig);
    fsig >>= trailingZeroes;
    fexp += trailingZeroes;
    int64_t bb2 = bb5;
    int64_t bd2 = bd5;
    if (fexp >= 0) {
      bb2 += fexp;
    } else {
      bd2 -= fexp;
    }
    break;
  }
  apint10_uninitialize(&bigd);
  apint10_uninitialize(&bigb);
  return false;
}

static bool
apreal10_to_flt_slow
  (
    Arcadia_Thread* thread,
    apreal10* a,
    float* pResult
  )
{
  // A decimal exponent above +38 already yields infinity.
  // A decimal exponent below +45 already yields infinity.
  // Hence any valid exponent must fit into an int32_t anyway.
  int32_t exp;
  if (apint10_to_int32(&exp, &a->exponent)) {
    return false;
  }
  const int32_t dexp = exp;
  if (exp < -45) {
    *pResult = a->significand.negative ? -0.f : +0.f;
    return true;
  } else if (exp > 38) {
    *pResult = a->significand.negative ? -INFINITY : +INFINITY;
    return true;
  }

  // Now, we have the significant part of the float in fvalue.
  double fval;
  {
    int32_t temporary;
    if (apint10_to_int32(&temporary, &a->significand)) {
      return false;
    }
    fval = (float)temporary;
  }

  // For now simply compute some kind of approximation in sigbf by simply scaling by powers of 10 until.
  if (exp > 0) {
    // & 7 is nothing else but a speedy mod 8 (masks the lower 3 bit)
    // >>= 3 is nothing else but a speedy / 8
    // we use 8 here because it is the largest power of two smaller than or equal to number of table entries in FLT_EXACT_POW10
    while (exp & 7) {
      fval *= FLT_EXACT_POW10[exp & 7];
      exp >>= 3;
    }
    if (isinf(fval)) {
      *pResult = fval;
      return true;
    }
  } else if (exp < 0) {
    exp = -exp;
    while (exp & 7) {
      fval *= FLT_EXACT_POW10[exp & 7];
      exp >>= 3;
    }
    if (0.0f == fval) {
      *pResult = fval;
      return true;
    }
  }
  // bigb represents the big binary value and bigd represents the big decimal value
  apint10 bigb, bigd;
  if (apint10_initialize(&bigb)) {
    return false;
  }
  if (apint10_initialize(&bigd)) {
    apint10_uninitialize(&bigb);
    return false;
  }
  if (apint10_copy(&bigd, &a->significand)) {
    apint10_uninitialize(&bigd);
    apint10_uninitialize(&bigb);
    return false;
  }
#if F32_TRUNCATE_MANY_DIGITS
  {
    // The maximum number of digits we use.
    // Note that FLT_DECIMAL_DIG is so small that FLT_DECIMAL_DIG nines fit into an uint32_t.
    size_t temporary = FLT_DECIMAL_DIG < a->significand.size ? FLT_DECIMAL_DIG : a->significand.size;
    // If the number n of digits exceeds the threshold by d, then we
    // - replace the last d digits by a single 1 and
    // - increase the exponent by d - 1.
    // Example:
    // Given the number 15012 * 10^1 (which is 150120) and a threshold of 3 then that number of digits in that number exceeds the treshold by 2.
    // Hence we replace the last 2 digits by a 1 and multiply by 10^1 to obtain 1501 * 10^2 (which is 150100).
    if (bigd.size > temporary) {
      size_t delta = bigd.size - temporary;
      apint10_divide_p10_uint64(&bigd, delta);
      apint10_multiply_p10_uint64(&bigd, 1);
      apint10_add_uint16(&bigd, 1);
      exp += delta - 1;
    }
  }
#endif
  // Important: Recompute now the actual exponent.
  exp = dexp - bigd.size;

  uint32_t fbits = flt_to_uint32(fval);

  // bigd = sig * 10^exp is the precise representation.
  // bigb = binsig * 2^fexp is an approximation.
  // Note that
  // bigd = sig * 10^exp = sig * 5^e * 2^e
  // Hence if we only are interested in the relation of bigd and bigb,
  // then it is convenient to simply not consider the common powers of 2.
  // Hence we actually compare
  // bigd' = sig * 2^exp
  // bigb' = bsing * 2^binexp

  const int32_t bb5 = exp < 0 ? -exp : 0; // bb5 = Math.max(0, -exp)
  const int32_t bd5 = exp >= 0 ? +exp : 0; // bd5 = Math.max(0, +exp)

  // The correction loop.
  while (true) {
    int32_t fexp = (int32_t)(fbits >> FLT_EXPONENT_SHIFT);
    int32_t fsig = (int32_t)(fbits & FLT_SIGNIFICAND_MASK);
    if (fexp > 0) {
      // add the implicit one bit.
      fexp |= INT32_C(1) << FLT_EXPONENT_SHIFT;
    } else {
      // The biased exponent is 0. As fbits is not "not a number" or "infinity", this suggests a denormalized number.
      // First we compute the number of leading zeroes of the binsig and from that number
      // - we subtract 1 for the sign bit
      // - we subtract 11 for the exponent bits
      // - we add 1 for the implicit 0 bit
      size_t leadingZeroes = Arcadia_countLeadingZeroesNatural32Value(thread, fsig);
      leadingZeroes -= FLT_SIGN_BITS + FLT_EXPONENT_BITS - 1; // rhs is 8 as FLT_SIGN_BITS = 1 and FLT_EXPONENT_BITS = 8 hence 1 + 8 - 1 := 8
      // An alternative is
      // - we subtract 32
      // - we add the number of sign bits
      // - we add the exponent shift
      //leadingZeroes -= 32 - FLT_SIGN_BITS - FLT_EXPONENT_SHIFT; // rhs is 8 as FLT_SIGN_BITS = 1 and FLT_EXPONENT_SHIFT = 23 hence 32 - 1 - 23 := 8
      fsig <<= leadingZeroes;
      // The minimum biased exponent for a normalized number is 1.
      // So set the exponent to 1 - leadingZeroes (which is not a valid biased exponent value anymore, however, we do not care at this point yet).
      fexp = INT32_C(1) - (int32_t)leadingZeroes;
    }
    // Unbias binexp.
    fexp -= Arcadia_Real32Value_ExponentBias;
    // If binsig has |# trailing zeroes| trailing zeroes, we divide it by 2^|# trailing zeroes| and increment binexp by |# trailing zeroes|.
    size_t trailingZeroes = Arcadia_countTrailingZeroesInteger32Value(thread, fsig);
    fsig >>= trailingZeroes;
    fexp += trailingZeroes;

    // Note that one of the three conditions hold:
    // if bd2 is |e| then bb2 is 0 and e is non-negative
    // if bb2 is |e| then bd2 is 0 and e is negative
    // both bb2 and bd2 are 0
    int32_t bb2 = bb5;
    int32_t bd2 = bd5;
    if (fexp >= 0) {
      bb2 += fexp;
    } else {
      bd2 -= fexp;
    }
    break;
  }
  apint10_uninitialize(&bigd);
  apint10_uninitialize(&bigb);
  return false;
}

static bool
apreal10_to_dbl
  (
    Arcadia_Thread* thread,
    apreal10* a,
    double* pResult
  )
{
  if (apreal10_to_dbl_fast(thread, a, pResult)) {
    return true;
  }
  if (apreal10_to_dbl_slow(thread, a, pResult)) {
    return true;
  }
  return false;
}

static bool
apreal10_to_flt
  (

    Arcadia_Thread* thread,
    apreal10* a,
    float* pResult
  )
{
  if (apreal10_to_flt_fast(thread, a, pResult)) {
    return true;
  }
  if (apreal10_to_flt_slow(thread, a, pResult)) {
    return true;
  }
  return false;
}

#include <stdio.h>

static void check_to_flt(Arcadia_Thread* thread, const char *literal) {
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (apreal10_from_literal(&a, literal, strlen(literal))) {
    goto Error;
  }
  float af;
  if (!apreal10_to_flt(thread, &a, &af)) {
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
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
  return;
}

// test
// - from literal
static void
testFromLiteral
  (
    Arcadia_Thread* thread
  )
{
  float f;
  bool booleanResult;
  apreal10 a; apint10 shiftExp;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (apint10_initialize(&shiftExp)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    check_to_flt(thread, u8"36e-1");  // path 2.1
    check_to_flt(thread, u8"36e+1");  // path 2.1
    check_to_flt(thread, u8"36e-10"); // path 2.1 (corner case for float)
    check_to_flt(thread, u8"36e+10"); // path 2.1 (corner case for float)
    check_to_flt(thread, u8"36e+15"); // path 2.2 (corner case for float)
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
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
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
  return;
}

// test
// - initialize and
// - set i64
static void
testFromI64
  (
    Arcadia_Thread* thread
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  for (size_t i = 0; i < 63; ++i) {
    int64_t v = INT64_C(1) << i;
    if (apreal10_from_uint64(&a, v)) {
      apreal10_uninitialize(&a);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
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
    Arcadia_Thread* thread
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  for (size_t i = 0; i < 63; ++i) {
    uint64_t v = UINT64_C(1) << i;
    if (apreal10_from_uint64(&a, v)) {
      apreal10_uninitialize(&a);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
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
    Arcadia_Thread* thread
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
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

// test
// - set i64 and
// - copy
static void
testCopy
  (
    Arcadia_Thread* thread
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump((thread));
  }
  if (apreal10_from_int64(&a, INT64_MAX)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (apreal10_copy(&b, &a)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  int result;
  if (apreal10_compare(&result, &a, &b)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (result) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}

void
Arcadia_Ring1_Tests_Support_apreal10
  (
    Arcadia_Thread* thread
  )
{
  testFromU64(thread);
  testFromI64(thread);
  testFromLiteral(thread);
  testCopy(thread);
  testShift(thread);

}
