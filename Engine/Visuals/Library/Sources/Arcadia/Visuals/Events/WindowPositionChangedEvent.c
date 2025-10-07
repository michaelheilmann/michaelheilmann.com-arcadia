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
#include "Arcadia/Visuals/Events/WindowPositionChangedEvent.h"

#include "Arcadia/Visuals/Include.h"

static void
Arcadia_Visuals_WindowPositionChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowPositionChangedEvent* self
  );

static void
Arcadia_Visuals_WindowPositionChangedEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowPositionChangedEvent* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_WindowPositionChangedEvent_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_WindowPositionChangedEvent_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.WindowPositionChangedEvent", Arcadia_Visuals_WindowPositionChangedEvent,
                         u8"Arcadia.Engine.Event", Arcadia_Engine_Event,
                         &_typeOperations);

static void
Arcadia_Visuals_WindowPositionChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowPositionChangedEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_WindowPositionChangedEvent_getType(thread);
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1); // pop number of arguments
  if (4 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural64Value(thread, Arcadia_ValueStack_getNatural64Value(thread, 3));
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->window = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Window_getType(thread));
  self->horizontalPosition = Arcadia_ValueStack_getInteger32Value(thread, 1);
  self->verticalPosition = Arcadia_ValueStack_getInteger32Value(thread, 0);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1);
}

static void
Arcadia_Visuals_WindowPositionChangedEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowPositionChangedEvent* self
  )
{
  if (self->window) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->window);
  }
}

Arcadia_Visuals_WindowPositionChangedEvent*
Arcadia_Visuals_WindowPositionChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_Window* window,
    Arcadia_Integer32Value horizontalPosition,
    Arcadia_Integer32Value verticalPosition
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural64Value(thread, timestamp);
  if (window) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, window);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushInteger32Value(thread, horizontalPosition);
  Arcadia_ValueStack_pushInteger32Value(thread, verticalPosition);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_WindowPositionChangedEvent);
}
