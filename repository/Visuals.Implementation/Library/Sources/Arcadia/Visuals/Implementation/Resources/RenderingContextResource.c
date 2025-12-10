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

#include "Arcadia/Visuals/Implementation/Resources/RenderingContextResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_RenderingContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_RenderingContextResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_RenderingContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_RenderingContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

static void
Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_RenderingContextResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_RenderingContextResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_RenderingContextResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.RenderingContextResource", Arcadia_Visuals_Implementation_RenderingContextResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_RenderingContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_RenderingContextResource_getType(thread);
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

  self->dirty = Arcadia_Visuals_Implementation_RenderingContextResource_ViewToProjectionMatrixDirty
              | Arcadia_Visuals_Implementation_RenderingContextResource_WorldToViewMatrixDirty
              ;

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  Arcadia_Visuals_Implementation_BackendContext* backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
  self->viewerConstantBuffer = (Arcadia_Visuals_Implementation_ConstantBufferResource*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);

  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_RenderingContextResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResourceDispatch* self
  )
{ 
  self->setViewToProjectionMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrixImpl;
  self->setWorldToViewMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrixImpl;
}

static void
Arcadia_Visuals_Implementation_RenderingContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  )
{
  assert(NULL == self->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_RenderingContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self
  )
{
  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
}

static void
Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{
  self->viewToProjectionMatrix = viewToProjectionMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_RenderingContextResource_ViewToProjectionMatrixDirty;
}

static void
Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{
  self->worldToViewMatrix = worldToViewMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_RenderingContextResource_WorldToViewMatrixDirty;
}

void
Arcadia_Visuals_Implementation_RenderingContextResource_setTargetFrameBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_FrameBufferResource* frameBuffer
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_RenderingContextResource, setTargetFrameBuffer, self, frameBuffer); }

void
Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_RenderingContextResource, setViewToProjectionMatrix, self, viewToProjectionMatrix); }

void
Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_RenderingContextResource, setWorldToViewMatrix, self, worldToViewMatrix); }
