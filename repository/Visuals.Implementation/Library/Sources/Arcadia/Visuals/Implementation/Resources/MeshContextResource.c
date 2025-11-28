// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/Visuals/Implementation/Resources/MeshContextResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

#define Arcadia_Visuals_Implementation_MeshContextResource_ViewToProjectionMatrixDirty (1)
#define Arcadia_Visuals_Implementation_MeshContextResource_WorldToViewMatrixDirty (2)

static void
Arcadia_Visuals_Implementation_MeshContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

static void
Arcadia_Visuals_Implementation_MeshContextResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_MeshContextResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_MeshContextResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_MeshContextResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.MeshContextResource", Arcadia_Visuals_Implementation_MeshContextResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_MeshContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_MeshContextResource_getType(thread);
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

  self->dirty = Arcadia_Visuals_Implementation_MeshContextResource_ViewToProjectionMatrixDirty
              | Arcadia_Visuals_Implementation_MeshContextResource_WorldToViewMatrixDirty
              ;

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  Arcadia_Visuals_Implementation_BackendContext* backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
  self->viewerConstantBuffer = (Arcadia_Visuals_Implementation_ConstantBufferResource*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);

  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer);

  ((Arcadia_Visuals_Implementation_Resource*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_MeshContextResource_loadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_MeshContextResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_MeshContextResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_MeshContextResource*)) & Arcadia_Visuals_Implementation_MeshContextResource_renderImpl;
  self->setViewToProjectionMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshContextResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_MeshContextResource_setViewToProjectionMatrixImpl;
  self->setWorldToViewMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshContextResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_MeshContextResource_setWorldToViewMatrixImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  )
{
  assert(NULL == self->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
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
Arcadia_Visuals_Implementation_MeshContextResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  )
{
  static const Arcadia_Natural8Value matrixMask = Arcadia_Visuals_Implementation_MeshContextResource_ViewToProjectionMatrixDirty
                                                | Arcadia_Visuals_Implementation_MeshContextResource_WorldToViewMatrixDirty
                                                ;

  if (self->dirty & matrixMask) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer, Arcadia_BooleanValue_True, self->viewToProjectionMatrix);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer, Arcadia_BooleanValue_True, self->worldToViewMatrix);
    self->dirty &= ~matrixMask;
  }
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_MeshContextResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self
  )
{
  if (self->viewerConstantBuffer) {
    ((Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer)->referenceCount--;
    self->viewerConstantBuffer = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  )
{
  static const Arcadia_Natural8Value matrixMask = Arcadia_Visuals_Implementation_MeshContextResource_ViewToProjectionMatrixDirty
                                                | Arcadia_Visuals_Implementation_MeshContextResource_WorldToViewMatrixDirty
                                                ;

  if (self->dirty & matrixMask) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer, Arcadia_BooleanValue_True, self->viewToProjectionMatrix);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->viewerConstantBuffer, Arcadia_BooleanValue_True, self->worldToViewMatrix);
    self->dirty &= ~matrixMask;
  }
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{
  self->viewToProjectionMatrix = viewToProjectionMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_MeshContextResource_ViewToProjectionMatrixDirty;
}

static void
Arcadia_Visuals_Implementation_MeshContextResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{
  self->worldToViewMatrix = worldToViewMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_MeshContextResource_WorldToViewMatrixDirty;
}

Arcadia_Visuals_Implementation_MeshContextResource*
Arcadia_Visuals_Implementation_MeshContextResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_MeshContextResource);
}

void
Arcadia_Visuals_Implemention_MeshContextResource_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{ self->setViewToProjectionMatrix(thread, self, viewToProjectionMatrix); }

void
Arcadia_Visuals_Implemention_MeshContextResource_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{ self->setWorldToViewMatrix(thread, self, worldToViewMatrix); }
