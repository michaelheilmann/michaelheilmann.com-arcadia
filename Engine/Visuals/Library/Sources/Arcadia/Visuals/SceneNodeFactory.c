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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/SceneNodeFactory.h"

static void
Arcadia_Visuals_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  );

static void
Arcadia_Visuals_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  );

static void
Arcadia_Visuals_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_SceneNodeFactory_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Visuals_SceneNodeFactory_construct,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_SceneNodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_SceneNodeFactory_visit,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_SceneNodeFactory_typeOperations = {
  .objectTypeOperations = &_Arcadia_Visuals_SceneNodeFactory_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcardia.Visuals.SceneNodeFactory", Arcadia_Visuals_SceneNodeFactory,
                         u8"Arcadia.Engine.SceneNodeFactory", Arcadia_Engine_SceneNodeFactory,
                         &_Arcadia_Visuals_SceneNodeFactory_typeOperations);

static void
Arcadia_Visuals_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_SceneNodeFactory_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->createCameraNode = NULL;
  self->createMeshContext = NULL;
  self->createMeshNode = NULL;
  self->createViewportNode = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

Arcadia_Visuals_Scene_CameraNode*
Arcadia_Visuals_SceneNodeFactory_createCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ return self->createCameraNode(thread, self, backendContext); }

Arcadia_Visuals_Scene_MeshContext*
Arcadia_Visuals_SceneNodeFactory_createMeshContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ return self->createMeshContext(thread, self, backendContext); }

Arcadia_Visuals_Scene_MeshNode*
Arcadia_Visuals_SceneNodeFactory_createMeshNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ return self->createMeshNode(thread, self, backendContext); }

Arcadia_Visuals_Scene_ViewportNode*
Arcadia_Visuals_SceneNodeFactory_createViewportNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ return self->createViewportNode(thread, self, backendContext); }
