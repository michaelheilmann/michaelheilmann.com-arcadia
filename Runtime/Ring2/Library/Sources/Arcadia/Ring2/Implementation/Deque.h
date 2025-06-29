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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_DEQUE_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_DEQUE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Deque", Arcadia_Deque, u8"Arcadia.Object");

Arcadia_Deque*
Arcadia_Deque_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Deque*
Arcadia_Deque_clone
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

void
Arcadia_Deque_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

Arcadia_SizeValue
Arcadia_Deque_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Deque const* self
  );

void
Arcadia_Deque_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  );

void
Arcadia_Deque_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  );

void
Arcadia_Deque_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  );

Arcadia_Value
Arcadia_Deque_getFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

Arcadia_Value
Arcadia_Deque_getBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

Arcadia_Value
Arcadia_Deque_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  );

void
Arcadia_Deque_removeFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

void
Arcadia_Deque_removeBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

void
Arcadia_Deque_removeAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_DEQUE_H_INCLUDED
