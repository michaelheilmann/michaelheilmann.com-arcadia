// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/IntegerToString/Include.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_Integer16Value_toUTF8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUTF8String(thread, integer16Value, context, function); }

void
Arcadia_Integer32Value_toUTF8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUTF8String(thread, integer32Value, context, function); }

void
Arcadia_Integer64Value_toUTF8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
  // The maximum value of a int64_t is 2^63-1 = 9,223,372,036,854,775,807.
  // The minimum value of a int64_t is 2^64 = 9,223,372,036,854,775,808.
  // These are 19 decimal digit symbol.
  // Plus one more symbol for the sign, these are 20 symbols.
  // We allocate 32 symbols in paranoia mode.
  // Note we do not use a static buffer to be thread-safe.
  Arcadia_Natural8Value bytes[32];

  Arcadia_Integer64Value valueTemporary;
  Arcadia_SizeValue numberOfDigits = 0;
  Arcadia_SizeValue numberOfBytes = 0;

  valueTemporary = integer64Value;
  if (!valueTemporary) {
    numberOfBytes++;
    numberOfDigits++;
  } else {
    if (valueTemporary < 0) {
      numberOfBytes++; // for the sign
      while (valueTemporary < 0) {
        valueTemporary /= 10;
        numberOfBytes++;
        numberOfDigits++;
      }
    } else {
      while (valueTemporary > 0) {
        valueTemporary /= 10;
        numberOfBytes++;
        numberOfDigits++;
      }
    }
  }

  valueTemporary = integer64Value;
  char *p = &(bytes[0]);
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    if (valueTemporary < 0) {
      *p = (char)'-';
      ++p;
      char* q = p + numberOfDigits;
      while (valueTemporary < 0) {
        Arcadia_Integer64Value digit = -(valueTemporary % 10);
        *(--q) = (char)digit + '0';
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    } else {
      char* q = p + numberOfDigits;
      while (valueTemporary > 0) {
        Arcadia_Integer64Value digit = valueTemporary % 10;
        *(--q) = (char)digit + '0';
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    }
  }

  (*function)(thread, context, bytes, numberOfBytes);
}

void
Arcadia_Integer8Value_toUTF8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUTF8String(thread, integer8Value, context, function); }
