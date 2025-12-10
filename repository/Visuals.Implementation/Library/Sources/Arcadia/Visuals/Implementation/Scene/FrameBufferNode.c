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

#include "Arcadia/Visuals/Implementation/Scene/FrameBufferNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Resource.h"
#include "Arcadia/Visuals/Implementation/Resources/FrameBufferResource.h"
#include "Arcadia/Visuals/Implementation/Scene/RenderingContextNode.h"

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNodeDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_FrameBufferNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_FrameBufferNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_FrameBufferNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.FrameBufferNode", Arcadia_Visuals_Implementation_Scene_FrameBufferNode,
                         u8"Arcadia.Visuals.Scene.FrameBufferNode", Arcadia_Visuals_Scene_FrameBufferNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_FrameBufferNode_getType(thread);
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
  self->width = 320;
  self->height = 240;
  self->frameBufferResource = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNodeDispatch* self  
  )
{
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_Scene_RenderingContextNode*)) & Arcadia_Visuals_Implementation_Scene_FrameBufferNode_renderImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setBackendContextImpl;
  ((Arcadia_Visuals_Scene_FrameBufferNodeDispatch*)self)->setSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_FrameBufferNode*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setSizeImpl;
  ((Arcadia_Visuals_Scene_FrameBufferNodeDispatch*)self)->getSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_FrameBufferNode*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & Arcadia_Visuals_Implementation_Scene_FrameBufferNode_getSizeImpl;
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  )
{
  if (self->backendContext) {
    if (self->frameBufferResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->frameBufferResource);
      self->frameBufferResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self
  )
{/* The backend context and resources are locked. No need to visit them. */}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  )
{
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)self, (Arcadia_Visuals_BackendContext*)renderingContextNode->backendContext);
  if (self->backendContext) {
    if (!self->frameBufferResource) {
      Arcadia_Visuals_Implementation_BackendContext* backendContext = self->backendContext;
      self->frameBufferResource =
        Arcadia_Visuals_Implementation_BackendContext_createFrameBufferResource
          (
            thread,
            backendContext
          );
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->frameBufferResource);
    }
    Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->frameBufferResource);
    Arcadia_Visuals_Implementation_FrameBufferResource_setSize(thread, self->frameBufferResource, self->width, self->height);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
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
    if (self->frameBufferResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->frameBufferResource);
      self->frameBufferResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  self->width = width;
  self->height = height;
}

static void
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = self->width;
  *height = self->height;
}

Arcadia_Visuals_Implementation_Scene_FrameBufferNode*
Arcadia_Visuals_Implementation_Scene_FrameBufferNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_FrameBufferNode);
}
