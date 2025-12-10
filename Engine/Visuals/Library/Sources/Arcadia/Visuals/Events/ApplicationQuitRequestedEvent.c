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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.h"

#include "Arcadia/Visuals/Include.h"

static void
Arcadia_Visuals_ApplicationQuitRequestedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationQuitRequestedEvent* self
  );

static void
Arcadia_Visuals_ApplicationQuitRequestedEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationQuitRequestedEventDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Visuals_ApplicationQuitRequestedEvent_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.ApplicationQuitRequestedEvent", Arcadia_Visuals_ApplicationQuitRequestedEvent,
                         u8"Arcadia.Visuals.ApplicationEvent", Arcadia_Visuals_ApplicationEvent,
                         &_typeOperations);

static void
Arcadia_Visuals_ApplicationQuitRequestedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationQuitRequestedEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_ApplicationQuitRequestedEvent_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1); // pop number of arguments
  if (2 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural64Value(thread, Arcadia_ValueStack_getNatural64Value(thread, 1));
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 0, _Arcadia_Visuals_BackendContext_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1);
}

static void
Arcadia_Visuals_ApplicationQuitRequestedEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationQuitRequestedEventDispatch* self
  )
{ }

Arcadia_Visuals_ApplicationQuitRequestedEvent*
Arcadia_Visuals_ApplicationQuitRequestedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural64Value(thread, timestamp);
  if (backendContext) { Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); } else { Arcadia_ValueStack_pushObjectReferenceValue(thread, Arcadia_VoidValue_Void); }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_ApplicationQuitRequestedEvent);
}
