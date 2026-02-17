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

#include "Arcadia/Visuals/Implementation/Resources/EnterPassResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_EnterPassResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearColorBuffer
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Color4Real32* clearColor
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearDepthBuffer
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value clearDepth
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

static void
Arcadia_Visuals_Implementation_EnterPassResource_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_EnterPassResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_EnterPassResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_EnterPassResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.EnterPassResource", Arcadia_Visuals_Implementation_EnterPassResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_EnterPassResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_EnterPassResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->viewerConstantBuffer = NULL;

  self->dirty = Arcadia_Visuals_Implementation_EnterPassResource_AllDirty;

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  self->canvasSize.width = 320.f;
  self->canvasSize.height = 240.f;

  self->relativeViewportRectangle.left = 0.f;
  self->relativeViewportRectangle.bottom = 0.f;
  self->relativeViewportRectangle.right = 1.f;
  self->relativeViewportRectangle.top = 1.f;

  self->clearColorBuffer = Arcadia_BooleanValue_True;
  self->clearColor = Arcadia_Math_Color4Real32_create4(thread, 193.f / 255.f, 216.f / 255.f, 195.f / 255.f, 1.f);

  self->clearDepthBuffer = Arcadia_BooleanValue_True;
  self->clearDepth = 1.f;

  Arcadia_Visuals_Implementation_BackendContext* backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
  self->viewerConstantBuffer = (Arcadia_Visuals_Implementation_ConstantBufferResource*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);

  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResourceDispatch* self
  )
{
  self->setViewToProjectionMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_EnterPassResource_setViewToProjectionMatrixImpl;
  self->setWorldToViewMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_EnterPassResource_setWorldToViewMatrixImpl;

  self->setCanvasSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_EnterPassResource_setCanvasSizeImpl;
  self->setClearColorBuffer = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_BooleanValue)) & Arcadia_Visuals_Implementation_EnterPassResource_setClearColorBufferImpl;
  self->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Math_Color4Real32*)) & Arcadia_Visuals_Implementation_EnterPassResource_setClearColorImpl;
  self->setClearDepthBuffer = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_BooleanValue)) & Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthBufferImpl;
  self->setClearDepth = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthImpl;
  self->setRelativeViewportRectangle = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_EnterPassResource*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_EnterPassResource_setRelativeViewportRectangleImpl;
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  )
{
  assert(NULL == self->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self
  )
{
  if (self->clearColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->clearColor);
  }
  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{
  Arcadia_Value other = Arcadia_Value_makeObjectReferenceValue(self->viewToProjectionMatrix);
  Arcadia_BooleanValue changed = Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)viewToProjectionMatrix, &other);
  Arcadia_Math_Matrix4Real32_assign(thread, self->viewToProjectionMatrix, viewToProjectionMatrix);
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_ViewToProjectionMatrixDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{
  Arcadia_Value other = Arcadia_Value_makeObjectReferenceValue(self->worldToViewMatrix);
  Arcadia_BooleanValue changed = Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)worldToViewMatrix, &other);
  Arcadia_Math_Matrix4Real32_assign(thread, self->worldToViewMatrix, worldToViewMatrix);
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_WorldToViewMatrixDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColorBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearColorBuffer
  )
{
  Arcadia_BooleanValue changed = self->clearColorBuffer != clearColorBuffer;
  self->clearColorBuffer = clearColorBuffer;
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_ClearColorDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Color4Real32* clearColor
  )
{
  // @todo Provide a comparison function.
  Arcadia_Math_Color4Real32_assign(thread, self->clearColor, clearColor);
  self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_ClearColorDirty;
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearDepthBuffer
  )
{
  Arcadia_BooleanValue changed = self->clearDepthBuffer != clearDepthBuffer;
  self->clearDepthBuffer = clearDepthBuffer;
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_ClearDepthDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value clearDepth
  )
{
  Arcadia_BooleanValue changed = self->clearDepth != clearDepth;
  self->clearDepth = clearDepth;
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_ClearDepthDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{
  Arcadia_BooleanValue changed = Arcadia_BooleanValue_False;
  changed |= self->relativeViewportRectangle.left != left;
  changed |= self->relativeViewportRectangle.bottom != bottom;
  changed |= self->relativeViewportRectangle.right != right;
  changed |= self->relativeViewportRectangle.top != top;
  self->relativeViewportRectangle.left = left;
  self->relativeViewportRectangle.bottom = bottom;
  self->relativeViewportRectangle.right = right;
  self->relativeViewportRectangle.top = top;
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_RelativeViewportRectangleDirty;
  }
}

static void
Arcadia_Visuals_Implementation_EnterPassResource_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{
  Arcadia_BooleanValue changed = self->canvasSize.width != width || self->canvasSize.height != height;
  self->canvasSize.width = width;
  self->canvasSize.height = height;
  if (changed) {
    self->dirty |= Arcadia_Visuals_Implementation_EnterPassResource_CanvasSizeDirty;
  }
}

void
Arcadia_Visuals_Implementation_EnterPassResource_setTargetFrameBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Visuals_Implementation_FrameBufferResource* frameBuffer
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setTargetFrameBuffer, self, frameBuffer); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setViewToProjectionMatrix, self, viewToProjectionMatrix); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setWorldToViewMatrix, self, worldToViewMatrix); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColorBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearColorBuffer
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setClearColorBuffer, self, clearColorBuffer); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Math_Color4Real32* clearColor
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setClearColor, self, clearColor); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepthBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_BooleanValue clearDepthBuffer
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setClearDepthBuffer, self, clearDepthBuffer); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value clearDepth
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setClearDepth, self, clearDepth); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setRelativeViewportRectangle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setRelativeViewportRectangle, self, left, bottom, right, top); }

void
Arcadia_Visuals_Implementation_EnterPassResource_setCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_EnterPassResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_EnterPassResource, setCanvasSize, self, width, height); }
