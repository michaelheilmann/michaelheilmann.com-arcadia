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

#include "Arcadia/Visuals/Implementation/Scene/CameraNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Scene/RenderingContextNode.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNodeDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_CameraNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_CameraNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_CameraNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.CameraNode", Arcadia_Visuals_Implementation_Scene_CameraNode,
                         u8"Arcadia.Visuals.Scene.CameraNode", Arcadia_Visuals_Scene_CameraNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_CameraNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  // Set a perspective projection matrix.
  Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection(thread, self->viewToProjectionMatrix, 60.f, 4.f / 3.f, 0.1f, +100.f);
  // Move the camera along the positive right axis and along the positive z axis by multiplying the camera position by `translate(0, 0, 1)`.
  // However, as we actually do not transform the camera position but the position of the objects in world space,
  // we actually have to use the inverse `inverse(translate(0, 0, 1))`.
  //Arcadia_Math_Matrix4Real32* worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_MatrixReal32Value_setTranslation(thread, self->worldToViewMatrix, 0.f, 0.f, -1.f);

  self->constantBufferResource = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNodeDispatch* self
  )
{
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_Scene_RenderingContextNode*)) & Arcadia_Visuals_Implementation_Scene_CameraNode_renderImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_CameraNode_setBackendContextImpl;
}

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  )
{
  if (self->backendContext) {
    if (self->constantBufferResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBufferResource);
      self->constantBufferResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self
  )
{
  /* The backend context and resources are locked. No need to visit them. */
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  )
{
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)self, (Arcadia_Visuals_BackendContext*)renderingContextNode->backendContext);
  if (self->backendContext) {
    if (!self->constantBufferResource) {
      Arcadia_Visuals_Implementation_BackendContext* backendContext = self->backendContext;
      self->constantBufferResource = Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, backendContext);
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBufferResource);
    }
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, self->constantBufferResource);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, self->constantBufferResource, Arcadia_BooleanValue_True,
                                                                                       self->viewToProjectionMatrix);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, self->constantBufferResource, Arcadia_BooleanValue_True,
                                                                                       self->worldToViewMatrix);

    // Render the viewport.
    Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)((Arcadia_Visuals_Scene_CameraNode*)self)->viewport,
                                              (Arcadia_Visuals_Scene_RenderingContextNode*)renderingContextNode);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_CameraNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_CameraNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  if (backendContext == self->backendContext) {
    // Only change something if the backend context changes.
    return;
  }
  if (backendContext) {
    Arcadia_Object_lock(thread, (Arcadia_Object*)backendContext);
  }
  if (self->backendContext) {
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
  }
  if (self->backendContext) {
    if (self->constantBufferResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBufferResource);
      self->constantBufferResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

Arcadia_Visuals_Implementation_Scene_CameraNode*
Arcadia_Visuals_Implementation_Scene_CameraNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_CameraNode);
}
