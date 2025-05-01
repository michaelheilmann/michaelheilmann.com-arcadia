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

// Last modified: 2025-04-19

#include "Module/Visuals/Events/CanvasActivationStateChangedEvent.h"

#include "R/ArgumentsValidation.h"

static void
Arcadia_Visuals_CanvasActivationStateChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_CanvasActivationStateChangedEvent_constructImpl,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.CanvasActivationStateChangedEvent", Arcadia_Visuals_CanvasActivationStateChangedEvent, u8"Arcadia.Visuals.CanvasEvent", Arcadia_Visuals_CanvasEvent, &_typeOperations);

static void
Arcadia_Visuals_CanvasActivationStateChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_CanvasActivationStateChangedEvent* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_CanvasActivationStateChangedEvent_getType(thread);
  {
    if (2 != numberOfArgumentValues) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  //
  _self->active = R_Argument_getBooleanValue(thread, &argumentValues[1]);
  //
  Arcadia_Object_setType(thread, _self, _type);  
}

Arcadia_Visuals_CanvasActivationStateChangedEvent*
Arcadia_Visuals_CanvasActivationStateChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timeStamp,
    Arcadia_BooleanValue active
  )
{
  Arcadia_Value argumentValues[] = { { .tag = Arcadia_ValueTag_Natural64, .natural64Value = timeStamp },
                                     { .tag = Arcadia_ValueTag_Boolean, .booleanValue = active }, };
  Arcadia_Visuals_CanvasActivationStateChangedEvent* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_CanvasActivationStateChangedEvent_getType(thread), 2, &argumentValues[0]);
  return self;
}
