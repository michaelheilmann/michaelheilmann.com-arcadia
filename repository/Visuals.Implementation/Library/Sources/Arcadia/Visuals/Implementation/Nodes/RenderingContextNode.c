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

#include "Arcadia/Visuals/Implementation/Nodes/RenderingContextNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Nodes/FrameBufferNode.h"

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_RenderingContextNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_RenderingContextNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_RenderingContextNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.RenderingContextNode", Arcadia_Engine_Visuals_Implementation_RenderingContextNode,
                         u8"Arcadia.Engine.Visuals.RenderingContextNode", Arcadia_Engine_Visuals_RenderingContextNode,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_Implementation_RenderingContextNode_getType(thread);
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
  self->renderingContextResource = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNodeDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_RenderingContextNode*)) & Arcadia_Engine_Visuals_Implementation_RenderingContextNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_Implementation_RenderingContextNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  )
{
  if (self->backendContext) {
    if (self->renderingContextResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->renderingContextResource);
      self->renderingContextResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* renderingContextNode
  )
{
  if (self->backendContext) {
    if (!self->renderingContextResource) {
      self->renderingContextResource =
        Arcadia_Visuals_Implementation_BackendContext_createRenderingContextResource
          (
            thread,
            self->backendContext
          );
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->renderingContextResource);
    }
    // Pass the matrices to the backend.
    Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrix(thread, self->renderingContextResource, ((Arcadia_Engine_Visuals_RenderingContextNode*)self)->worldToViewMatrix);
    Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrix(thread, self->renderingContextResource, ((Arcadia_Engine_Visuals_RenderingContextNode*)self)->viewToProjectionMatrix);

    // Load the resouurce.
    Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->renderingContextResource);
    if (((Arcadia_Engine_Visuals_RenderingContextNode*)self)->frameBufferNode) {
      Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)((Arcadia_Engine_Visuals_RenderingContextNode*)self)->frameBufferNode, (Arcadia_Engine_Visuals_RenderingContextNode*)self);
      // If there is a frame buffer to render to, render to that frame buffer.
      Arcadia_Engine_Visuals_Implementation_FrameBufferNode* frameBufferNode = (Arcadia_Engine_Visuals_Implementation_FrameBufferNode*)((Arcadia_Engine_Visuals_RenderingContextNode*)self)->frameBufferNode;
      Arcadia_Visuals_Implementation_RenderingContextResource_setTargetFrameBuffer(thread, self->renderingContextResource, frameBufferNode->frameBufferResource);
    } else {
      // Otherwise render to the default frame buffer.
      Arcadia_Visuals_Implementation_RenderingContextResource_setTargetFrameBuffer(thread, self->renderingContextResource, NULL);
    }
  }
}

static void
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* self,
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
    if (self->renderingContextResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->renderingContextResource);
      self->renderingContextResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

Arcadia_Engine_Visuals_Implementation_RenderingContextNode*
Arcadia_Engine_Visuals_Implementation_RenderingContextNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_RenderingContextNode);
}
