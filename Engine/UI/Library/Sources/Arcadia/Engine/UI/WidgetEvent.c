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
#include "Arcadia/Engine/UI/WidgetEvent.h"

#include "Arcadia/Engine/UI/Include.h"

static void
Arcadia_Engine_UI_WidgetEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEvent* self
  );

static void
Arcadia_Engine_UI_WidgetEvent_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEvent* self
  );

static void
Arcadia_Engine_UI_WidgetEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEventDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_UI_WidgetEvent_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_UI_WidgetEvent_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.UI.WidgetEvent", Arcadia_Engine_UI_WidgetEvent,
                         u8"Arcadia.Engine.UI.Event", Arcadia_Engine_UI_Event,
                         &_typeOperations);

static void
Arcadia_Engine_UI_WidgetEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_UI_WidgetEvent_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
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
  self->source = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_UI_WidgetNode_getType(thread));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_UI_WidgetEvent_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEvent* self
  )
{
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
}

static void
Arcadia_Engine_UI_WidgetEvent_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetEventDispatch* self
  )
{ }
