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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

#define Arcadia_Utf8CodePoint_Last (0x0010ffff)
Arcadia_StaticAssert(Arcadia_Utf8CodePoint_Last <= Arcadia_Natural32Value_Maximum - 3, "<internal error>");

static Arcadia_BooleanValue
_isUtf8
  (
    Arcadia_Process1* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  );

static Arcadia_BooleanValue
_isUtf8
  (
    Arcadia_Process1* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  )
{
  Arcadia_SizeValue numberOfSymbols1 = 0;
  uint8_t const* start = (uint8_t const*)bytes;
  uint8_t const* end = start + numberOfBytes;
  uint8_t const* current = start;

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      current += 1;
      numberOfSymbols1++;
    } else if (x <= 0x7ff) {
      if (end - current < 2) {
        if (numberOfSymbols) {
          *numberOfSymbols = numberOfSymbols1;
        }
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
          return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0xffff) {
      if (end - current < 3) {
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
         return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0x10ffff) {
      if (end - current < 4) {
        if (numberOfSymbols) {
          *numberOfSymbols = numberOfSymbols1;
        }
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
          return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else {
      return Arcadia_BooleanValue_False;
    }
  }
  if (numberOfSymbols) {
    *numberOfSymbols = numberOfSymbols1;
  }
  return Arcadia_BooleanValue_True;
}

Arcadia_ImmutableUtf8String*
_createFromBytes
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);   
  }
  if (SIZE_MAX - sizeof(Arcadia_ImmutableUtf8String) < numberOfBytes) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  if (!_isUtf8(process, bytes, numberOfBytes, NULL)) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_EncodingInvalid);
    Arcadia_Process1_jump(process);
  }
  _ensureTypeRegistered(process);
  Arcadia_ImmutableUtf8String* string = NULL;
  Arcadia_Process1_allocate(process, &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + numberOfBytes);
  Arcadia_Process1_copyMemory(process, string->bytes, bytes, numberOfBytes);
  string->numberOfBytes = numberOfBytes;
  string->hash = _hashUtf8(process, string->bytes, string->numberOfBytes);
  return string;
}
