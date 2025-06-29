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
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromSize.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

Arcadia_ImmutableUtf8String*
_createFromSize
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue
  )
{
  Arcadia_SizeValue valueTemporary;
  Arcadia_SizeValue numberOfDigits = 0;
  Arcadia_SizeValue numberOfBytes = 0;

  valueTemporary = sizeValue;
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

  if (SIZE_MAX - sizeof(Arcadia_ImmutableUtf8String) < numberOfBytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }

  _ensureTypeRegistered(thread);

  Arcadia_ImmutableUtf8String* string = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + numberOfBytes);

  valueTemporary = sizeValue;
  char* p = string->bytes;
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    char* q = p + numberOfDigits;
    while (valueTemporary > 0) {
      Arcadia_SizeValue digit = valueTemporary % 10;
      *(--q) = (char)digit + '0';
      valueTemporary /= 10;
    }
    p += numberOfDigits;
  }

  string->numberOfBytes = numberOfBytes;
  string->hash = _hashUtf8(thread, string->bytes, string->numberOfBytes);

  return string;
}
