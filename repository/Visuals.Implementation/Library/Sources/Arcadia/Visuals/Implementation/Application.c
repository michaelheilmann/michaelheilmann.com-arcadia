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

#include "Arcadia/Visuals/Implementation/Application.h"

static void
Arcadia_Visuals_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Application_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Application_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Application_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Application", Arcadia_Visuals_Application,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Application* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Application_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->createIcon = NULL;
  _self->createWindow = NULL;
  _self->getDisplayDevices = NULL;
  _self->getQuitRequested = NULL;
  _self->setQuitRequested = NULL;
  _self->update = NULL;
  _self->events = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Visuals_Application_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{
  if (self->events) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->events);
  }
}

Arcadia_Visuals_Icon*
Arcadia_Visuals_Application_createIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{ return self->createIcon(thread, self, width, height, red, green, blue, alpha); }

Arcadia_Visuals_Window*
Arcadia_Visuals_Application_createWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{ return self->createWindow(thread, self); }

Arcadia_List*
Arcadia_Visuals_Application_getDisplayDevices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{ return self->getDisplayDevices(thread, self); }

void
Arcadia_Visuals_Application_enqueEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self,
    Arcadia_Engine_Event* event
  )
{ 
  Arcadia_Deque_insertBack(thread, self->events, Arcadia_Value_makeObjectReferenceValue(event));
}

Arcadia_Engine_Event*
Arcadia_Visuals_Application_dequeEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{
  if (Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)self->events)) {
    return NULL;
  }
  Arcadia_Value eventValue = Arcadia_Deque_getFront(thread, self->events);
  Arcadia_Deque_removeFront(thread, self->events);
  Arcadia_Engine_Event* event = (Arcadia_Engine_Event*)Arcadia_Value_getObjectReferenceValue(&eventValue);
  return event;
}

Arcadia_BooleanValue
Arcadia_Visuals_Application_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{ return self->getQuitRequested(thread, self); }

void
Arcadia_Visuals_Application_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->setQuitRequested(thread, self, quitRequested); }

void
Arcadia_Visuals_Application_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  )
{ self->update(thread, self); }
