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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_WEAKREFERENCE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_WEAKREFERENCE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Object.h"

Arcadia_declareObjectType(u8"Arcadia.WeakReference", Arcadia_WeakReference,
                          u8"Arcadia.Object");

struct Arcadia_WeakReferenceDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_WeakReference {
  Arcadia_Object _parent;
  Arcadia_Value value;
};

Arcadia_WeakReference*
Arcadia_WeakReference_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  );

Arcadia_Value
Arcadia_WeakReference_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_WEAKREFERENCE_H_INCLUDED
