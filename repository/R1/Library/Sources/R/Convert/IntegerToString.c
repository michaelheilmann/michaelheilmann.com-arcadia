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

#include "R/Convert/IntegerToString.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_Integer16_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Integer16Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Integer64_toString(process, memoryManager, value, buffer, bufferLength); }

void
Arcadia_Integer32_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Integer32Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Integer64_toString(process, memoryManager, value, buffer, bufferLength); }

void
Arcadia_Integer64_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Integer64Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{
  Arcadia_Integer64Value valueTemporary;
  Arcadia_SizeValue numberOfDigits = 0;
  Arcadia_SizeValue _bufferLength = 0;

  valueTemporary = value;
  if (!valueTemporary) {
    _bufferLength++;
    numberOfDigits++;
  } else {
    if (valueTemporary < 0) {
      while (value < 0) {
        valueTemporary /= 10;
        _bufferLength++;
        numberOfDigits++;
      }
    } else {
      while (valueTemporary > 0) {
        valueTemporary /= 10;
        _bufferLength++;
        numberOfDigits++;
      }
    }
  }

  char* _buffer = NULL;
  if (Arms_MemoryManager_allocate(memoryManager, &_buffer, _bufferLength)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }

  valueTemporary = value;
  char *p = _buffer;
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
        *(--q) = (char)digit;
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    } else {
      char* q = p + numberOfDigits;
      while (valueTemporary > 0) {
        Arcadia_Integer64Value digit = valueTemporary % 10;
        *(--q) = (char)digit;
        valueTemporary /= 10;
      }
      p += numberOfDigits;
    }
  }

  *buffer = _buffer;
  *bufferLength = _bufferLength;
}

void
Arcadia_Integer8_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_Integer8Value value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  )
{ Arcadia_Integer64_toString(process, memoryManager, value, buffer, bufferLength); }
