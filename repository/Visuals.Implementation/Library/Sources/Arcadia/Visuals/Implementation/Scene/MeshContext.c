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

#include "Arcadia/Visuals/Implementation/Scene/MeshContext.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshContext_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.MeshContext", Arcadia_Visuals_Implementation_Scene_MeshContext,
                         u8"Arcadia.Visuals.Scene.MeshContext", Arcadia_Visuals_Scene_MeshContext,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_MeshContext_getType(thread);
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
  }
  self->meshContextResource = NULL;

  ((Arcadia_Visuals_Scene_MeshContext*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_MeshContext*)) & Arcadia_Visuals_Implementation_Scene_MeshContext_renderImpl;
  ((Arcadia_Visuals_Scene_MeshContext*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_MeshContext*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_MeshContext_setBackendContextImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  )
{ 
  if (self->meshContextResource) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshContextResource);
  }
  if (self->backendContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backendContext);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self
  )
{
  if (self->backendContext) {
    if (!self->meshContextResource) {
      self->meshContextResource =
        Arcadia_Visuals_Implementation_BackendContext_createMeshContextResource
          (
            thread,
            self->backendContext
          );
    }

    // @todo Track if the matrices were actually modified.
    // (1) Hardcoded matrices for now:
    Arcadia_Math_Matrix4Real32_setIdentity(thread, ((Arcadia_Visuals_Scene_MeshContext*)self)->worldToViewMatrix);
    // (1.1) World-to-View matrix: Move the camera along the positive right axis and along the positive z axis by multiplying the camera position by `translate(0, 0, 1)`.
    // However, as we actually do not transform the camera position but the position of the objects in world space,
    // we actually have to use the inverse `inverse(translate(0, 0, 1))`.
    Arcadia_Math_MatrixReal32Value_setTranslation(thread, ((Arcadia_Visuals_Scene_MeshContext*)self)->worldToViewMatrix, 0.f, 0.f, -1.f);
    // (1.2) View-to-Projection matrix: Use a perspective projection matrix for the camera.
    Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection(thread, ((Arcadia_Visuals_Scene_MeshContext*)self)->viewToProjectionMatrix, 60.f, 4.f / 3.f, 0.1f, +100.f);

    Arcadia_Visuals_Implemention_MeshContextResource_setWorldToViewMatrix(thread, self->meshContextResource, ((Arcadia_Visuals_Scene_MeshContext*)self)->worldToViewMatrix);
    Arcadia_Visuals_Implemention_MeshContextResource_setViewToProjectionMatrix(thread, self->meshContextResource, ((Arcadia_Visuals_Scene_MeshContext*)self)->viewToProjectionMatrix);

    Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshContextResource);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_MeshContext_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshContext* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  if (self->backendContext) {
    if (self->meshContextResource) {
      ((Arcadia_Visuals_Implementation_Resource*)self->meshContextResource)->referenceCount--;
      self->meshContextResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

Arcadia_Visuals_Implementation_Scene_MeshContext*
Arcadia_Visuals_Implementation_Scene_MeshContext_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_MeshContext);
}
