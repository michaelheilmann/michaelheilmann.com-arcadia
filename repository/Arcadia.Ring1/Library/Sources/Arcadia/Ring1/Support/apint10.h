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

// Last modified: 2025-02-16

#if !defined(ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <malloc.h>
#include <string.h>

// use uint32_t instead of size_t for sizes
typedef uint32_t apint10_size_type;
#define APINT10_SIZE_MIN (UINT32_C(0))
#define APINT10_SIZE_MAX (UINT32_MAX)

// arbitrary precision base 10 integer.
// zero is denoted by digits[0] = 0, size = 1.
// this implementation distinguishes between signed zero by setting negative accordingly.
// in arithmetic and equivalence checks, positive and negative zero are not distinguished.
// for a non-zero number with n > 0 digits, size = n.
// the least significand digit ist stored at digits[0] and the most significand digit is stored at digits[n-1] with digits[n-1] > 0.
typedef struct apint10 {
  uint8_t* digits;
  apint10_size_type size;
  apint10_size_type capacity;
  bool negative;
} apint10;

#define APINT10_MAXIMAL_CAPACITY APINT10_SIZE_MAX / sizeof(uint8_t)

static inline int
apint10_initialize
  (
    apint10* this
  );

static inline int
apint10_uninitialize
  (
    apint10* this
  );

static inline int
apint10_copy
  (
    apint10* this,
    apint10* other
  );

static inline int
apint10_increase_capacity
  (
    apint10* this,
    uint32_t additional_capacity
  );

static inline int
apint10_from_int16
  (
    apint10* this,
    int16_t value
  );

static inline int
apint10_from_int32
  (
    apint10* this,
    int32_t value
  );

static inline int
apint10_from_int64
  (
    apint10* this,
    int64_t value
  );

static inline int
apint10_from_int8
  (
    apint10* this,
    int8_t value
  );

static inline int
apint10_from_literal
  (
    apint10* this,
    const uint8_t* p,
    uint32_t n
  );

static inline int
apint10_from_uint16
  (
    apint10* this,
    uint16_t value
  );

static inline int
apint10_from_uint32
  (
    apint10* this,
    uint32_t value
  );

static inline int
apint10_from_uint64
  (
    apint10* this,
    uint64_t value
  );

static inline int
apint10_from_uint8
  (
    apint10* this,
    uint8_t value
  );

static inline int
apint10_compare_magnitudes
  (
    int* result,
    apint10* this,
    apint10* other
  );

static inline int
apint10_compare
  (
    int* result,
    apint10* this,
    apint10* other
  );

static inline int
apint10_swap
  (
    apint10* this,
    apint10* other
  );

static inline int
apint10_add
  (
    apint10* this,
    apint10* other
  );

static inline int
apint10_multiply
  (
    apint10* this,
    apint10* other
  );

static inline int
apint10_multiply_p10
  (
    apint10* this,
    uint64_t e
  );

static inline int
apint10_divide_p10  
  (
    apint10* this,
    uint64_t e
  );

static inline int
apint10_initialize
  (
    apint10* this
  )
{
  this->size = 1;
  this->capacity = 1;
  this->digits = malloc(sizeof(uint8_t));
  if (!this->digits) {
    return 1;
  }
  this->digits[0] = 0;
  this->negative = false;
  return 0;
}

static inline int
apint10_uninitialize
  (
    apint10* this
  )
{
  free(this->digits);
  this->digits = 0;
  return 0;
}

static inline int
apint10_copy
  (
    apint10* this,
    apint10* other
  )
{
  if (!this || !other) {
    return 1;
  }
  if (this == other) {
    return 0;
  }
  if (this->capacity < other->capacity) {
    if (apint10_increase_capacity(this, other->capacity - this->capacity)) {
      return 1;
    }
  }
  memcpy(this->digits, other->digits, other->size * sizeof(uint8_t));
  this->size = other->size;
  this->negative = other->negative;
  return 0;
}

static inline int
apint10_increase_capacity
  (
    apint10* this,
    uint32_t additional_capacity
  )
{ 
  uint32_t old_capacity = this->capacity;
  if (APINT10_MAXIMAL_CAPACITY - old_capacity < additional_capacity) {
    return 1;
  }
  uint32_t new_capacity = old_capacity + additional_capacity;
  uint8_t* new_digits = realloc(this->digits, new_capacity * sizeof(uint8_t));
  if (!new_digits) {
    return 1;
  }
  this->capacity = new_capacity;
  this->digits = new_digits;
  return 0;
}

static inline int
apint10_from_int16
  (
    apint10* this,
    int16_t value
  )
{ return apint10_from_int64(this, value); }

static inline int
apint10_from_int32
  (
    apint10* this,
    int32_t value
  )
{ return apint10_from_int64(this, value); }

static inline int
apint10_from_int64
  (
    apint10* this,
    int64_t value
  )
{
  bool negative = value < INT64_C(0);
  uint64_t value1;
  if (value == INT64_MIN) {
    value1 = ((uint64_t)(INT64_MIN + 1)) + 1;
  } else {
    value1 = (uint64_t)(value < INT64_C(0) ? -value : value);
  }
  if (apint10_from_uint64(this, value1)) {
    return 1;
  }
  this->negative = negative;
  return 0; 
}

static inline int
apint10_from_int8
  (
    apint10* this,
    int8_t value
  )
{ return apint10_from_int64(this, value); }

static inline int
apint10_from_literal
  (
    apint10* this,
    const uint8_t* p,
    uint32_t n
  )
{

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

  const uint8_t* digits_start = NULL;
  const uint8_t* digits_end = NULL;

  // determine "negative" and "capacity"
  bool negative = false;
  uint32_t capacity = 0;
  if (IS('+')) {
    NEXT();
  } else if (IS('-')) {
    negative = true;
    NEXT();
  }
  if (!ISRANGE('0', '9')) {
    return 1;
  }
  // skip trailing zeroes
  while (IS('0')) {
    NEXT();
  }
  digits_start = s.current;
  if (s.symbol == END) {
    digits_start--;
  }
  do {
    NEXT();
    capacity++;
  } while (ISRANGE('0', '9'));
  digits_end = s.current;
  capacity = digits_end - digits_start;
  if (this->capacity < capacity) {
    if (apint10_increase_capacity(this, capacity - this->capacity)) {
      return 1;
    }
  }
  this->size = 0;
  while (digits_start != digits_end) {
    this->digits[this->size++] = *digits_start - '0';
    digits_start++;
  }
  this->negative = negative;
  return 0;

#undef IS
#undef NEXT
#undef ERROR
#undef END
#undef START
}

static inline int
apint10_from_uint16
  (
    apint10* this,
    uint16_t value
  )
{ return apint10_from_uint64(this, value); }

static inline int
apint10_from_uint32
  (
    apint10* this,
    uint32_t value
  )
{ return apint10_from_uint64(this, value); }

static inline int
apint10_from_uint64
  (
    apint10* this,
    uint64_t value
  )
{
  uint64_t value1;
  uint32_t required_capacity;
  // (1) compute required capacity
  value1 = value;
  required_capacity = 0;
  do {
    value1 = value1 / UINT64_C(10);
    required_capacity++;
  } while (value1 > 0);
  // (2) allocate required capacity
  if (this->capacity < required_capacity) {
    if (apint10_increase_capacity(this, required_capacity - this->capacity)) {
      return 1;
    }
  }
  // (3) compute size and digits
  value1 = value;
  this->size = 0;
  do {
    uint8_t digit = value1 % UINT8_C(10);
    this->digits[this->size++] = digit;
    value1 = value1 / UINT8_C(10);
  } while (value1 > 0);
  // (4) compute sign
  this->negative = false;
  return 0;
}

static inline int
apint10_from_uint8
  (
    apint10* this,
    uint8_t value
  )
{ return apint10_from_uint64(this, value); }

static inline int
apint10_compare_magnitudes
  (
    int* result,
    apint10* this,
    apint10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  if (this->size < other->size) {
    *result = -1;
    return 0;
  } else if (this->size > other->size) {
    *result = +1;
    return 0;
  } else {
    for (uint32_t i = this->size; i > 0; --i) {
      if (this->digits[i - 1] < other->digits[i - 1]) {
        *result = -1;
        return 0;
      } else if (this->digits[i - 1] > other->digits[i - 1]) {
        *result = +1;
        return 0;
      }
    }
  }
  *result = 0;
  return 0;
}

static inline int
apint10_compare
  (
    int* result,
    apint10* this,
    apint10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  if (this->negative &&  !other->negative) {
    // this is negative, other is non-negative
    // unless both are zero, a is smaller then b
    if (this->size == 1 && this->digits[0] == 0 && other->size == 1 && other->digits[0] == 0) {
      *result = 0;
      return 0;
    } else {
      *result = -1;
      return 0;
    }
  }
  if (!this->negative && other->negative) {
    // this is non-negative, other is negative
    // unless both are zero, a is greater then b
    if (this->size == 1 && this->digits[0] == 0 && other->size == 1 && other->digits[0] == 0) {
      *result = 0;
      return 0;
    } else {
      *result = +1;
      return 0;
    }
  }
  // both have the same sign, compare their magnitudes
  int temporary;
  if (apint10_compare_magnitudes(&temporary, this, other)) {
    return 1;
  }
  // Why is this correct?
  // Case 1: Both are negative including negative zero.
  // Case 1.1: Assume |a| < |b| holds (that is, -1 = temporary) then consequently b < a.
  //           Hence temporary must be negated to return -1.
  // Case 1.2: Assume |a| > |b| holds (that is, +1 = temporary) then consequently a < b.
  //           Hence temporary must be negated to return -1.
  // Case 1.3: Assume |a| = |b| holds (that is,  0 = temporary) then consequently a = b.
  //           Hence temporary can be negated or retained, however, the correct result is always 0.
  // Case 2: Both are non-negative including non-negative zero.
  // Case 2.1: Assume |a| < |b| holds (that is, -1 = temporary) then consequently a < b.
  //           Hence temporary must be retained to return -1.
  // Case 2.2: Assume |a| > |b| holds (that is, +1 = temporary) then consequently a > b.
  //           Hence temporary must be retained to return +1.
  // Case 2.3: Assume |a| = |b| holds (that is,  0 = temporary) then consequently a = b.
  //           Hence temporary can be negated or retained, however, the correct result is always 0.
  *result = this->negative ? +temporary : -temporary;
  return 0;
}

static inline int
apint10_swap
  (
    apint10* this,
    apint10* other
  )
{
  if (this == other) {
    return 0;
  }
  {
    uint8_t* t = this->digits;
    this->digits = other->digits;
    other->digits = t;
  }
  {
    uint32_t t = this->size;
    this->size = other->size;
    other->size = t;
  }
  {
    uint32_t t = this->capacity;
    this->capacity = other->capacity;
    other->capacity = t;
  }
  {
    bool t = this->negative;
    this->negative = other->negative;
    other->negative = t;
  }
  return 0;
}

static inline int
apint10_add
  (
    apint10* this,
    apint10* other
  ) 
{
  apint10* a = this;
  apint10* b = other;

  if (a->digits[0] == 0) {
    // special case: a is zero; result is b
    if (apint10_copy(a, b)) {
      return 1;
    }
    return 0;
  }
  if (b->digits[0] == 0) {
    // special case: b is zero, result is a
    return 0;
  }

  apint10 c;
  if (apint10_initialize(&c)) {
    return 1;
  }

  // INVARIANT: both this and other are non-zero
  if (a->negative == b->negative) {
    // INVARIANT: a and b have the same sign
    // STRATEGY: add their magnitudes
    
    if (a->size < b->size) {
      apint10* t = a;
      a = b;
      b = t;
    }
    // INVARIANT: |a| >= |b|     
    if (c.capacity < a->size + 1) {
      if (apint10_increase_capacity(&c, a->size + 1 - c.capacity)) {
        apint10_uninitialize(&c);
        return 1;
      }
      c.size = a->size + 1;
      for (uint32_t i = 0; i < c.size; ++i) {
        c.digits[i] = 0;
      }
    }
    uint8_t carry = 0; 
    apint10_size_type i = 0;
    // process digits common to a and b
    for (;i < b->size; ++i) {
      uint8_t result = a->digits[i] + b->digits[i] + carry; // 9 + 9 + 9 always fits the
      uint8_t digit = result % 10;
      carry = result / 10; // carry is never greater than 1
      c.digits[i] = digit;
    }
    // process digits specific to a
    for (; i < a->size; ++i) {
      uint8_t result = a->digits[i] + carry;
      uint8_t digit = result % 10;
      carry = result / 10; // carry is never greater than 1
      c.digits[i] = digit;
    }
    c.size = i;
    if (carry) {
      c.digits[c.size++] = carry;
    }
    c.negative = a->negative;
  } else {
    // INVARIANT: a and b have different signs
    // STRATEGY: subtract the smaller magnitude from the greater magnitude
    int result;
    if (apint10_compare_magnitudes(&result, a, b)) {
      return 1;
    }
    if (result > 0) {
      apint10* t = a;
      a = b;
      b = t;
    }
    // INVARIANT: |a| >= |b|

    if (c.capacity < a->size + 1) {
      if (apint10_increase_capacity(&c, (a->size + 1)- c.capacity)) {
        apint10_uninitialize(&c);
        return 1;
      }
      c.size = a->size + 1;
      for (uint32_t i = 0; i < c.size; ++i) {
        c.digits[i] = 0;
      }
    }
    uint8_t carry = 0;
    apint10_size_type i = 0;
    // process digits common to a and b
    for (; i < b->size; ++i) {
      uint8_t x = a->digits[i];
      uint8_t y = b->digits[i] + carry;
      carry = (y < carry);
      carry += (x < y);
      c.digits[i] = x - y;
    }
    // process digits specific to a
    for (; i < a->size; ++i) {
      uint8_t x = a->digits[i];
      uint8_t y = carry;
      carry = (x < y);
      c.digits[i] = x - y;
    }
    if (c.digits[i] == 0) {
      c.size = 1;
    } else {
      c.size = i;
    }
    c.size = i;
    if (carry) {
      c.digits[c.size++] = carry;
    }
    c.negative = a->negative;
  }

  apint10_swap(this, &c);

  apint10_uninitialize(&c);

  return 0;
}

static inline int
apint10_multiply
  (
    apint10* this,
    apint10* other
  )
{
  if (!this || !other) {
    return 1;
  }
  apint10* a = this;
  apint10* b = other;
  if (a->size < b->size) {
    apint10 *t = a;
    a = b;
    b = t;
  }

  apint10 c;
  if (apint10_initialize(&c)) {
    return 1;
  }
  if (c.capacity < a->size + b->size) {
    if (apint10_increase_capacity(&c, a->size + b->size - c.capacity)) {
      apint10_uninitialize(&c);
      return 1;
    }
    c.size = a->size + b->size;
    for (uint32_t i = 0; i < c.size; ++i) {
      c.digits[i] = 0;
    }
  }
  uint32_t i = 0;
  for (; i < a->size; ++i) {
    uint16_t carry = 0;
    uint32_t j = 0;
    for (; j < b->size || carry; ++j) {
      uint16_t current = c.digits[i + j] + a->digits[i] * (j < b->size ? b->digits[j] : 0) + carry;
      c.digits[i + j] = current % 10;
      carry = current / 10;
    }
  }
  // compute "negative"
  c.negative = a->negative != b->negative; 
  // trim zeroes above the MSB
  while (c.size > 0 && c.digits[c.size - 1] == 0) {
    c.size--;
  }
  if (c.size == 0) {
    c.size = 1;
  }

  apint10_swap(a, &c);

  apint10_uninitialize(&c);

  return 0;
}

static inline int
apint10_multiply_p10
  (
    apint10* this,
    uint64_t e
  )
{
  if (!e) {
    return 0;
  }
  if (this->size == 1 && this->digits[0] == 0) {
    return 0;
  }
  uint32_t available_free_capacity = this->capacity - this->size;
  uint32_t required_free_capacity = e;
  if (available_free_capacity < required_free_capacity) {
    if (apint10_increase_capacity(this, required_free_capacity - available_free_capacity)) {
      return 1;
    }
  }
  memmove(this->digits + e, this->digits, sizeof(uint8_t) * this->size);
  memset(this->digits, 0, sizeof(uint8_t) * e);
  this->size += e;
  return 0;
}

static inline int
apint10_divide_p10
  (
    apint10* this,
    uint64_t e
  )
{
  if (!e) {
    return 0;
  }
  if (this->size == 1 && this->digits[0] == 0) {
    return 0;
  }
  if (this->size <= e) {
    this->size = 1;
    this->digits[0] = 0;
    return 0;
  }
  memmove(this->digits, this->digits + e, sizeof(uint8_t) * (this->size - e));
  this->size -= e;
  return 0;
}

#endif // ARCADIA_RING1_SUPPORT_APINT10_H_INCLUDED
