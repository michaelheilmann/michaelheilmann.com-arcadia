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

// Last modified: 2025-02-19

#if !defined(ARCADIA_RING1_SUPPORT_IEEE754_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_IEEE754_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if __STDC_VERSION__ < 202311L
  #define STATIC_ASSERT(condition, message) _Static_assert(condition, message)
#else
  #define STATIC_ASSERT(condition, message) static_assert(condition, message)
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// the number of bits of a float (https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
#define FLT_BITS (32)
// the number of fraction bits of a float
#define FLT_FRAC_BITS (23)
// the number of exponent bits of a float
#define FLT_EXP_BITS (8)
// the number of sign bits of a float
#define FLT_SGN_BITS (1)

// mask for the fraction bits of a float
#define FLT_FRAC_MASK (UINT32_C(1) << FLT_FRAC_BITS) - 1
// mask for the exponent bits of a float
#define FLT_EXP_MASK ((UINT32_C(1) << FLT_EXP_BITS) - 1) << FLT_FRAC_BITS
// mask for the sign bits of a float
#define FLT_SGN_MASK (((UINT32_C(1) << FLT_SGN_BITS) - 1) << (FLT_EXP_BITS + FLT_FRAC_BITS))

// We have a significand of 23 bits (the bits at indices 0 trough 22) explicitly stored. In addition, the MSB  (the bit at index 23) is fixed to 1.
// A maximum value of 16 777 215 = 2^24 - 1 can be represent if all 24 bits - that is, the bits at indices 0 through 23 - are set to 1.
// A minimum value of  8 388 608 = 2^23 can be represented if the bit at index 23 is set to 1 and the bits at indices 0 through 22 are set to 0.
STATIC_ASSERT(FLT_BITS == FLT_SGN_BITS + FLT_EXP_BITS + FLT_FRAC_BITS, "<internal error>");

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// the number of bits of a double (https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
#define DBL_BITS (64)
// the number of bits of the fraction of a double
#define DBL_FRAC_BITS (52)
// the number of exponent bits of a double
#define DBL_EXP_BITS (11)
// the number of sign bits of a double
#define DBL_SGN_BITS (1)

// mask for the fraction bits of a double
#define DBL_FRAC_MASK (UINT64_C(1) << DBL_FRAC_BITS) - 1
// mask for the exponent bits of a double
#define DBL_EXP_MASK ((UINT64_C(1) << DBL_EXP_BITS) - 1) << DBL_FRAC_BITS
// mask for the sign bits of a double
#define DBL_SGN_MASK ((UINT64_C(1) << DBL_SGN_BITS) - 1) << (DBL_EXP_BITS + DBL_FRAC_BITS)

// The significand has 52 bits (the bits at indices 0 through 51) explicitly stored. In addition, the MSB (the bit at index 52) is fixed to 1.
// A maximum value of 9 007 199 254 740 991 = 2^53 - 1 can be represented if all 53 bits - that is, the bits at indices 0 through 52 - are set to 1.
// A minimum value of 4 503 599 627 370 496 = 2^52  can be represented if the bit at index 52 is set to 1 and the bits at indices 0 through 51 are set to 0.
STATIC_ASSERT(DBL_BITS == DBL_SGN_BITS + DBL_EXP_BITS + DBL_FRAC_BITS, "<internal error>");

#endif // ARCADIA_RING1_SUPPORT_IEEE754_H_INCLUDED
