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

#include "Module/Visuals/Events/KeyboardKeyEvent.h"

static void
Arcadia_Visuals_KeyboardKeyEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_KeyboardKeyEvent_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.KeyboardKeyEvent", Arcadia_Visuals_KeyboardKeyEvent, u8"Arcadia.Visuals.Event", Arcadia_Visuals_Event, &_typeOperations);

static void
Arcadia_Visuals_KeyboardKeyEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_KeyboardKeyEvent* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_KeyboardKeyEvent_getType(thread);
  {
    if (3 != numberOfArgumentValues) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  //
  _self->action = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[1]);
  _self->key = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[2]);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Visuals_KeyboardKeyEvent*
Arcadia_Visuals_KeyboardKeyEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_KeyboardKey key,
    Arcadia_Visuals_KeyboardKeyAction action
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural64Value(timestamp),
    Arcadia_Value_makeInteger32Value(action),
    Arcadia_Value_makeInteger32Value(key),
  };
  Arcadia_Visuals_KeyboardKeyEvent* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread), 3, &argumentValues[0]);
  return self;
}

Arcadia_Visuals_KeyboardKeyAction
Arcadia_Visuals_KeyboardKeyEvent_getAction
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  )
{ return self->action; }

Arcadia_Visuals_KeyboardKey
Arcadia_Visuals_KeyboardKeyEvent_getKey
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  )
{ return self->key; }
