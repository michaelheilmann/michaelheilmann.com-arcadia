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
#include "Arcadia/Ring1/Implementation/NaturalToString/Include.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_Natural16Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Natural64Value_toUtf8String(thread, natural16Value, context, function); }

void
Arcadia_Natural32Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Natural64Value_toUtf8String(thread, natural32Value, context, function); }

void
Arcadia_Natural64Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
  // TODO: Properly determine the maximal length.
  static Arcadia_Natural8Value bytes[512];

  Arcadia_Natural64Value valueTemporary;
  Arcadia_SizeValue numberOfDigits = 0;
  Arcadia_SizeValue numberOfBytes = 0;

  valueTemporary = natural64Value;
  if (!valueTemporary) {
    numberOfBytes++;
    numberOfDigits++;
  } else {
    while (valueTemporary > 0) {
      valueTemporary /= 10;
      numberOfBytes++;
      numberOfDigits++;
    }
  }

  valueTemporary = natural64Value;
  char* p = &(bytes[0]);
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    char* q = p + numberOfDigits;
    while (valueTemporary > 0) {
      Arcadia_Natural64Value digit = valueTemporary % 10;
      *(--q) = (char)digit + '0';
      valueTemporary /= 10;
    }
    p += numberOfDigits;
  }

  (*function)(thread, context, bytes, numberOfBytes);
}

void
Arcadia_Natural8Value_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{ Arcadia_Natural64Value_toUtf8String(thread, natural8Value, context, function); }
