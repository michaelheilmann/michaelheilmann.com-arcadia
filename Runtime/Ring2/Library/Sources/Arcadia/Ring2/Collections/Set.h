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

#if !defined(ARCADIA_RING2_COLLECTIONS_SET_H_INCLUDED)
#define ARCADIA_RING2_COLLECTIONS_SET_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Collections/Collection.h"

Arcadia_declareObjectType(u8"Arcadia.Set", Arcadia_Set,
                          u8"Arcadia.Collection");

struct Arcadia_Set {
  Arcadia_Collection parent;

  void (*add)(Arcadia_Thread* thread, Arcadia_Set* self, Arcadia_Value value, Arcadia_Value* oldValue);
  Arcadia_BooleanValue(*contains)(Arcadia_Thread* thread, Arcadia_Set* self, Arcadia_Value value);
  Arcadia_Value(*get)(Arcadia_Thread* thread, Arcadia_Set* self, Arcadia_Value value);
  void (*remove)(Arcadia_Thread* thread, Arcadia_Set* self, Arcadia_Value value, Arcadia_Value* oldValue);
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Set_add
void
Arcadia_Set_add
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Set_contains
Arcadia_BooleanValue
Arcadia_Set_contains
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Set_get
Arcadia_Value
Arcadia_Set_get
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Set_remove
void
Arcadia_Set_remove
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  );

#endif // ARCADIA_RING2_COLLECTIONS_SET_H_INCLUDED
