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

#include "Arcadia/Engine/Demo/Scene.h"

#include "Arcadia/Engine/Demo/SceneManager.h"

static void
Arcadia_Engine_Demo_Scene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  );

static void
Arcadia_Engine_Demo_Scene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneDispatch* self
  );

static void
Arcadia_Engine_Demo_Scene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_Scene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_Scene_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_Scene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_Scene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_Scene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Demo_Scene_typeOperations);

static void
Arcadia_Engine_Demo_Scene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_Scene_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->engine = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_getType(thread));
  self->sceneManager = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Engine_Demo_SceneManager_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Engine_Demo_Scene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneDispatch* self
  )
{ }

static void
Arcadia_Engine_Demo_Scene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  )
{
  if (self->engine) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->engine);
  }
  if (self->sceneManager) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->sceneManager);
  }
}

void
Arcadia_Engine_Demo_Scene_updateAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Demo_Scene, updateAudials, self, tick, width, height); }

void
Arcadia_Engine_Demo_Scene_updateLogics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self,
    Arcadia_Real64Value tick
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Demo_Scene, updateLogics, self, tick); }

void
Arcadia_Engine_Demo_Scene_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Demo_Scene, updateVisuals, self, tick, width, height); }
