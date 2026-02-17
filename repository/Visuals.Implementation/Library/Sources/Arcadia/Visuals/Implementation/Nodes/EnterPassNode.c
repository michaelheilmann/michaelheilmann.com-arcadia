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

#include "Arcadia/Visuals/Implementation/Nodes/EnterPassNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Nodes/FrameBufferNode.h"

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  );

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_EnterPassNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_EnterPassNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_EnterPassNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.EnterPassNode", Arcadia_Engine_Visuals_Implementation_EnterPassNode,
                         u8"Arcadia.Engine.Visuals.RenderingContextNode", Arcadia_Engine_Visuals_EnterPassNode,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_Implementation_EnterPassNode_getType(thread);
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
  self->enterPassResource = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNodeDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_EnterPassNode*)) & Arcadia_Engine_Visuals_Implementation_EnterPassNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_Implementation_EnterPassNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  )
{
  if (self->backendContext) {
    if (self->enterPassResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->enterPassResource);
      self->enterPassResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  )
{
  if (self->backendContext) {
    if (!self->enterPassResource) {
      self->enterPassResource =
        Arcadia_Visuals_Implementation_BackendContext_createEnterPassResource
          (
            thread,
            self->backendContext
          );
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->enterPassResource);
    }
    // Get the camera.
    Arcadia_Engine_Visuals_CameraNode* cameraNode = ((Arcadia_Engine_Visuals_EnterPassNode*)self)->cameraNode;
    // Pass the camera's data to the resource.
    Arcadia_Visuals_Implementation_EnterPassResource_setWorldToViewMatrix(thread, self->enterPassResource, Arcadia_Engine_Visuals_CameraNode_getWorldToViewMatrix(thread, cameraNode));
    Arcadia_Visuals_Implementation_EnterPassResource_setViewToProjectionMatrix(thread, self->enterPassResource, Arcadia_Engine_Visuals_CameraNode_getViewToProjectionMatrix(thread, cameraNode));
    // Get the viewport.
    Arcadia_Engine_Visuals_ViewportNode* viewportNode = ((Arcadia_Engine_Visuals_EnterPassNode*)self)->viewportNode;
    // Pass the viewport's data to the resource.
    Arcadia_Visuals_Implementation_EnterPassResource_setClearColor(thread, self->enterPassResource, Arcadia_Engine_Visuals_ViewportNode_getClearColor(thread, viewportNode));
    Arcadia_Visuals_Implementation_EnterPassResource_setClearColorBuffer(thread, self->enterPassResource, Arcadia_Engine_Visuals_ViewportNode_getClearColorBuffer(thread, viewportNode));
    Arcadia_Visuals_Implementation_EnterPassResource_setClearDepth(thread, self->enterPassResource, Arcadia_Engine_Visuals_ViewportNode_getClearDepth(thread, viewportNode));
    Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthBuffer(thread, self->enterPassResource, Arcadia_Engine_Visuals_ViewportNode_getClearDepthBuffer(thread, viewportNode));
    Arcadia_Real32Value left, bottom, right, top;
    Arcadia_Engine_Visuals_ViewportNode_getRelativeViewportRectangle(thread, viewportNode, &left, &bottom, &right, &top);
    Arcadia_Visuals_Implementation_EnterPassResource_setRelativeViewportRectangle(thread, self->enterPassResource, left, bottom, right, top);
    Arcadia_Real32Value width, height;
    Arcadia_Engine_Visuals_ViewportNode_getCanvasSize(thread, viewportNode, &width, &height);
    Arcadia_Visuals_Implementation_EnterPassResource_setCanvasSize(thread, self->enterPassResource, width, height);

    if (((Arcadia_Engine_Visuals_EnterPassNode*)self)->frameBufferNode) {
      Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)((Arcadia_Engine_Visuals_EnterPassNode*)self)->frameBufferNode, (Arcadia_Engine_Visuals_EnterPassNode*)self);
      // If there is a frame buffer to render to, render to that frame buffer.
      Arcadia_Engine_Visuals_Implementation_FrameBufferNode* frameBufferNode = (Arcadia_Engine_Visuals_Implementation_FrameBufferNode*)((Arcadia_Engine_Visuals_EnterPassNode*)self)->frameBufferNode;
      Arcadia_Visuals_Implementation_EnterPassResource_setTargetFrameBuffer(thread, self->enterPassResource, frameBufferNode->frameBufferResource);
    } else {
      // Otherwise render to the default frame buffer.
      Arcadia_Visuals_Implementation_EnterPassResource_setTargetFrameBuffer(thread, self->enterPassResource, NULL);
    }
    // Load the resouurce.
    Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->enterPassResource);
    // Render the resource.
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->enterPassResource,
                                                           renderingContextNode->enterPassResource);

    Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)viewportNode, (Arcadia_Engine_Visuals_EnterPassNode*)renderingContextNode);
  }
}

static void
Arcadia_Engine_Visuals_Implementation_EnterPassNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* self,
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
    if (self->enterPassResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->enterPassResource);
      self->enterPassResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

Arcadia_Engine_Visuals_Implementation_EnterPassNode*
Arcadia_Engine_Visuals_Implementation_EnterPassNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_EnterPassNode);
}
