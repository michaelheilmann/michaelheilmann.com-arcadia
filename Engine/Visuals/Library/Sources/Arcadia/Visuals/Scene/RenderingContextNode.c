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
#include "Arcadia/Visuals/Scene/RenderingContextNode.h"

static void
Arcadia_Visuals_Scene_RenderingContextNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  );

static void
Arcadia_Visuals_Scene_RenderingContextNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_RenderingContextNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  );

static void
Arcadia_Visuals_Scene_RenderingContextNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_RenderingContextNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_RenderingContextNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_RenderingContextNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.RenderingContextNode", Arcadia_Visuals_Scene_RenderingContextNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_RenderingContextNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_RenderingContextNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->cameraNode = NULL;
  self->frameBufferNode = NULL;

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  self->viewportClearColor.red = 193;
  self->viewportClearColor.green = 216;
  self->viewportClearColor.blue = 195;
  self->viewportClearColor.alpha = 255;

  self->viewportClearDepth = 1.f;

  self->relativeViewportRectangle.left = 0.f;
  self->relativeViewportRectangle.bottom = 0.f;
  self->relativeViewportRectangle.right = 1.f;
  self->relativeViewportRectangle.top = 1.f;

  self->canvasSize.width = 320.f;
  self->canvasSize.height = 240.f;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_RenderingContextNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_Scene_RenderingContextNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_RenderingContextNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  )
{
  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }

  if (self->frameBufferNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->frameBufferNode);
  }

  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
}

void
Arcadia_Visuals_Scene_RenderingContextNode_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{
  Arcadia_Math_Matrix4Real32_assign(thread, self->viewToProjectionMatrix, viewToProjectionMatrix);
}

void
Arcadia_Visuals_Scene_RenderingContextNode_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{
  Arcadia_Math_Matrix4Real32_assign(thread, self->worldToViewMatrix, worldToViewMatrix);
}

void
Arcadia_Visuals_Scene_RenderingContextNode_setFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Visuals_Scene_FrameBufferNode* frameBufferNode
  )
{ self->frameBufferNode = frameBufferNode; }

Arcadia_Visuals_Scene_FrameBufferNode*
Arcadia_Visuals_Scene_RenderingContextNode_getFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  )
{ return self->frameBufferNode; }

void
Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Visuals_Scene_CameraNode* cameraNode
  )
{ self->cameraNode = cameraNode; }

Arcadia_Visuals_Scene_CameraNode*
Arcadia_Visuals_Scene_RenderingContextNode_getCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  )
{ return self->cameraNode; }
