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

#include "R/Convert/BooleanToString.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/cstdlib.h"

void
R_Boolean_toString
  (
    Arms_MemoryManager* memoryManager,
    R_BooleanValue value,
    char** buffer,
    R_SizeValue* bufferLength
  )
{
  char* _buffer = NULL;
  size_t _bufferLength;
  if (value) {
     _bufferLength = sizeof(u8"true") - 1;
    if (Arms_MemoryManager_allocate(memoryManager, &_buffer, _bufferLength)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    c_memcpy(_buffer, u8"true", _bufferLength);
  } else {
     _bufferLength = sizeof(u8"false") - 1;
    if (Arms_MemoryManager_allocate(memoryManager, &_buffer, _bufferLength)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    c_memcpy(_buffer, u8"false", _bufferLength);
  }
  *buffer = _buffer;
  *bufferLength = _bufferLength;
}
