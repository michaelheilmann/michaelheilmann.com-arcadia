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

// The number of bits of the significand.
// Usually 23.
// TODO: Add to documentation.
#define FLT_SIGNIFICAND_BITS (23)
// The shift of the bits of the significand.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the significand.
// Usually 0.
// TODO: Add to documentation.
#define FLT_SIGNIFICAND_SHIFT (0)

// The number of bits of the exponent.
// Usually 8.
// TODO: Add to documentation.
#define FLT_EXPONENT_BITS (8)
// The shift of the bits of the exponent.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the exponent.
// Usually 23.
// TODO: Add to documentation.
#define FLT_EXPONENT_SHIFT FLT_SIGNIFICAND_BITS

// The number of bits of the sign.
// Usually 1.
// TODO: Add to documentation.
#define FLT_SIGN_BITS (1)
// The shift of the bits of the sign.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the sign.
// Usually 31.
// TODO: Add to documentation.
#define FLT_SIGN_SHIFT (FLT_EXPONENT_BITS + FLT_SIGNIFICAND_BITS)

// The bits mask for the bits of the significand.
// TODO: Add to documentation.
#define FLT_SIGNIFICAND_MASK (((UINT32_C(1) << FLT_SIGNIFICAND_BITS) - 1) << FLT_SIGNIFICAND_SHIFT)
// The bits mask for the bits of the exponent.
// TODO: Add to documentation.
#define FLT_EXPONENT_MASK (((UINT32_C(1) << FLT_EXPONENT_BITS) - 1) << FLT_EXPONENT_SHIFT)
// The bits mask for the bits of the sign.
// TODO: Add to documentation.
#define FLT_SIGN_MASK (((UINT32_C(1) << FLT_SIGN_BITS) - 1) << FLT_SIGN_SHIFT)

// We have a significand of 23 bits (the bits at indices 0 trough 22) explicitly stored. In addition, the MSB  (the bit at index 23) is fixed to 1.
// A maximum value of 16 777 215 = 2^24 - 1 can be represent if all 24 bits - that is, the bits at indices 0 through 23 - are set to 1.
// A minimum value of  8 388 608 = 2^23 can be represented if the bit at index 23 is set to 1 and the bits at indices 0 through 22 are set to 0.
STATIC_ASSERT(FLT_BITS == FLT_SIGN_BITS + FLT_EXPONENT_BITS + FLT_SIGNIFICAND_BITS, "<internal error>");

uint32_t flt_to_uint32(float v);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// the number of bits of a double (https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
#define DBL_BITS (64)

// The number of bits of the significand.
// Usually 52.
// TODO: Add to documentation.
#define DBL_SIGNIFICAND_BITS (52)
// The shift of the bits of the significand.
// In other terms, if the 64 bits have indices from 0 to 63, then this is the index of the LSB of the significand.
// Usually 0.
// TODO: Add to documentation.
#define DBL_SIGNIFICAND_SHIFT (0)

// The number of bits of the exponent.
// Usually 11.
// TODO: Add to documentation.
#define DBL_EXPONENT_BITS (11)
// The shift of the bits of the exponent.
// In other terms, if the 64 bits have indices from 0 to 63, then this is the index of the LSB of the exponent.
// Usually 52.
// TODO: Add to documentation.
#define DBL_EXPONENT_SHIFT DBL_SIGNIFICAND_BITS

// The number of bits of the sign.
// Usually 1.
// TODO: Add to documentation.
#define DBL_SIGN_BITS (1)
// The shift of the bits of the sign.
// In other terms, if the 64 bits have indices from 0 to 63, then this is the index of the LSB of the sign.
// Usually 63.
// TODO: Add to documentation.
#define DBL_SIGN_SHIFT (DBL_EXPONENT_BITS + DBL_SIGNIFICAND_BITS)

// The bits mask for the bits of the significand.
// TODO: Add to documentation.
#define DBL_SIGNIFICAND_MASK (((UINT64_C(1) << DBL_SIGNIFICAND_BITS) - 1) << DBL_SIGNIFICAND_SHIFT)
// The bits mask for the bits of the exponent.
// TODO: Add to documentation.
#define DBL_EXPONENT_MASK (((UINT64_C(1) << DBL_EXPONENT_BITS) - 1) << DBL_EXPONENT_SHIFT)
// The bits mask for the bits of the sign.
// TODO: Add to documentation.
#define DBL_SIGN_MASK (((UINT64_C(1) << DBL_SIGN_BITS) - 1) << DBL_SIGN_SHIFT)

// The significand has 52 bits (the bits at indices 0 through 51) explicitly stored. In addition, the MSB (the bit at index 52) is fixed to 1.
// A maximum value of 9 007 199 254 740 991 = 2^53 - 1 can be represented if all 53 bits - that is, the bits at indices 0 through 52 - are set to 1.
// A minimum value of 4 503 599 627 370 496 = 2^52  can be represented if the bit at index 52 is set to 1 and the bits at indices 0 through 51 are set to 0.
STATIC_ASSERT(DBL_BITS == DBL_SIGN_BITS + DBL_EXPONENT_BITS + DBL_SIGNIFICAND_BITS, "<internal error>");

uint64_t dbl_to_uint64(double v);

#endif // ARCADIA_RING1_SUPPORT_IEEE754_H_INCLUDED
