#include "R/BigInteger/add.h"

#include "R/BigInteger/digits.h"

// precondition: the magnitude of a must be greater than the magnitude of b
// Examples where this is applied:
// - a + b where the signs are different for example 2 + (-3) = -(|3|-|2|)
// - a - b where a and b are positive for example 2 - 3 = -(|3|-|2|)
// - ...
static void
Digits_subtractMagnitude
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  );

static void
Digits_addMagnitude
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  );

// precondition: the magnitude of a must be greater than the magnitude of b
// Examples where this is applied:
// - a + b where the signs are different for example 2 + (-3) = -(|3|-|2|)
// - a - b where a and b are positive for example 2 - 3 = -(|3|-|2|)
// - ...
static void
Digits_subtractMagnitude
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_BigInteger_Digit* digits1 = NULL;
  Arcadia_SizeValue maximalSize = a->size > b->size ? a->size : b->size;
  Arcadia_SizeValue capacity1 = maximalSize;
  Digits_allocate(process, &digits1, capacity1);
  // the signs are not equal, subtract the smaller magnitude from the greater magnitude.
  R_BigInteger_Digit carry = 0;
  Arcadia_SizeValue i, n;
  for (i = 0, n = b->size; i < n; ++i) {
    // Note: as the magnitude of a is greater than the magnitude of b,
    // the number of digits in a must be greater than or equal to the number of digits in b.
    R_BigInteger_Digit ad = a->digits[i];
    R_BigInteger_Digit bd = b->digits[i] + carry;
    carry = (bd < carry);
    carry += (ad < bd);
    digits1[i] = ad - bd;
  }
  for (i = b->size, n = a->size; i < n; ++i) {
    R_BigInteger_Digit ad = a->digits[i];
    R_BigInteger_Digit bd = carry;
    carry += (ad < bd);
    digits1[i] = ad - bd;
  }
  Arcadia_SizeValue size1;
  if (digits1[i] == 0) {
    size1 = 1;
  } else {
    size1 = i;
  }
  *digits = digits1;
  *capacity = capacity1;
  *size = size1;
  assert(!carry);
}

static void
Digits_addMagnitude
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  Arcadia_SizeValue maximalSize = a->size > b->size ? a->size : b->size;
  Arcadia_SizeValue minimalSize = a->size < b->size ? a->size : b->size;
  Arcadia_SizeValue size1 = 0;
  Arcadia_SizeValue capacity1 = maximalSize;
  R_BigInteger_Digit* digits1 = NULL;
  Digits_allocate(process, &digits1, capacity1);
  // We have digit sequences a1 ..., an and b1, ..., bm.
  // We add the part a1 + b1 + c1, ..., ak + bk + ck where k = min(n,m).
  R_BigInteger_DoubleDigit carry = 0;
  Arcadia_SizeValue i = 0, n = minimalSize;
  for (; i < n; ++i) {
    R_BigInteger_DoubleDigit x = a->digits[i] + b->digits[i] + carry;
    carry = ((x & R_BigInteger_DoubleDigit_UpperBitsMask) >> R_BigInteger_DoubleDigit_UpperBitsShift);
    R_BigInteger_Digit digit = (R_BigInteger_Digit)(x & R_BigInteger_DoubleDigit_LowerBitsMask) >> R_BigInteger_DoubleDigit_LowerBitsShift;
    digits1[i] = digit;
  }
  // Add the part a[k+1] + c[k+1], ..., a[n] + c[n] or b[k+1] + c[k+1], ..., b[m] + c[n]
  // depending on wether a or b is longer.
  if (a->size > b->size) {
    n = maximalSize;
    for (; i < n; ++i) {
      R_BigInteger_DoubleDigit x = a->digits[i] /* + b->digits[i]*/ + carry;
      carry = ((x & R_BigInteger_DoubleDigit_UpperBitsMask) >> R_BigInteger_DoubleDigit_UpperBitsShift);
      R_BigInteger_Digit digit = (R_BigInteger_Digit)(x & R_BigInteger_DoubleDigit_LowerBitsMask) >> R_BigInteger_DoubleDigit_LowerBitsShift;
      digits1[i] = digit;
    }
  } else {
    n = maximalSize;
    for (; i < n; ++i) {
      R_BigInteger_DoubleDigit x = b->digits[i] + carry;
      carry = ((x & R_BigInteger_DoubleDigit_UpperBitsMask) >> R_BigInteger_DoubleDigit_UpperBitsShift);
      R_BigInteger_Digit digit = (R_BigInteger_Digit)(x & R_BigInteger_DoubleDigit_LowerBitsMask) >> R_BigInteger_DoubleDigit_LowerBitsShift;
      digits1[i] = digit;
    }
  }
  size1 = i;

  if (carry) {
    capacity1 = capacity1 + 1;
    Digits_reallocate(process, &a->digits, capacity1);
    digits1[size1++] = carry;

  }
  *digits = digits1;
  *size = size1;
  *capacity = capacity1;
}

void
Digits_add
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (R_BigInteger_isZero(b)) {
    // b is zero. Return a.
    R_BigInteger_Digit* digits1 = NULL;
    Digits_allocate(process, &digits1, a->size);
    c_memcpy(digits1, a->digits, sizeof(R_BigInteger_Digit) * a->size);
    *digits = digits1;
    *size = a->size;
    *capacity = a->size;
    *sign = a->sign;
    return;
  }
  if (R_BigInteger_isZero(a)) {
    // a is zero. b is not zero.
    // Return -b.
    R_BigInteger_Digit* digits1 = NULL;
    Digits_allocate(process, &digits1, b->size);
    c_memcpy(digits1, b->digits, sizeof(R_BigInteger_Digit) * b->size);
    *digits = digits1;
    *size = b->size;
    *capacity = b->size;
    *sign = !b->sign;
    return;
  }
  if (a->sign == b->sign) {
    Digits_addMagnitude(process, digits, size, capacity, a, b);
    *sign = a->sign;
  } else {
    // the signs are not equal, subtract the smaller magnitude from the greater magnitude
    if (R_BigInteger_compareMagnitudes(a, b) > 0) {
      // a.magnitude is greater than b.magnitude
      // hence compute
      // a.magnitude = a.magnitude - b.magnitude
      Digits_subtractMagnitude(process, digits, size, capacity, a, b);
      if (*size == 1 && (*digits)[0] == 0) {
        *sign = Arcadia_BooleanValue_True;
      } else {
        *sign = a->sign;
      }
    } else {
      // a.magnitude is smaller than or equal to b.magnitude
      // hence compute
      // a.magnitude = b.magnitude - a.magnitude
      Digits_subtractMagnitude(process, digits, size, capacity, b, a);
      if (*size == 1 && (*digits)[0] == 0) {
        *sign = Arcadia_BooleanValue_True;
      } else {
        *sign = b->sign;
      }
    }
  }
}

void
Digits_subtract
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (R_BigInteger_isZero(b)) {
    // b is zero. Return a.
    R_BigInteger_Digit* digits1 = NULL;
    Digits_allocate(process, &digits1, a->size);
    c_memcpy(digits1, a->digits, sizeof(R_BigInteger_Digit) * a->size);
    *digits = digits1;
    *size = a->size;
    *capacity = a->size;
    *sign = a->sign;
    return;
  }
  if (R_BigInteger_isZero(a)) {
    // a is zero. b is not zero.
    // Return b.
    R_BigInteger_Digit* digits1 = NULL;
    Digits_allocate(process, &digits1, b->size);
    c_memcpy(digits1, b->digits, sizeof(R_BigInteger_Digit) * b->size);
    *digits = digits1;
    *size = b->size;
    *capacity = b->size;
    *sign = b->sign;
    return;
  }
  if (a->sign != a->sign) {
    // a is positive, b is negative
    // a is negative, b is positive
    Digits_addMagnitude(process, digits, size, capacity, a, b);
    *sign = a->sign;
    return;
  } else { 
    if (R_BigInteger_compareMagnitudes(a, b) > 0) {
      // the signs are equal, subtract the smaller magnitude from the greater magnitude
      // a.magnitude is greater than b.magnitude
      // hence compute
      // a.magnitude = a.magnitude - b.magnitude
      Digits_subtractMagnitude(process, digits, size, capacity, a, b);
      if (*size == 1 && (*digits)[0] == 0) {
        *sign = Arcadia_BooleanValue_True;
      } else {
        *sign = !a->sign;
      }
    } else {
      // a.magnitude is smaller than or equal to b.magnitude
      // hence compute
      // a.magnitude = b.magnitude - a.magnitude
      Digits_subtractMagnitude(process, digits, size, capacity, b, a);
      if (*size == 1 && (*digits)[0] == 0) {
        *sign = Arcadia_BooleanValue_True;
      } else {
        *sign = !a->sign;
      }
    }
  }
}
