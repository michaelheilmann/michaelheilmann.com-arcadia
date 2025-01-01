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

// Last modified: 2024-09-26

#include "R/Convert/NaturalToString.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_Natural16_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Natural16Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Natural64_toString(process, memoryManager, value, buffer, bufferLength); }

void
Arcadia_Natural32_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Natural32Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Natural64_toString(process, memoryManager, value, buffer, bufferLength); }

void
Arcadia_Natural64_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Natural64Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{
  Arcadia_Natural64Value valueTemporary;
  Arcadia_SizeValue numberOfDigits = 0;
  Arcadia_SizeValue _bufferLength = 0;

  valueTemporary = value;
  if (!valueTemporary) {
    _bufferLength++;
    numberOfDigits++;
  } else {
    while (valueTemporary > 0) {
      valueTemporary /= 10;
      _bufferLength++;
      numberOfDigits++;
    }
  }

  char* _buffer = NULL;
  if (Arms_MemoryManager_allocate(memoryManager, &_buffer, _bufferLength)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }

  valueTemporary = value;
  char* p = _buffer;
  if (!valueTemporary) {
    *p = (char)'0';
    ++p;
  } else {
    char* q = p + numberOfDigits;
    while (valueTemporary > 0) {
      Arcadia_Natural64Value digit = valueTemporary % 10;
      *(--q) = (char)digit;
      valueTemporary /= 10;
    }
    p += numberOfDigits;
  }

  *buffer = _buffer;
  *bufferLength = _bufferLength;
}

void
Arcadia_Natural8_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Natural8Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Natural64_toString(process, memoryManager, value, buffer, bufferLength); }
