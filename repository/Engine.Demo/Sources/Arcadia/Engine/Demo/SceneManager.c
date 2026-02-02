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

#include "Arcadia/Engine/Demo/SceneManager.h"

static void
Arcadia_Engine_Demo_SceneManager_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  );

static void
Arcadia_Engine_Demo_SceneManager_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManagerDispatch* self
  );

static void
Arcadia_Engine_Demo_SceneManager_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  );

static void
Arcadia_Engine_Demo_SceneManager_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_SceneManager_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Demo_SceneManager_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_SceneManager_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.SceneManager", Arcadia_Engine_Demo_SceneManager,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Engine_Demo_SceneManager_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_SceneManager_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->engine = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_getType(thread));
  self->scene = NULL;
  self->sceneChangedEvent = Arcadia_Signal_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Demo_SceneManager_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManagerDispatch* self
  )
{ }

static void
Arcadia_Engine_Demo_SceneManager_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  )
{ }

static void
Arcadia_Engine_Demo_SceneManager_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  )
{
  if (self->sceneChangedEvent) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->sceneChangedEvent);
  }
  if (self->engine) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->engine);
  }
  if (self->scene) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scene);
  }
}

Arcadia_Engine_Demo_Scene*
Arcadia_Engine_Demo_SceneManager_getScene
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  )
{ return self->scene; }

void
Arcadia_Engine_Demo_SceneManager_setScene
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self,
    Arcadia_Engine_Demo_Scene* scene
  )
{
  if (self->scene != scene) {
    Arcadia_Object* oldValue = (Arcadia_Object*)self->scene;
    Arcadia_Object* newValue = (Arcadia_Object*)scene;
    self->scene = scene;
    if (oldValue) Arcadia_ValueStack_pushObjectReferenceValue(thread, oldValue); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
    if (newValue) Arcadia_ValueStack_pushObjectReferenceValue(thread, newValue); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_Signal_emit(thread, self->sceneChangedEvent, (Arcadia_Object*)self);
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_ValueStack_popValues(thread, 2 + 1);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_ValueStack_popValues(thread, 2 + 1);
      Arcadia_Thread_jump(thread);
    }
  }
}

Arcadia_Engine_Demo_SceneManager*
Arcadia_Engine_Demo_SceneManager_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (engine) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)engine);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_SceneManager);
}
