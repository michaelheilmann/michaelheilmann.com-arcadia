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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Scene/CameraNode.h"

static void
Arcadia_Visuals_Scene_CameraNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self
  );

static void
Arcadia_Visuals_Scene_CameraNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_CameraNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_CameraNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_CameraNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.CameraNode", Arcadia_Visuals_Scene_CameraNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_CameraNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_CameraNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->viewport = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_CameraNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_Scene_CameraNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Visuals_Scene_CameraNode_setViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Visuals_Scene_ViewportNode* viewport
  )
{ self->viewport = viewport; }

void
Arcadia_Visuals_Scene_CameraNode_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_CameraNode, setViewToProjectionMatrix, self, viewToProjectionMatrix); }

void
Arcadia_Visuals_Scene_CameraNode_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_CameraNode, setWorldToViewMatrix, self, worldToViewMatrix); }
