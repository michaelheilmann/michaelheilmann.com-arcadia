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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Input/MouseButtonEvent.h"

static void
Arcadia_Engine_Input_MouseButtonEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_MouseButtonEvent* self
  );

static void
Arcadia_Engine_Input_MouseButtonEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_MouseButtonEventDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Input_MouseButtonEvent_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Input_MouseButtonEvent_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Input.MouseButtonEvent", Arcadia_Engine_Input_MouseButtonEvent,
                         u8"Arcadia.Engine.Event", Arcadia_Engine_Event,
                         &_typeOperations);

static void
Arcadia_Engine_Input_MouseButtonEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_MouseButtonEvent* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Input_MouseButtonEvent);
  if (5 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural64Value(thread, Arcadia_ValueStack_getNatural64Value(thread, 5));
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->action = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->button = Arcadia_ValueStack_getNatural64Value(thread, 3);
  self->x = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->y = Arcadia_ValueStack_getInteger32Value(thread, 1);
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Input_MouseButtonEvent);
}

static void
Arcadia_Engine_Input_MouseButtonEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_MouseButtonEventDispatch* self
  )
{/*Intentionally empty.*/}

Arcadia_Engine_Input_MouseButtonEvent*
Arcadia_Engine_Input_MouseButtonEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Engine_Input_MouseButtonAction action,
    Arcadia_Natural64Value button,
    Arcadia_Integer32Value x,
    Arcadia_Integer32Value y
  )
{
  _Arcadia_BeginCreate(Arcadia_Engine_Input_MouseButtonEvent);
  Arcadia_ValueStack_pushNatural64Value(thread, timestamp);
  Arcadia_ValueStack_pushInteger32Value(thread, action);
  Arcadia_ValueStack_pushNatural64Value(thread, button);
  Arcadia_ValueStack_pushInteger32Value(thread, x);
  Arcadia_ValueStack_pushInteger32Value(thread, y);
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  _Arcadia_EndCreate(Arcadia_Engine_Input_MouseButtonEvent);
}
