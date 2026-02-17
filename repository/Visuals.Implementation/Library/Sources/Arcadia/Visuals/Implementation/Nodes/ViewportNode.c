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

#include "Arcadia/Visuals/Implementation/Nodes/ViewportNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Nodes/EnterPassNode.h"
#include <assert.h>

#define ClearColorDirty (1)
#define ClearColorBufferDirty (2)

#define ClearDepthDirty (4)
#define ClearDepthBufferDirty (8)

#define RelativeRectangleDirty (16)
#define CanvasSizeDirty (32)

#define DirtyBitsAll (ClearColorDirty | ClearColorBufferDirty | ClearDepthDirty | ClearDepthBufferDirty | RelativeRectangleDirty | CanvasSizeDirty)

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_BooleanValue
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_BooleanValue clearColorBuffer
  );

static Arcadia_Math_Color4Real32*
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_BooleanValue clearDepthBuffer
  );

static Arcadia_BooleanValue
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static Arcadia_Real32Value
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value depth
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_getRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value* width,
    Arcadia_Real32Value* height
  );

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ViewportNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ViewportNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ViewportNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.ViewportNode", Arcadia_Engine_Visuals_Implementation_ViewportNode,
                         u8"Arcadia.Engine.Visuals.ViewportNode", Arcadia_Engine_Visuals_ViewportNode,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_Implementation_ViewportNode_getType(thread);
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

  self->dirtyBits = DirtyBitsAll;

  self->clearColorBuffer = Arcadia_BooleanValue_True;
  self->clearColor = Arcadia_Math_Color4Real32_create4(thread, 193.f / 255.f, 216.f / 255.f, 195.f / 255.f, 1.f);

  self->clearDepthBuffer = Arcadia_BooleanValue_True;
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
Arcadia_Engine_Visuals_Implementation_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNodeDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getCanvasSize = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Real32Value*, Arcadia_Real32Value*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getCanvasSizeImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setCanvasSize = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setCanvasSizeImpl;
  
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getClearColorBuffer = (Arcadia_BooleanValue (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorBufferImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setClearColorBuffer = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_BooleanValue)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorBufferImpl;

  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getClearColor = (Arcadia_Math_Color4Real32* (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Math_Color4Real32*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorImpl;

  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getClearDepthBuffer = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthBufferImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setClearDepthBuffer = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_BooleanValue)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthBufferImpl;

  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getClearDepth = (Arcadia_Real32Value(*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setClearDepth = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Real32Value)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthImpl;
  
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->getRelativeViewportRectangle = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_getRelativeViewportRectangleImpl;
  ((Arcadia_Engine_Visuals_ViewportNodeDispatch*)self)->setRelativeViewportRectangle = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_ViewportNode*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setRelativeViewportRectangleImpl;
  
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_EnterPassNode*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_Implementation_ViewportNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{
  if (self->backendContext) {
#if 0
    if (self->viewportResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource);
      self->viewportResource = NULL;
    }
#endif
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
    self->dirtyBits = ClearColorDirty | ClearDepthDirty | RelativeRectangleDirty | CanvasSizeDirty;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{
  if (self->clearColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->clearColor);
  }
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  )
{
  Arcadia_Engine_Node_setVisualsBackendContext(thread, (Arcadia_Engine_Node*)self, (Arcadia_Engine_Visuals_BackendContext*)renderingContextNode->backendContext);
  if (self->backendContext) {
#if 0
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
                                                           renderingContextNode->enterPassResource);
    if (self->dirtyBits & ClearColorDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearColor(thread, self->viewportResource,
                                                                            self->clearColor);
      self->dirtyBits &= ~ClearColorDirty;
    }
    if (self->dirtyBits & ClearColorBufferDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearColorBuffer(thread, self->viewportResource, self->clearColorBuffer);
      self->dirtyBits &= ~ClearColorBufferDirty;
    }
    if (self->dirtyBits & ClearDepthDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearDepth(thread, self->viewportResource,
                                                                            self->clearDepth);
      self->dirtyBits &= ~ClearDepthDirty;
    }
    if (self->dirtyBits & ClearDepthBufferDirty) {
      Arcadia_Visuals_Implementation_ViewportResource_setClearDepthBuffer(thread, self->viewportResource, self->clearDepthBuffer);
      self->dirtyBits &= ~ClearDepthBufferDirty;
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
#endif
  }
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
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
#if 0
    if (self->viewportResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewportResource);
      self->viewportResource = NULL;
    }
#endif
  }
  self->backendContext = backendContext;
}

static Arcadia_BooleanValue
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{ return self->clearColorBuffer; }

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_BooleanValue clearColorBuffer
  )
{ 
  self->clearColorBuffer = clearColorBuffer;
  self->dirtyBits |= ClearColorBufferDirty;
}

static Arcadia_Math_Color4Real32*
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  )
{
  Arcadia_Math_Color4Real32* clone = Arcadia_Math_Color4Real32_create(thread);
  Arcadia_Math_Color4Real32_assign(thread, clone, self->clearColor);
  return clone;
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  )
{
  Arcadia_Math_Color4Real32_assign(thread, self->clearColor, clearColor);
  self->dirtyBits |= ClearColorDirty;
}

static Arcadia_BooleanValue
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{ return self->clearDepthBuffer; }

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_BooleanValue clearDepthBuffer
  )
{
  self->clearDepthBuffer = clearDepthBuffer;
  self->dirtyBits |= ClearDepthBufferDirty;
}

static Arcadia_Real32Value
Arcadia_Engine_Visuals_Implementation_ViewportNode_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self
  )
{ return self->clearDepth; }

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value depth
  )
{
  self->clearDepth = depth;
  self->dirtyBits |= ClearDepthDirty;
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_getRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  )
{
  *left = self->relativeViewportRectangle.left;
  *bottom = self->relativeViewportRectangle.bottom;
  *right = self->relativeViewportRectangle.right;
  *top = self->relativeViewportRectangle.top;
}


static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
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
Arcadia_Engine_Visuals_Implementation_ViewportNode_getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value* width,
    Arcadia_Real32Value* height
  )
{
  *width = self->canvasSize.width;
  *height = self->canvasSize.height;
}

static void
Arcadia_Engine_Visuals_Implementation_ViewportNode_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{
  self->canvasSize.width = width;
  self->canvasSize.height = height;
  self->dirtyBits |= CanvasSizeDirty;
}

Arcadia_Engine_Visuals_Implementation_ViewportNode*
Arcadia_Engine_Visuals_Implementation_ViewportNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_ViewportNode);
}
