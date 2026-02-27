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

#define ARCADIA_ENGINE_UI_PRIVATE (1)
#include "Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.h"

#include "Arcadia/Engine/UI/Include.h"

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEvent* self
  );

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEventDispatch* self
  );

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEvent* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_UI_WidgetSizeChangedEvent_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_UI_WidgetSizeChangedEvent_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.UI.WidgetSizeChangedEvent", Arcadia_Engine_UI_WidgetSizeChangedEvent,
                         u8"Arcadia.Engine.UI.WidgetEvent", Arcadia_Engine_UI_WidgetEvent,
                         &_typeOperations);

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_UI_WidgetSizeChangedEvent_getType(thread);
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (4 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value timestamp = Arcadia_ValueStack_getValue(thread, 4);
    Arcadia_Value source = Arcadia_ValueStack_getValue(thread, 3);
    Arcadia_ValueStack_pushValue(thread, &timestamp);
    Arcadia_ValueStack_pushValue(thread, &source);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->horizontalSize = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->verticalSize = Arcadia_ValueStack_getInteger32Value(thread, 1);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEventDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_UI_WidgetSizeChangedEvent_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetSizeChangedEvent* self
  )
{/*Intentionally empty.*/}

Arcadia_Engine_UI_WidgetSizeChangedEvent*
Arcadia_Engine_UI_WidgetSizeChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Engine_UI_WidgetNode* source,
    Arcadia_Integer32Value horizontalSize,
    Arcadia_Integer32Value verticalSize
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural64Value(thread, timestamp);
  if (source) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, source);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushInteger32Value(thread, horizontalSize);
  Arcadia_ValueStack_pushInteger32Value(thread, verticalSize);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_UI_WidgetSizeChangedEvent);
}
