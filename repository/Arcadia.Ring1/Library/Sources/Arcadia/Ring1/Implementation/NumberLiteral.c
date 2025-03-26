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

// Last modified: 2024-10-27

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/NumberLiteral.h"

static inline Arcadia_NumberLiteral_Sign
Arcadia_NumberLiteral_Sign_empty
  (
    Arcadia_SizeValue start
  )
{
  Arcadia_NumberLiteral_Sign instance = { .start = start, .length = 0 };
  return instance;
}

static inline Arcadia_NumberLiteral_Fractional
Arcadia_NumberLiteral_Fractional_empty
  (
    Arcadia_SizeValue start
  )
{
  Arcadia_NumberLiteral_Fractional instance = { .start = start, .length = 0, .trailingZeroes.start = start, .trailingZeroes.length = 0 };
  return instance;
}

static inline Arcadia_NumberLiteral_Integral
Arcadia_NumberLiteral_Integral_empty
  (
    Arcadia_SizeValue start
  )
{
  Arcadia_NumberLiteral_Integral instance = { .start = start, .length = 0, .leadingZeroes.start = start, .leadingZeroes.length = 0 };
  return instance;
}

static inline Arcadia_NumberLiteral_Exponent
Arcadia_NumberLiteral_Exponent_empty
  (
    Arcadia_SizeValue start
  )
{
  Arcadia_NumberLiteral_Exponent instance = {
    .start = start,
    .length = 0,
    .integral = Arcadia_NumberLiteral_Integral_empty(start),
    .powerSymbol.start = start,
    .powerSymbol.length = 0,
    .sign = Arcadia_NumberLiteral_Sign_empty(start)
  };
  return instance;
}

static inline Arcadia_NumberLiteral
Arcadia_NumberLiteral_empty
  (
    Arcadia_SizeValue start
  )
{
  Arcadia_NumberLiteral instance = {
    .significand.sign = Arcadia_NumberLiteral_Sign_empty(start),
    .significand.integral = Arcadia_NumberLiteral_Integral_empty(start),
    .significand.fractional = Arcadia_NumberLiteral_Fractional_empty(start),
    .significand.radixPoint.start = start,
    .significand.radixPoint.length = 0,
    .exponent = Arcadia_NumberLiteral_Exponent_empty(start),
  };
  return instance;
}

Arcadia_BooleanValue
Arcadia_parseNumberLiteral
  (
    Arcadia_Thread* thread,
    Arcadia_NumberLiteral* result,
    const Arcadia_Natural8Value* source,
    Arcadia_SizeValue sourceLength
  )
{
  Arcadia_SizeValue i = 0;
  Arcadia_SizeValue n = sourceLength;

  Arcadia_NumberLiteral number = Arcadia_NumberLiteral_empty(0);

  // Parse "significand.sign".
  if (i == n) {
    return Arcadia_BooleanValue_False;
  }
  number.significand.sign.start = i;
  switch (source[i]) {
    case '+':
    case '-': {
      number.significand.sign.start = i;
      number.significand.sign.length = 1;
      i++;
    } break;
  };

  // Parse "significand.integral".
  number.significand.integral.start = i;
  number.significand.integral.length = 0;
  number.significand.integral.leadingZeroes.start = i;
  number.significand.integral.leadingZeroes.length = 0;
  // Count leading zeroes of "significand.integral".
  while (i < n && source[i] == '0') {
    number.significand.integral.leadingZeroes.length++;
    number.significand.integral.length++;
    i++;
  }
  while (i < n && '0' <= source[i] && source[i] <= '9') {
    number.significand.integral.length++;
    i++;
  }
  // Parse "significand.radixPoint".
  if (i == n) {
    number.exponent = Arcadia_NumberLiteral_Exponent_empty(i);
    number.significand.radixPoint.start = i;
    number.significand.radixPoint.length = 0;
    number.significand.fractional = Arcadia_NumberLiteral_Fractional_empty(i);
    *result = number;
    if (number.significand.integral.length == 0) {
      return Arcadia_BooleanValue_False;
    } else {
      return Arcadia_BooleanValue_True;
    }
  }
  if (source[i] == '.') {
    number.significand.radixPoint.start = i;
    number.significand.radixPoint.length = 1;
    i++;
    if (i == n) {
      number.exponent = Arcadia_NumberLiteral_Exponent_empty(i);
      number.significand.fractional = Arcadia_NumberLiteral_Fractional_empty(i);
      *result = number;
      if (number.significand.integral.length == 0) {
        return Arcadia_BooleanValue_True;
      } else {
        return Arcadia_BooleanValue_True;
      }
    }
  } else {
    number.significand.radixPoint.start = i;
    number.significand.radixPoint.length = 0;
  }
  // Parse "significand.fractional".
  number.significand.fractional.start = i;
  while (i < n && '0' <= source[i] && source[i] <= '9') {
    number.significand.fractional.length++;
    i++;
  }
  // Count trailing zeroes of "significand.fractional".
  number.significand.fractional.trailingZeroes.start = number.significand.fractional.start + number.significand.fractional.length;
  number.significand.fractional.trailingZeroes.length = 0;
  for (Arcadia_SizeValue i = number.significand.fractional.start + number.significand.fractional.length; i > number.significand.fractional.start; --i) {
    if (source[i - 1] != '0') {
      break;
    }
    number.significand.fractional.trailingZeroes.start--;
    number.significand.fractional.trailingZeroes.length++;
    
  }
  if (i == n) {
    number.exponent = Arcadia_NumberLiteral_Exponent_empty(i);
    *result = number;
    if (number.significand.integral.length == 0 && number.significand.fractional.length == 0) {
      return Arcadia_BooleanValue_False;
    } else {
      return Arcadia_BooleanValue_True;
    }
  }
  // Parse "exponent".
  number.exponent.start = i;
  switch (source[i]) {
    case 'e':
    case 'E':
    case '^': {
      number.exponent.powerSymbol.start = i;
      number.exponent.powerSymbol.length = 1;
      number.exponent.length++;
      i++;
    } break;
    default: {
      number.exponent.length = 1;
      number.exponent.sign = Arcadia_NumberLiteral_Sign_empty(i);
      number.exponent.integral = Arcadia_NumberLiteral_Integral_empty(i);
      *result = number;
      return Arcadia_BooleanValue_False;
    } break;
  }
  if (i == n) {
    number.exponent.length = 1;
    number.exponent.sign = Arcadia_NumberLiteral_Sign_empty(i);
    number.exponent.integral = Arcadia_NumberLiteral_Integral_empty(i);
    *result = number;
    return Arcadia_BooleanValue_False;
  }
  switch (source[i]) {
    case '+':
    case '-': {
      number.exponent.sign.start = i;
      number.exponent.sign.length = 1;
      number.exponent.length++;
      i++;
    } break;
    default: {
      number.exponent.sign.start = i;
      number.exponent.sign.length = 0;
    } break;
  }
  number.exponent.integral.start = i;
  number.exponent.integral.leadingZeroes.start = i;
  // Count leading zeroes of "exponent.integral".
  while (i < n && source[i] == '0') {
    number.exponent.integral.leadingZeroes.length++;
    number.exponent.integral.length++;
    number.exponent.length++;
    i++;
  }
  while (i < n && '0' <= source[i] && source[i] <= '9') {
    number.exponent.integral.length++;
    number.exponent.length++;
    i++;
  }
  *result = number;
  if (i != n || number.exponent.integral.length == 0) {
    return Arcadia_BooleanValue_False;
  }
  return Arcadia_BooleanValue_True;
}
