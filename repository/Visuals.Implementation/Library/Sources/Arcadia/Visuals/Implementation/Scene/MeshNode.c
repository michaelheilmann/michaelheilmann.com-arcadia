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

#include "Arcadia/Visuals/Implementation/Scene/MeshNode.h"

#include "Arcadia/Visuals/Implementation/Resource.h"
#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ViewportResource.h"
#include "Arcadia/Visuals/Implementation/BackendContext.h"

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshNode_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_MeshNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.MeshNode", Arcadia_Visuals_Implementation_Scene_MeshNode,
                         u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_MeshNode_getType(thread);
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
  self->meshResource = NULL;
  ((Arcadia_Visuals_Scene_Node*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*)) & Arcadia_Visuals_Implementation_Scene_MeshNode_renderImpl;
  ((Arcadia_Visuals_Scene_Node*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) &Arcadia_Visuals_Implementation_Scene_MeshNode_setBackendContextImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  )
{
  if (self->backendContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backendContext);
  }
  if (self->meshResource) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshResource);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self
  )
{
  if (self->backendContext) {
    if (!self->meshResource) {
      Arcadia_Visuals_Implementation_BackendContext* backendContext = self->backendContext;
      // (1) vertex buffer
      Arcadia_Visuals_Implementation_VertexBufferResource* vertexBufferResource = NULL;
      vertexBufferResource = Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource(thread, backendContext);
      Arcadia_Visuals_Implementation_VertexBufferResource_setData
        (
          thread,
          vertexBufferResource,
          ((Arcadia_Visuals_Scene_MeshNode*)self)->numberOfVertices,
          (void*)((Arcadia_Visuals_Scene_MeshNode*)self)->vertexPositions,
          ((Arcadia_Visuals_Scene_MeshNode*)self)->numberOfVertices * sizeof(Arcadia_Real32Value) * 3
        );
      // (2) program
      Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgramResource = NULL;
      vertexProgramResource = Arcadia_Visuals_Implementation_BackendContext_createVertexProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
      Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgramResource = NULL;
      fragmentProgramResource = Arcadia_Visuals_Implementation_BackendContext_createFragmentProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
      Arcadia_Visuals_Implementation_ProgramResource* programResource = NULL;
      programResource = Arcadia_Visuals_Implementation_BackendContext_createProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext, vertexProgramResource, fragmentProgramResource);
      // (3) mesh
      self->meshResource =
        Arcadia_Visuals_Implementation_BackendContext_createMeshResource
          (
            thread,
            backendContext,
            vertexBufferResource,
            programResource
          );
      ((Arcadia_Visuals_Implementation_Resource*)self->meshResource)->referenceCount++;

      // (4) Set the matrices of the mesh resource.
      Arcadia_Math_Matrix4Real32* localToWorldMatrix = Arcadia_Math_Matrix4Real32_create(thread);
      Arcadia_Math_Matrix4Real32_setIdentity(thread, localToWorldMatrix);
      Arcadia_Visuals_Implemention_MeshResource_setLocalToWorldMatrix(thread, self->meshResource, localToWorldMatrix);

      Arcadia_Math_Matrix4Real32* viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
      Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection(thread, viewToProjectionMatrix, 60.f, 4.f / 3.f, 0.1f, +100.f);
      Arcadia_Visuals_Implemention_MeshResource_setViewToProjectionMatrix(thread, self->meshResource, viewToProjectionMatrix);

      // Move the camera along the positive right axis and along the positive z axis by multiplying the camera position by `translate(0, 0, 1)`.
      // However, as we actually do not transform the camera position but the position of the objects in world space,
      // we actually have to use the inverse `inverse(translate(0, 0, 1))`.
      Arcadia_Math_Matrix4Real32* worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
      Arcadia_Math_MatrixReal32Value_setTranslation(thread, worldToViewMatrix, 0.f, 0.f, -1.f);
      Arcadia_Visuals_Implemention_MeshResource_setWorldToViewMatrix(thread, self->meshResource, worldToViewMatrix);
    }
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshResource);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_MeshNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_MeshNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  if (self->backendContext) {
    if (self->meshResource) {
      ((Arcadia_Visuals_Implementation_Resource*)self->meshResource)->referenceCount--;
      self->meshResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

Arcadia_Visuals_Implementation_Scene_MeshNode*
Arcadia_Visuals_Implementation_Scene_MeshNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_MeshNode);
}
