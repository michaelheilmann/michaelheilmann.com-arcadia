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

// Last modified: 2024-09-20

#include "Arcadia/Ring1/Implementation/Utf8ToIeee754/Include.h"

#include <stdbool.h>
#include <malloc.h>
#include <string.h>

int
big_decimal_init
  (
    big_decimal_t* this
  )
{
  if (apint10_initialize(&this->integer)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
big_decimal_uninit
  (
    big_decimal_t* this
  )
{
  apint10_uninitialize(&this->integer);
  return 0;
}

int
big_decimal_copy
  (
    big_decimal_t* this,
    big_decimal_t* other
  )
{
  if (!this || !other) {
    return 1;
  }
  if (this == other) {
    return 0;
  }
  if (apint10_copy(&this->integer, &other->integer)) {
    return 1;
  }
  this->exp = other->exp;
  return 0;
}

int
big_decimal_set_i16
  (
    big_decimal_t* this,
    int16_t x
  )
{ return big_decimal_set_i64(this, x); }

int
big_decimal_set_i32
  (
    big_decimal_t* this,
    int32_t x
  )
{ return big_decimal_set_i64(this, x); }

int
big_decimal_set_i64
  (
    big_decimal_t* this,
    int64_t x
  )
{
  if (apint10_from_int64(&this->integer, x)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
big_decimal_set_i8
  (
    big_decimal_t* this,
    int8_t x
  )
{ return big_decimal_set_i64(this, x); }

int
big_decimal_set_u16
  (
    big_decimal_t* this,
    uint16_t x
  )
{ return big_decimal_set_u64(this, x); }

int
big_decimal_set_u32
  (
    big_decimal_t* this,
    uint32_t x
  )
{ return big_decimal_set_u64(this, x); }

int
big_decimal_set_u64
  (
    big_decimal_t* this,
    uint64_t x
  )
{
  if (apint10_from_uint64(&this->integer, x)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
big_decimal_set_u8
  (
    big_decimal_t* this,
    uint8_t x
  )
{ return big_decimal_set_u64(this, x); }

int
big_decimal_compare_magnitudes
  (
    int* result,
    big_decimal_t* this,
    big_decimal_t* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare_magnitudes(result, &this->integer, &other->integer);
}

int
big_decimal_compare
  (
    int* result,
    big_decimal_t* this,
    big_decimal_t* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare(result, &this->integer, &other->integer);
}

int
big_decimal_multiply_p10
  (
    big_decimal_t* this,
    uint64_t e
  )
{
  return apint10_multiply_p10(&this->integer, e);
}

int
big_decimal_divide_p10
  (
    big_decimal_t* this,
    uint64_t e
  )
{
  return apint10_divide_p10(&this->integer, e);
}
