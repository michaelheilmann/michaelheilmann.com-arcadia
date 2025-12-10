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

#include "Arcadia/Visuals/Implementation/Scene/ViewportNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Scene/RenderingContextNode.h"
#include <assert.h>

#define ClearColorDirty (1)
#define ClearDepthDirty (2)
#define RelativeRectangleDirty (4)
#define CanvasSizeDirty (8)

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNodeDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value depth
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ViewportNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ViewportNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ViewportNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.ViewportNode", Arcadia_Visuals_Implementation_Scene_ViewportNode,
                         u8"Arcadia.Visuals.Scene.ViewportNode", Arcadia_Visuals_Scene_ViewportNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_ViewportNode_getType(thread);
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

  self->dirtyBits = ClearColorDirty | ClearDepthDirty | RelativeRectangleDirty | CanvasSizeDirty;

  self->viewportResource = NULL;

  self->clearColor.red = 193;
  self->clearColor.green = 216;
  self->clearColor.blue = 195;
  self->clearColor.alpha = 255;

  self->clearDepth = 1.f;

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
Arcadia_Visuals_Implementation_Scene_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNodeDispatch* self
  )
{
  ((Arcadia_Visuals_Scene_ViewportNodeDispatch*)self)->setCanvasSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_ViewportNode*, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_setCanvasSizeImpl;
  ((Arcadia_Visuals_Scene_ViewportNodeDispatch*)self)->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_ViewportNode*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearColorImpl;
  ((Arcadia_Visuals_Scene_ViewportNodeDispatch*)self)->setClearDepth = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_ViewportNode*, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearDepthImpl;
  ((Arcadia_Visuals_Scene_ViewportNodeDispatch*)self)->setRelativeViewportRectangle = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_ViewportNode*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_setRelativeViewportRectangleImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_Scene_RenderingContextNode*)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_renderImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_ViewportNode_setBackendContextImpl;
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  )
{
  if (self->backendContext) {
    if (self->viewportResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource);
      self->viewportResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
    self->dirtyBits = ClearColorDirty | ClearDepthDirty | RelativeRectangleDirty | CanvasSizeDirty;
  }
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self
  )
{
#if 0
  if (self->backendContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backendContext);
  }
#endif
#if 0
  if (self->viewportResource) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportResource);
  }
#endif
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  )
{
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)self, (Arcadia_Visuals_BackendContext*)renderingContextNode->backendContext);
  if (self->backendContext) {
    if (!self->viewportResource) {
      self->viewportResource =
        Arcadia_Visuals_Implementation_BackendContext_createViewportResource
          (
            thread,
            self->backendContext
          );
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource);
    }
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource,
                                                           renderingContextNode->renderingContextResource);
    if (self->dirtyBits & ClearColorDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearColor(thread, self->viewportResource,
                                                                            self->clearColor.red,
                                                                            self->clearColor.green,
                                                                            self->clearColor.blue,
                                                                            self->clearColor.alpha);
      self->dirtyBits &= ~ClearColorDirty;
    }
    if (self->dirtyBits & ClearDepthDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearDepth(thread, self->viewportResource,
                                                                            self->clearDepth);
      self->dirtyBits &= ~ClearDepthDirty;
    }
    if (self->dirtyBits & RelativeRectangleDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setRelativeViewportRectangle(thread, self->viewportResource,
                                                                                           self->relativeViewportRectangle.left,
                                                                                           self->relativeViewportRectangle.bottom,
                                                                                           self->relativeViewportRectangle.right,
                                                                                           self->relativeViewportRectangle.top);
      self->dirtyBits &= ~RelativeRectangleDirty;
    }
    if (self->dirtyBits & CanvasSizeDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setCanvasSize(thread, self->viewportResource,
                                                                            self->canvasSize.width,
                                                                            self->canvasSize.height);
      self->dirtyBits &= ~CanvasSizeDirty;
    }
  }
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
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
    if (self->viewportResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource);
      self->viewportResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  )
{
  self->clearColor.red = red;
  self->clearColor.green = green;
  self->clearColor.blue = blue;
  self->clearColor.alpha = alpha;
  self->dirtyBits |= ClearColorDirty;
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value depth
  )
{
  self->clearDepth = depth;
  self->dirtyBits |= ClearDepthDirty;
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{
  self->relativeViewportRectangle.left = left;
  self->relativeViewportRectangle.bottom = bottom;
  self->relativeViewportRectangle.right = right;
  self->relativeViewportRectangle.top = top;
  self->dirtyBits |= RelativeRectangleDirty;
}

static void
Arcadia_Visuals_Implementation_Scene_ViewportNode_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{
  self->canvasSize.width = width;
  self->canvasSize.height = height;
  self->dirtyBits |= CanvasSizeDirty;
}

Arcadia_Visuals_Implementation_Scene_ViewportNode*
Arcadia_Visuals_Implementation_Scene_ViewportNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_ViewportNode);
}
