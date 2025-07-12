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

#include "Module/Visuals/Events/MousePointerEvent.h"

static void
Arcadia_Visuals_MousePointerEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_MousePointerEvent_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.MousePointerEvent", Arcadia_Visuals_MousePointerEvent, u8"Arcadia.Visuals.Event", Arcadia_Visuals_Event, &_typeOperations);

static void
Arcadia_Visuals_MousePointerEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_MousePointerEvent* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_MousePointerEvent_getType(thread);
  {
    if (4 != numberOfArgumentValues) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  //
  _self->action = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[1]);
  _self->x = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[2]);
  _self->x = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[3]);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Visuals_MousePointerEvent*
Arcadia_Visuals_MousePointerEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_MousePointerAction action,
    Arcadia_Integer32Value x,
    Arcadia_Integer32Value y
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural64Value(timestamp),
    Arcadia_Value_makeInteger32Value(action),
    Arcadia_Value_makeInteger32Value(x),
    Arcadia_Value_makeInteger32Value(y),
  };
  Arcadia_Visuals_MousePointerEvent* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_MousePointerEvent_getType(thread), 4, &argumentValues[0]);
  return self;
}
