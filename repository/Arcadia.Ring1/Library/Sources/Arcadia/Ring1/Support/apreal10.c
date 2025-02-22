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

#include "Arcadia/Ring1/Support/apreal10.h"

#include <stdbool.h>

int
apreal10_initialize
  (
    apreal10* this
  )
{
  if (apint10_initialize(&this->significand)) {
    return 1;
  }
  if (apint10_initialize(&this->exponent)) {
    apint10_uninitialize(&this->significand);
    return 1;
  }
  return 0;
}

int
apreal10_uninitialize
  (
    apreal10* this
  )
{
  apint10_uninitialize(&this->exponent);
  apint10_uninitialize(&this->significand);
  return 0;
}

int
apreal10_copy
  (
    apreal10* this,
    apreal10* other
  )
{
  if (!this || !other) {
    return 1;
  }
  if (this == other) {
    return 0;
  }
  if (apint10_copy(&this->significand, &other->significand)) {
    return 1;
  }
  if (apint10_copy(&this->exponent, &other->exponent)) {
    return 1;
  }
  return 0;
}

int
apreal10_from_int16
  (
    apreal10* this,
    int16_t other
  )
{ return apreal10_from_int64(this, other); }

int
apreal10_from_int32
  (
    apreal10* this,
    int32_t other
  )
{ return apreal10_from_int64(this, other); }

int
apreal10_from_int64
  (
    apreal10* this,
    int64_t other
  )
{
  if (apint10_from_int64(&this->significand, other)) {
    return 1;
  }
  if (apint10_from_uint8(&this->exponent, 0)) {
    return 1;
  }
  return 0;
}

int
apreal10_from_int8
  (
    apreal10* this,
    int8_t other
  )
{ return apreal10_from_int64(this, other); }

int
apreal10_from_uint16
  (
    apreal10* this,
    uint16_t other
  )
{ return apreal10_from_uint64(this, other); }

int
apreal10_from_uint32
  (
    apreal10* this,
    uint32_t other
  )
{ return apreal10_from_uint64(this, other); }

int
apreal10_from_uint64
  (
    apreal10* this,
    uint64_t other
  )
{
  if (apint10_from_uint64(&this->significand, other)) {
    return 1;
  }
  if (apint10_from_uint8(&this->exponent, 0)) {
    return 1;
  }
  return 0;
}

int
apreal10_from_uint8
  (
    apreal10* this,
    uint8_t other
  )
{ return apreal10_from_uint64(this, other); }

int
apreal10_from
  (
    apreal10* this,
    apint10* significand,
    apint10* exponent
  )
{ 
  if (apint10_copy(&this->significand, significand)) {
    return 1;
  }
  if (apint10_copy(&this->exponent, exponent)) {
    return 1;
  }
  return 0;
}

int
apreal10_from_literal
  (
    apreal10* this,
    const uint8_t* p,
    uint32_t n
  )
{
  apint10 significand, exponent, shiftExponent;
  if (apint10_initialize(&significand)) {
    return 1;
  }
  if (apint10_initialize(&exponent)) {
    apint10_uninitialize(&significand);
    return 1;
  }
  if (apint10_initialize(&shiftExponent)) {
    apint10_uninitialize(&exponent);
    apint10_uninitialize(&significand);
    return 1;
  }
  
#define START (253)

#define END (254)

#define ERROR (255)

#define NEXT() \
    if (s.symbol != END && s.symbol != ERROR) { \
      if (s.current == s.end) { \
        s.symbol = END; \
      } else { \
        s.symbol = *s.current; \
        s.current++; \
      } \
    }

#define IS(X) ((X) == s.symbol)
#define ISRANGE(X, Y) ((X) <= s.symbol && s.symbol <= (Y))

  struct STATE {
    const uint8_t* start;
    const uint8_t* end;
    const uint8_t* current;
    uint32_t symbol;
  };

  struct STATE s = { .start = p, .end = p + n, .current = p, .symbol = START };

  bool exponentNegative = false;
  bool significandNegative = false;
  NEXT();
  if (IS('+')) {
    NEXT();
  } else if (IS('-')) {
    significandNegative = true;
    NEXT();
  }
  if (IS('.')) {
    NEXT();
    if (!ISRANGE('0', '9')) {
      goto SyntaxError;
    }
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10_uint64(&significand, 1)) {
        goto AllocationError;
      }
      if (apint10_add_uint8(&significand, digit)) {
        goto AllocationError;
      }
      if (apint10_subtract_uint8(&shiftExponent, 1)) {
        goto AllocationError;
      }
      NEXT();
    } while (ISRANGE('0', '9'));
  } else if (ISRANGE('0', '9')) {
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10_uint64(&significand, 1)) {
        goto AllocationError;
      }
      if (apint10_add_uint8(&significand, digit)) {
        goto AllocationError;
      }
      NEXT();
    } while (ISRANGE('0', '9'));
    if (IS('.')) {
      NEXT();
      while (ISRANGE('0', '9')) {
        uint8_t digit = s.symbol - '0';
        if (apint10_multiply_p10_uint64(&significand, 1)) {
          goto AllocationError;
        }
        if (apint10_add_uint8(&significand, digit)) {
          goto AllocationError;
        }
        if (apint10_subtract_uint8(&shiftExponent, 1)) {
          goto AllocationError;
        }
        NEXT();
      }
    }
  } else {
    goto SyntaxError;
  }
  if (significandNegative) {
    if (apint10_negate(&significand)) {
      goto AllocationError;
    }
  }
  if (IS('e') || IS('E')) {
    NEXT();
    if (IS('+')) {
      NEXT();
    } else if (IS('-')) {
      exponentNegative = true;
      NEXT();
    }
    if (!ISRANGE('0', '9')) {
      goto SyntaxError;
    }
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10_uint64(&exponent, 1)) {
        goto AllocationError;
      }
      if (apint10_add_uint8(&exponent, digit)) {
        goto AllocationError;
      }
      NEXT();
    } while (ISRANGE('0', '9'));
    if (exponentNegative) {
      if (apint10_negate(&exponent)) {
        goto AllocationError;
      }
    }
  }

#undef IS
#undef NEXT
#undef ERROR
#undef END
#undef START

  if (apint10_add(&exponent, &shiftExponent)) {
    goto AllocationError;
  }

  if (apint10_copy(&this->significand, &significand)) {
    goto AllocationError;
  }

  if (apint10_copy(&this->exponent, &exponent)) {
    goto AllocationError;
  }

  apint10_uninitialize(&shiftExponent);
  apint10_uninitialize(&exponent);
  apint10_uninitialize(&significand);

  return 0;
AllocationError:
SyntaxError:
  apint10_uninitialize(&shiftExponent);
  apint10_uninitialize(&exponent);
  apint10_uninitialize(&significand);
  return 1;
}

int
apreal10_compare_magnitudes
  (
    int* result,
    apreal10* this,
    apreal10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare_magnitudes(result, &this->significand, &other->significand);
}

int
apreal10_compare
  (
    int* result,
    apreal10* this,
    apreal10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare(result, &this->significand, &other->significand);
}

int
apreal10_add
  (
    apreal10* this,
    apreal10* other
  )
{
  int result;
  if (apint10_compare(&result, &this->exponent, &other->exponent)) {
    return 1;
  }
  apint10 delta;
  if (apint10_initialize(&delta)) {
    return 1;
  }
  size_t k = 0;
  apreal10 v[4];
  for (; k < 4; ++k) {
    if (apreal10_initialize(&v[k])) {
      while (k > 0) {
        apreal10_uninitialize(&v[--k]);
      }
      return 1;
    }
  }
  if (apreal10_copy(&v[0], this) || apreal10_copy(&v[1], other)) {
    goto Error;
  }
  if (result < 0) {
    // "v[0]" is smaller than "v[1]"
    // "delta" := "v[1].exponent" - "v[0].exponent"
    // "v[0].exponent" += "delta"
    // "v[0].significand" *= 10^"delta"
    if (apint10_copy(&delta, &v[1].exponent)) goto Error;
    if (apint10_subtract(&delta, &v[0].exponent)) goto Error;
    if (apint10_add(&v[0].exponent, &delta)) {
      goto Error;
    }
    while (true) {
      bool result;
      if (apint10_greater_than_uint64(&result, &delta, UINT64_MAX)) {
        goto Error;
      }
      if (!result) {
        break;
      }
      if (apint10_subtract_uint64(&delta, UINT64_MAX)) {
        goto Error;
      }
      if (apint10_multiply_p10_uint64(&v[0].significand, UINT64_MAX)) {
        goto Error;
      }
    }
    uint64_t t;
    if (apint10_to_uint64(&t, &delta)) {
      return 1;
    }
    if (apint10_multiply_p10_uint64(&v[0].significand, t)) {
      goto Error;
    }
  } else if (result > 0) {
    // "v[1]" is greater then "v[0]"
    // "delta" := "v[0].exponent" - "v[1].exponent"
    // "v[1].exponent" += "delta"
    // "v[1].significand" *= 10^"delta"
    if (apint10_copy(&delta, &v[0].exponent)) goto Error;
    if (apint10_subtract(&delta, &v[1].exponent)) goto Error;
    if (apint10_add(&v[1].exponent, &delta)) {
      goto Error;
    }
    while (true) {
      bool result;
      if (apint10_greater_than_uint64(&result, &delta, UINT64_MAX)) {
        goto Error;
      }
      if (!result) {
        break;
      }
      if (apint10_subtract_uint64(&delta, UINT64_MAX)) {
        goto Error;
      }
      if (apint10_multiply_p10_uint64(&v[1].significand, UINT64_MAX)) {
        goto Error;
      }
    }
    uint64_t t;
    if (apint10_to_uint64(&t, &delta)) {
      return 1;
    }
    if (apint10_multiply_p10_uint64(&v[1].significand, t)) {
      goto Error;
    }
  }
  if (apint10_add(&v[0].significand, &v[1].significand)) {
    goto Error;
  }
  if (apreal10_copy(this, &v[0])) {
    goto Error;
  }
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  apint10_uninitialize(&delta);
  return 0;
Error:
  while (k > 0) {
    apreal10_uninitialize(&v[--k]);
  }
  apint10_uninitialize(&delta);
  return 1;
}

int
apreal10_add_uint16
  (
    apreal10* this,
    uint16_t other
  )
{ return apreal10_add_uint64(this, other); }

int
apreal10_add_uint32
  (
    apreal10* this,
    uint32_t other
  )
{ return apreal10_add_uint64(this, other); }

int
apreal10_add_uint64
  (
    apreal10* this,
    uint64_t other
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    return 1;
  }
  if (apreal10_from_uint64(&a, other)) {
    apreal10_uninitialize(&a);
    return 1;
  }
  if (apreal10_add(this, &a)) {
    apreal10_uninitialize(&a);
    return 1;
  }
  apreal10_uninitialize(&a);
  return 0;
}

int
apreal10_add_uint8
  (
    apreal10* this,
    uint8_t other
  )
{ return apreal10_add_uint64(this, other); }

int
apreal10_multiply_p10_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  return apint10_add_uint64(&this->exponent, e);
}

int
apreal10_multiply_p5_uint64
    (
      apreal10* this,
      uint64_t e
  )
{
  apreal10 other;
  if (apreal10_initialize(&other)) {
    return 1;
  }
  if (apreal10_from_power_of_five_uint64(&other, e)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  if (apreal10_multiply(this, &other)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  return 0;
}

int
apreal10_multiply_p2_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  apreal10 other;
  if (apreal10_initialize(&other)) {
    return 1;
  }
  if (apreal10_from_power_of_two_uint64(&other, e)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  if (apreal10_multiply(this, &other)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  return 0;
}

int
apreal10_divide_p10_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  return apint10_subtract_uint64(&this->exponent, e);
}

#if 0
int
apreal10_divide_p2_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  apreal10 other;
  if (apreal10_initialize(&other)) {
    return 1;
  }
  if (apreal10_from_power_of_two_uint64(&other, e)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  if (apreal10_divide(this, &other)) {
    apreal10_uninitialize(&other);
    return 1;
  }
  return 0;
}
#endif

int
apreal10_from_power_of_two_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  if (apint10_from_power_of_two_uint64(&this->significand, e)) {
    return 1;
  }
  if (apint10_from_uint8(&this->exponent, UINT8_C(0))) {
    return 1;
  }
  return 0;
}

int
apreal10_from_power_of_five_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  if (apint10_from_power_of_five_uint64(&this->significand, e)) {
    return 1;
  }
  if (apint10_from_uint8(&this->exponent, UINT8_C(0))) {
    return 1;
  }
  return 0;
}

int
apreal10_from_power_of_ten_uint64
  (
    apreal10* this,
    uint64_t e
  )
{
  if (apint10_from_power_of_ten_uint64(&this->significand, e)) {
    return 1;
  }
  if (apint10_from_uint8(&this->exponent, UINT8_C(0))) {
    return 1;
  }
  return 0;
}

int
apreal10_multiply
  (
    apreal10* this,
    apreal10* other
  )
{
  if (apint10_multiply(&this->significand, &other->significand)) {
    return 1;
  }
  if (apint10_add(&this->exponent, &other->exponent)) {
    return 1;  
  }
  return 0;
}

#if 0
int
apreal10_divide
  (
    apreal10* this,
    apreal10* other
  )
{
  return 0;
}
#endif
