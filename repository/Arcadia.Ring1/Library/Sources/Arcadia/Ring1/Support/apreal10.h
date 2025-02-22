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

#if !defined(ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED

#include "Arcadia/Ring1/Support/apint10.h"
#include "Arcadia/Ring1/Support/ieee754.h"

// a decimal real number of the form <significand> * 10^<exponent> where <significand> is an integer and <exponent> is an integer.
typedef struct apreal10 {
  // the significaned
  apint10 significand;
  // the exponent
  apint10 exponent;
} apreal10;

// initialize to 0
int
apreal10_initialize
  (
    apreal10* this
  );

int
apreal10_uninitialize
  (
    apreal10* this
  );

int
apreal10_copy
  (
    apreal10* this,
    apreal10* other
  );

// negative = true if x is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_int16
  (
    apreal10* this,
    int16_t other
  );

// negative = true if ither is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_int32
  (
    apreal10* this,
    int32_t other
  );

// negative = true if other is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_int64
  (
    apreal10* this,
    int64_t other
  );

// negative = true if other is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_int8
  (
    apreal10* this,
    int8_t other
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_uint16
  (
    apreal10* this,
    uint16_t other
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_uint32
  (
    apreal10* this,
    uint32_t other
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_uint64
  (
    apreal10* this,
    uint64_t other
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_uint8
  (
    apreal10* this,
    uint8_t other
  );

int
apreal10_from
  (
    apreal10* this,
    apint10* significand,
    apint10* exponent
  );

// parse this apreal10 from an UTF8 decimal real literal string
int
apreal10_from_literal
  (
    apreal10* this,
    const uint8_t* p,
    uint32_t n
  );

int
apreal10_compare_magnitudes
  (
    int* result,
    apreal10* this,
    apreal10* other
  );

int
apreal10_compare
  (
    int* result,
    apreal10* this,
    apreal10* other
  );

int
apreal10_add
  (
    apreal10* this,
    apreal10* other
  );

int
apreal10_add_uint16
  (
    apreal10* this,
    uint16_t other
  );

int
apreal10_add_uint32
  (
    apreal10* this,
    uint32_t other
  );

int
apreal10_add_uint64
  (
    apreal10* this,
    uint64_t other
  );

int
apreal10_add_uint8
  (
    apreal10* this,
    uint8_t other
  );

// d := d * 10^e
int
apreal10_multiply_p10_uint64
  (
    apreal10* this,
    uint64_t e
  );

// d := d * 5^e
int
apreal10_multiply_p5_uint64
  (
    apreal10* this,
    uint64_t e
  );

// d := d * 2^e
int
apreal10_multiply_p2_uint64
  (
    apreal10* this,
    uint64_t e
  );

// d = d / 10^e
int
apreal10_divide_p10_uint64
  (
    apreal10* this,
    uint64_t e
  );

#if 0
// d := d / 2^e
int
apreal10_divide_p2
  (
    apreal10* this,
    uint64_t e
  );
#endif

int
apreal10_from_power_of_two_uint64
  (
    apreal10* this,
    uint64_t e
  );

int
apreal10_from_power_of_five_uint64
  (
    apreal10* this,
    uint64_t e
  );

int
apreal10_from_power_of_ten_uint64
  (
    apreal10* this,
    uint64_t e
  );

int
apreal10_multiply
  (
    apreal10* this,
    apreal10* other
  );

#if 0
int
apreal10_divide
  (
    apreal10* this,
    apreal10* other
  );
#endif

#endif // ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED
