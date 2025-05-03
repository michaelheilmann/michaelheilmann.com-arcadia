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
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

Arcadia_ImmutableUtf8String*
_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  )
{ return _createFromInteger64(thread, integer16Value); }

Arcadia_ImmutableUtf8String*
_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{ return _createFromInteger64(thread, integer32Value); }

Arcadia_ImmutableUtf8String*
_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
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

  if (SIZE_MAX - sizeof(Arcadia_ImmutableUtf8String) < numberOfBytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  
  _ensureTypeRegistered(thread);
  
  Arcadia_ImmutableUtf8String* string = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + numberOfBytes);

  valueTemporary = integer64Value;
  char *p = string->bytes;
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

  string->numberOfBytes = numberOfBytes;
  string->hash = _hashUtf8(thread, string->bytes, string->numberOfBytes);
  
  return string;
}

Arcadia_ImmutableUtf8String*
_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{ return _createFromInteger64(thread, integer8Value); }
