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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/SceneNodeFactory.h"

#include "Arcadia/Visuals/Implementation/Scene/CameraNode.h"
#include "Arcadia/Visuals/Implementation/Scene/MeshContext.h"
#include "Arcadia/Visuals/Implementation/Scene/MeshNode.h"
#include "Arcadia/Visuals/Implementation/Scene/ViewportNode.h"

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  );

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  );

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  );

static Arcadia_Visuals_Implementation_Scene_MeshContext*
Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Visuals_Implementation_Scene_CameraNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createCameraNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Visuals_Implementation_Scene_MeshNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Visuals_Implementation_Scene_ViewportNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createViewportNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_SceneNodeFactory_construct,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_SceneNodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_SceneNodeFactory_visit,
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

Arcadia_defineObjectType(u8"Arcardia.Visuals.Implementation.SceneNodeFactory", Arcadia_Visuals_Implementation_SceneNodeFactory,
                         u8"Arcadia.Visuals.SceneNodeFactory", Arcadia_Visuals_SceneNodeFactory,
                         &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_SceneNodeFactory_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Visuals_SceneNodeFactory*)self)->createCameraNode = (Arcadia_Visuals_Scene_CameraNode * (*)(Arcadia_Thread * thread, Arcadia_Visuals_SceneNodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_SceneNodeFactory_createCameraNodeImpl;
  ((Arcadia_Visuals_SceneNodeFactory*)self)->createMeshContext = (Arcadia_Visuals_Scene_MeshContext * (*)(Arcadia_Thread * thread, Arcadia_Visuals_SceneNodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshContextImpl;
  ((Arcadia_Visuals_SceneNodeFactory*)self)->createMeshNode = (Arcadia_Visuals_Scene_MeshNode* (*)(Arcadia_Thread * thread, Arcadia_Visuals_SceneNodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshNodeImpl;
  ((Arcadia_Visuals_SceneNodeFactory*)self)->createViewportNode = (Arcadia_Visuals_Scene_ViewportNode* (*)(Arcadia_Thread * thread, Arcadia_Visuals_SceneNodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_SceneNodeFactory_createViewportNodeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static Arcadia_Visuals_Implementation_Scene_MeshContext*
Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Visuals_Implementation_Scene_MeshContext_create(thread, backendContext); }

static Arcadia_Visuals_Implementation_Scene_CameraNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createCameraNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Visuals_Implementation_Scene_CameraNode_create(thread, backendContext); }

static Arcadia_Visuals_Implementation_Scene_MeshNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createMeshNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Visuals_Implementation_Scene_MeshNode_create(thread, backendContext); }

static Arcadia_Visuals_Implementation_Scene_ViewportNode*
Arcadia_Visuals_Implementation_SceneNodeFactory_createViewportNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_SceneNodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Visuals_Implementation_Scene_ViewportNode_create(thread, backendContext); }

Arcadia_Visuals_Implementation_SceneNodeFactory*
Arcadia_Visuals_Implementation_SceneNodeFactory_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_SceneNodeFactory);
}
