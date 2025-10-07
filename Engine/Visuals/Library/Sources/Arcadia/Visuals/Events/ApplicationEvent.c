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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Events/ApplicationEvent.h"

#include "Arcadia/Visuals/System.h"

static void
Arcadia_Visuals_ApplicationEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationEvent* self
  );

static void
Arcadia_Visuals_ApplicationEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationEvent* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_ApplicationEvent_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_ApplicationEvent_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.ApplicationEvent", Arcadia_Visuals_ApplicationEvent,
                         u8"Arcadia.Engine.Event", Arcadia_Engine_Event,
                         &_typeOperations);

static void
Arcadia_Visuals_ApplicationEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_ApplicationEvent_getType(thread);
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
  //
  self->system = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 0, _Arcadia_Visuals_System_getType(thread));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Visuals_ApplicationEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_ApplicationEvent* self
  )
{
  if (self->system) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->system);
  }
}
