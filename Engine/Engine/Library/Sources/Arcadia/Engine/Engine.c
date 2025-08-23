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

#include "Arcadia/Engine/Engine.h"

static Arcadia_Engine* g_instance = NULL;

static void
Arcadia_Engine_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Engine_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
  );

static void
Arcadia_Engine_destroyCallback
  (
    void* argument1,
    void* argument2
  );

static Arcadia_Engine*
Arcadia_Engine_create
  (
    Arcadia_Thread* thread
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Engine_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Engine_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine", Arcadia_Engine,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Engine_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Engine* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Engine_getType(thread);
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

  _self->visualBackendTypes = (Arcadia_Set*)Arcadia_HashSet_create(thread);
  _self->visualsSystem = NULL;
  
  _self->audialsBackendTypes = (Arcadia_Set*)Arcadia_HashSet_create(thread);
  _self->audialsSystem = NULL;
  
  _self->events = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);

  _self->update = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Engine_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
  )
{
  if (self->visualBackendTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->visualBackendTypes);
  }
  if (self->visualsSystem) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->visualsSystem);  
  }
  if (self->audialsBackendTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->audialsBackendTypes);
  }
  if (self->audialsSystem) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->audialsSystem);  
  }
  if (self->events) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->events);
  }
}

static void
Arcadia_Engine_destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

static Arcadia_Engine*
Arcadia_Engine_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Engine* self = Arcadia_allocateObject(thread, _Arcadia_Engine_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Engine_enqueEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self,
    Arcadia_Engine_Event* event
  )
{ 
  Arcadia_Deque_insertBack(thread, self->events, Arcadia_Value_makeObjectReferenceValue(event));
}

Arcadia_Engine_Event*
Arcadia_Engine_dequeEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
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

void
Arcadia_Engine_update
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
  )
{ self->update(thread, self); }

Arcadia_Engine*
Arcadia_Engine_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Engine* instance = Arcadia_Engine_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &Arcadia_Engine_destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}