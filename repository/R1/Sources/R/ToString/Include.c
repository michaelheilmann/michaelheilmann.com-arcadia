// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-26

#include "R/ToString/Include.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Utf8.h"
#include "R/cstdlib.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t
R_Integer16_toString
  (
    R_Integer16Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Integer64_toString(value, buffer, bufferLength); }

size_t
R_Integer32_toString
  (
    R_Integer32Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Integer64_toString(value, buffer, bufferLength); }

size_t
R_Integer64_toString
  (
    R_Integer64Value value,
    char* buffer,
    size_t bufferLength
  )
{
  R_Integer64Value valueTemporary;
  size_t numberOfDigits = 0;
  size_t requiredBufferLength = 0;

  valueTemporary = value;
  if (!valueTemporary) {
    requiredBufferLength++;
    numberOfDigits++;
  } else {
    if (valueTemporary < 0) {
      while (value < 0) {
        valueTemporary /= 10;
        requiredBufferLength++;
        numberOfDigits++;
      }
    } else {
      while (valueTemporary > 0) {
        valueTemporary /= 10;
        requiredBufferLength++;
        numberOfDigits++;
      }
    }
  }

  if (!buffer || bufferLength < requiredBufferLength) {
    return requiredBufferLength;
  }

  valueTemporary = value;
  char *p = buffer;
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    if (valueTemporary < 0) {
      *p = (char)'-';
      ++p;
      char* q = p + numberOfDigits;
      while (valueTemporary < 0) {
        R_Integer64Value digit = -(valueTemporary % 10);
        *(--q) = (char)digit;
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    } else {
      char* q = p + numberOfDigits;
      while (valueTemporary > 0) {
        R_Integer64Value digit = valueTemporary % 10;
        *(--q) = (char)digit;
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    }
  }

  return requiredBufferLength;
}

size_t
R_Integer8_toString
  (
    R_Integer8Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Integer64_toString(value, buffer, bufferLength); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t
R_Natural16_toString
  (
    R_Natural16Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Natural64_toString(value, buffer, bufferLength); }

size_t
R_Natural32_toString
  (
    R_Natural32Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Natural64_toString(value, buffer, bufferLength); }

size_t
R_Natural64_toString
  (
    R_Natural64Value value,
    char* buffer,
    size_t bufferLength
  )
{
  R_Natural64Value valueTemporary;
  size_t numberOfDigits = 0;
  size_t requiredBufferLength = 0;

  valueTemporary = value;
  if (!valueTemporary) {
    requiredBufferLength++;
    numberOfDigits++;
  } else {
    while (valueTemporary > 0) {
      valueTemporary /= 10;
      requiredBufferLength++;
      numberOfDigits++;
    }
  }

  if (!buffer || bufferLength < requiredBufferLength) {
    return requiredBufferLength;
  }

  valueTemporary = value;
  char* p = buffer;
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    char* q = p + numberOfDigits;
    while (valueTemporary > 0) {
      R_Integer64Value digit = valueTemporary % 10;
      *(--q) = (char)digit;
      valueTemporary /= 10;
    }
    p += numberOfDigits;
  }

  return requiredBufferLength;
}

size_t
R_Natural8_toString
  (
    R_Natural8Value value,
    char* buffer,
    size_t bufferLength
  )
{ return R_Natural64_toString(value, buffer, bufferLength); }


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
