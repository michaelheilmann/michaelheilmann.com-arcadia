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

// Last modified: 2025-01-01

#if !defined(ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include "Arcadia/Ring1/Support/apint10.h"
#include "Arcadia/Ring1/Support/ieee754.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint8_t digit_t;
#define DIGIT_MIN UINT8_C(0)
#define DIGIT_MAX (DIGIT_BASE-1)
#define DIGIT_BASE 10

#define BIG_DECIMAL_MAX_CP (UINT32_MAX / sizeof(digit_t))

typedef uint16_t double_digit_t;

typedef struct big_decimal_t {
  // the integer
  apint10 integer;
  // the base 10 exponent
  // epx = 0 means the value of this apdec is integer
  // exp > 0 means the value of this apfloat10 is integer * 10^|exp|
  // exp < 0 means the value of this apfloat10 is integer / 10^|exp| 
  int32_t exp;

} big_decimal_t;

// initialize to 0
int
big_decimal_init
  (
    big_decimal_t* this
  );

int
big_decimal_uninit
  (
    big_decimal_t* this
  );

int
big_decimal_copy
  (
    big_decimal_t* this,
    big_decimal_t* other
  );

int
big_decimal_set_i16
  (
    big_decimal_t* this,
    int16_t x
  );

int
big_decimal_set_i32
  (
    big_decimal_t* this,
    int32_t x
  );

// negative = true if x is negative, false otherwise
// sz = <count>
// decimal_point = <count>
// where <count> is the number of digits
int
big_decimal_set_i64
  (
    big_decimal_t* this,
    int64_t x
  );

int
big_decimal_set_i8
  (
    big_decimal_t* this,
    int8_t x
  );

int
big_decimal_set_u16
  (
    big_decimal_t* this,
    uint16_t x
  );

int
big_decimal_set_u32
  (
    big_decimal_t* this,
    uint32_t x
  );

// negative = false
// sz = <count>
// decimal_point = <count>
// where <count> is the number of digits
int
big_decimal_set_u64
  (
    big_decimal_t* this,
    uint64_t x
  );

int
big_decimal_set_u8
  (
    big_decimal_t* this,
    uint8_t x
  );

int
big_decimal_compare_magnitudes
  (
    int* result,
    big_decimal_t* this,
    big_decimal_t* other
  );

int
big_decimal_compare
  (
    int* result,
    big_decimal_t* this,
    big_decimal_t* other
  );

// d = d * 10^e, e >= 0
int
big_decimal_multiply_p10
  (
    big_decimal_t* this,
    uint64_t e
  );

// d = d / 10^e, e >= 0
int
big_decimal_divide_p10
  (
    big_decimal_t* this,
    uint64_t e
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if 0
// the number of bits of a float (https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
#define FLT_BITS (32)
// the number of fraction bits of a float
#define FLT_FRAC_BITS (23)
// the number of exponent bits of a float
#define FLT_EXP_BITS (8)
// the number of sign bits of a float
#define FLT_SGN_BITS (1)

static_assert(FLT_BITS == FLT_SGN_BITS + FLT_EXP_BITS + FLT_FRAC_BITS, "<internal error>");

// get the fraction bit mask
static inline uint32_t
flt_get_frac_mask
  (
  )
{
  return (UINT32_C(1) << FLT_FRAC_BITS) - 1;
}

// get the exponent bit mask
static inline uint32_t
flt_get_exp_mask
  (
  )
{
  return ((UINT32_C(1) << FLT_EXP_BITS) - 1) << FLT_FRAC_BITS;
}

// get the sign bit mask
static inline uint32_t
flt_get_sgn_mask
  (
  )
{
  return ((UINT32_C(1) << FLT_SGN_BITS) - 1) << (FLT_EXP_BITS + FLT_FRAC_BITS);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// the number of bits of a double (https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
#define DBL_BITS (64)
// the number of bits of the fraction of a double
#define DBL_FRAC_BITS (52)
// the number of exponent bits of a double
#define DBL_EXP_BITS (11)
// the number of sign bits of a double
#define DBL_SGN_BITS (1)

static_assert(DBL_BITS == DBL_SGN_BITS + DBL_EXP_BITS + DBL_FRAC_BITS, "<internal error>");

// get the fraction bit mask
static inline uint64_t
dbl_get_frac_mask
  (
  )
{
  return (UINT64_C(1) << DBL_FRAC_BITS) - 1;
}

// get the exponent bit mask
static inline uint64_t
dbl_get_exp_mask
  (
  )
{ 
  return ((UINT64_C(1) << DBL_EXP_BITS) - 1) << DBL_FRAC_BITS;
}

// get the sign bit mask
static inline uint64_t
dbl_get_sgn_mask
  (
  )
{
  return ((UINT64_C(1) << DBL_SGN_BITS) - 1) << (DBL_EXP_BITS + DBL_FRAC_BITS);
}
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @return @a 0 on success. A non-zero value on failure.
int
utf8_to_flt
  (
    const uint8_t* p,
    size_t n,
    float* v
  );
  
/// @return @a 0 on success. A non-zero value on failure.
int
utf8_to_dbl
  (
    const uint8_t* p,
    size_t n,
    double* v
  );

#endif // ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED
