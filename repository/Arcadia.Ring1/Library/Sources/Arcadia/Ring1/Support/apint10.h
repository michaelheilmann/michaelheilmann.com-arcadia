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

#if !defined(ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <malloc.h>
#include <string.h>
#include "Arcadia/Ring1/Support/tables.h"

// use uint32_t instead of size_t for sizes
typedef uint32_t apint10_size_type;
#define APINT10_SIZE_MIN (UINT32_C(0))
#define APINT10_SIZE_MAX (UINT32_MAX)

/// A arbitrary precisioninteger base 10.
/// s * (d[0] * 10^0 + d[1] * 10^1 + ... + d[n-1] * 10^[n-1]) 
/// where
/// - s denotes the sign (+1 for plus, -1 for minus)
/// - d[i] denotes a digit 0 <= d[i] <= 9
/// and n > 0 is the number of digits
/// The following invariant is preserved
/// - zero is always represented by n = 1, d0 = 0, and s = 1
/// - d[n-1] != 0 unless n = 1
/// This implementation distinguishes between signed zero by setting negative accordingly.
/// In arithmetic and equivalence checks, positive and negative zero are not distinguished.
typedef struct apint10 {
  uint8_t* digits;
  apint10_size_type size;
  apint10_size_type capacity;
  bool negative;
} apint10;

#define APINT10_MAXIMAL_CAPACITY APINT10_SIZE_MAX / sizeof(uint8_t)

int
apint10_initialize
  (
    apint10* this
  );

int
apint10_uninitialize
  (
    apint10* this
  );

int
apint10_is_zero
  (
    bool* result,
    apint10* this
  );

int
apint10_is_negative
  (
    bool* result,
    apint10* this
  );

int
apint10_is_positive
  (
    bool* result,
    apint10* this
  );

int
apint10_copy
  (
    apint10* this,
    apint10* other
  );

int
apint10_increase_capacity
  (
    apint10* this,
    uint32_t additional_capacity
  );

int
apint10_magnitude
  (
    apint10* this
  );

int
apint10_from_int16
  (
    apint10* this,
   int16_t value
  );

int
apint10_from_int32
  (
    apint10* this,
   int32_t value
  );

int
apint10_from_int64
  (
    apint10* this,
   int64_t value
  );

int
apint10_from_int8
  (
    apint10* this,
   int8_t value
  );

int
apint10_from_literal
  (
    apint10* this,
    const uint8_t* p,
    uint32_t n
  );

int
apint10_from_uint16
  (
    apint10* this,
    uint16_t value
  );

int
apint10_from_uint32
  (
    apint10* this,
    uint32_t value
  );

int
apint10_from_uint64
  (
    apint10* this,
    uint64_t value
  );

int
apint10_from_uint8
  (
    apint10* this,
    uint8_t value
  );

int
apint10_from_power_of_two_uint64
  (
    apint10* this,
    uint64_t e
  );

int
apint10_from_power_of_five_uint64
  (
    apint10* this,
    uint64_t e
  );

int
apint10_from_power_of_ten_uint64
  (
    apint10* this,
    uint64_t e
  );

int
apint10_compare_magnitudes
  (
   int* result,
    apint10* this,
    apint10* other
  );

int
apint10_compare
  (
   int* result,
    apint10* this,
    apint10* other
  );

int
apint10_swap
  (
    apint10* this,
    apint10* other
  );

int
apint10_add_uint16
  (
    apint10* this,
    uint16_t other
  );

int
apint10_add_uint32
  (
    apint10* this,
    uint32_t other
  );

int
apint10_add_uint64
  (
    apint10* this,
    uint64_t other
  );

int
apint10_add_uint8
  (
    apint10* this,
    uint8_t other
  );

int
apint10_add
  (
    apint10* this,
    apint10* other
  );

int
apint10_subtract_uint16
  (
    apint10* this,
    uint16_t other
  );

int
apint10_subtract_uint32
  (
    apint10* this,
    uint32_t other
  );

int
apint10_subtract_uint64
  (
    apint10* this,
    uint64_t other
  );

int
apint10_subtract_uint8
  (
    apint10* this,
    uint8_t other
  );

int
apint10_subtract
  (
    apint10* this,
    apint10* other
  );

int
apint10_multiply
  (
    apint10* this,
    apint10* other
  );

int
apint10_multiply_p10_uint64
  (
    apint10* this,
    uint64_t e
  );

int
apint10_divide_p10_uint64
  (
    apint10* this,
    uint64_t e
  );

int
apint10_negate
  (
    apint10* this
  );

int
apint10_equal_to
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_not_equal_to
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_greater_than
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_greater_than_or_equal_to
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_lower_than
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_lower_than_or_equal_to
  (
    bool* result,
    apint10* this,
    apint10* other
  );

int
apint10_equal_to_uint16
  (
    bool* result,
    apint10* this,
    uint16_t other
  );

int
apint10_equal_to_uint32
  (
    bool* result,
    apint10* this,
    uint32_t other
  );

int
apint10_equal_to_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_equal_to_uint8
  (
    bool* result,
    apint10* this,
    uint8_t other
  );

int
apint10_equal_to_int16
  (
    bool* result,
    apint10* this,
    int16_t other
  );

int
apint10_equal_to_int32
  (
    bool* result,
    apint10* this,
    int32_t other
  );

int
apint10_equal_to_int64
  (
    bool* result,
    apint10* this,
   int64_t other
  );

int
apint10_equal_to_int8
  (
    bool* result,
    apint10* this,
    int8_t other
  );

int
apint10_not_equal_to_uint16
  (
    bool* result,
    apint10* this,
    uint16_t other
  );

int
apint10_not_equal_to_uint32
  (
    bool* result,
    apint10* this,
    uint32_t other
  );

int
apint10_not_equal_to_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_not_equal_to_uint8
  (
    bool* result,
    apint10* this,
    uint8_t other
  );

int
apint10_not_equal_to_int64
  (
    bool* result,
    apint10* this,
   int64_t other
  );

int
apint10_greater_than_uint16
  (
    bool* result,
    apint10* this,
    uint16_t other
  );

int
apint10_greater_than_uint32
  (
    bool* result,
    apint10* this,
    uint32_t other
  );

int
apint10_greater_than_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_greater_than_uint8
  (
    bool* result,
    apint10* this,
    uint8_t other
  );

int
apint10_greater_than_int16
  (
    bool* result,
    apint10* this,
    int16_t other
  );

int
apint10_greater_than_int32
  (
    bool* result,
    apint10* this,
    int32_t other
  );

int
apint10_greater_than_int64
  (
    bool* result,
    apint10* this,
   int64_t other
  );

int
apint10_greater_than_int8
  (
    bool* result,
    apint10* this,
    int8_t other
  );

int
apint10_greater_than_or_equal_to_uint16
  (
    bool* result,
    apint10* this,
    uint16_t other
  );

int
apint10_greater_than_or_equal_to_uint32
  (
    bool* result,
    apint10* this,
    uint32_t other
  );

int
apint10_greater_than_or_equal_to_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_greater_than_or_equal_to_uint8
  (
    bool* result,
    apint10* this,
    uint8_t other
  );

int
apint10_greater_than_or_equal_to_int64
  (
    bool* result,
    apint10* this,
   int64_t other
  );

int
apint10_lower_than_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_lower_than_int64
  (
    bool* result,
    apint10* this,
   int64_t other
  );

int
apint10_lower_than_or_equal_to_uint16
  (
    bool* result,
    apint10* this,
    uint16_t other
  );

int
apint10_lower_than_or_equal_to_uint32
  (
    bool* result,
    apint10* this,
    uint32_t other
  );

int
apint10_lower_than_or_equal_to_uint64
  (
    bool* result,
    apint10* this,
    uint64_t other
  );

int
apint10_lower_than_or_equal_to_uint8
  (
    bool* result,
    apint10* this,
    uint8_t other
  );

int
apint10_lower_than_or_equal_to_int16
  (
    bool* result,
    apint10* this,
    int16_t x
  );

int
apint10_lower_than_or_equal_to_int32
  (
    bool* result,
    apint10* this,
    int32_t x
  );

int
apint10_lower_than_or_equal_to_int64
  (
    bool* result,
    apint10* this,
    int64_t x
  );

int
apint10_lower_than_or_equal_to_int8
  (
    bool* result,
    apint10* this,
    int8_t x
  );

int
apint10_to_uint16
  (
    uint16_t* result,
    apint10* this
  );

int
apint10_to_uint32
  (
    uint32_t* result,
    apint10* this
  );

int
apint10_to_uint64
  (
    uint64_t* result,
    apint10* this
  );

int
apint10_to_uint8
  (
    uint8_t* result,
    apint10* this
  );

int
apint10_to_int16
  (
   int16_t* result,
    apint10* this
  );

int
apint10_to_int32
  (
   int32_t* result,
    apint10* this
  );

int
apint10_to_int64
  (
   int64_t* result,
    apint10* this
  );

int
apint10_to_int8
  (
   int8_t* result,
    apint10* this
  );

#if 0
// this := 2^this
// pre: |this| >= 0
int
apint10_power_of_two
  (
    apint10* this
  );
#endif

#if 0
// this := 5^this
// pre: |this| >= 0
int
apint10_power_of_five
  (
    apint10* this
  );
#endif

#if 0
// this := 10^this
// pre: |this| >= 0
int
apint10_power_of_ten
  (
    apint10* this
  );
#endif


#endif // ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED
