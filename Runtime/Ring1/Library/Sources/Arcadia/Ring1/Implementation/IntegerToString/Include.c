// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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
Arcadia_Integer16Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUtf8String(thread, integer16Value, context, function); }

void
Arcadia_Integer32Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUtf8String(thread, integer32Value, context, function); }

void
Arcadia_Integer64Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
  // TODO: Properly determine the maximal length.
  static Arcadia_Natural8Value bytes[512];
  
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
Arcadia_Integer8Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Integer64Value_toUtf8String(thread, integer8Value, context, function); }
