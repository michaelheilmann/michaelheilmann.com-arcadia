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
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_WindowPositionChangedEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowPositionChangedEvent* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_WindowPositionChangedEvent_constructImpl,
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
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_WindowPositionChangedEvent* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_WindowPositionChangedEvent_getType(thread);
  {
    if (4 != numberOfArgumentValues) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  //
  _self->window = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_Visuals_Window_getType(thread));
  _self->horizontalPosition = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[2]);
  _self->verticalPosition = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[3]);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
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
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural64Value(timestamp),
    window ? Arcadia_Value_makeObjectReferenceValue(window) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    Arcadia_Value_makeInteger32Value(horizontalPosition),
    Arcadia_Value_makeInteger32Value(verticalPosition),
  };
  Arcadia_Visuals_WindowPositionChangedEvent* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_WindowPositionChangedEvent_getType(thread), 4, &argumentValues[0]);
  return self;
}
