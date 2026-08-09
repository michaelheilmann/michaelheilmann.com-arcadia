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

#include "Arcadia/Starship/PositionChangeInputEvent.h"

static void
Arcadia_Starship_PositionChangeInputEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Starship_PositionChangeInputEvent* self
  );

static void
Arcadia_Starship_PositionChangeInputEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Starship_PositionChangeInputEventDispatch* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Starship_PositionChangeInputEvent_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Starship_PositionChangeInputEvent_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Starship_PositionChangeInputEvent_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_Starship_PositionChangeInputEvent_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Starship_PositionChangeInputEvent_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Starship.PositionChangeInputEvent", Arcadia_Starship_PositionChangeInputEvent,
                         u8"Arcadia.Engine.Event", Arcadia_Engine_Event,
                         &_Arcadia_Starship_PositionChangeInputEvent_typeOperations);

static void
Arcadia_Starship_PositionChangeInputEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Starship_PositionChangeInputEvent* self
  )
{ 
  Arcadia_EnterConstructor(Arcadia_Starship_PositionChangeInputEvent);
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value timestamp = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &timestamp);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->translation = (Arcadia_Math_Vector3Real32*)Arcadia_Object_clone(thread, Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Math_Vector3Real32_getType(thread)));
  //
  Arcadia_LeaveConstructor(Arcadia_Starship_PositionChangeInputEvent);
}

static void
Arcadia_Starship_PositionChangeInputEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Starship_PositionChangeInputEventDispatch* self
  )
{/*Intentionally empty.*/}

Arcadia_Starship_PositionChangeInputEvent*
Arcadia_Starship_PositionChangeInputEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Math_Vector3Real32* translation
  )
{
  _Arcadia_BeginCreate(Arcadia_Starship_PositionChangeInputEvent);
  Arcadia_ValueStack_pushNatural64Value(thread, timestamp);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, translation);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  _Arcadia_EndCreate(Arcadia_Starship_PositionChangeInputEvent);   
}
