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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SLOT_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SLOT_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Object.h"
#include "Arcadia/Ring1/Implementation/WeakReference.h"
#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"
typedef struct Arcadia_Signal Arcadia_Signal;

Arcadia_declareObjectType(u8"Arcadia.Slot", Arcadia_Slot,
                          u8"Arcadia.Object");

struct Arcadia_SlotDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Slot {
  Arcadia_Object _parent;
  // Weak reference to the signal.
  Arcadia_WeakReference* signal;
  // Weak reference to the receiver.
  Arcadia_WeakReference* receiver;
  // The foreign procedure to invoke.
  Arcadia_ForeignProcedure* procedure;
};

// Create a connection which is associated with a signal but no node of the signal.
Arcadia_Slot*
Arcadia_Slot_create
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* signal,
    Arcadia_Object* receiver,
    Arcadia_ForeignProcedure* procedure
  );
  
void
Arcadia_Slot_disconnect
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* slot
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SLOT_H_INCLUDED
