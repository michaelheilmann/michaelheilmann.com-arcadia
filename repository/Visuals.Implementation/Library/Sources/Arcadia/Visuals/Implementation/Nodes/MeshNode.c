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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/Nodes/MeshNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Resource.h"
#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/RenderingContextResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ViewportResource.h"

#include "Arcadia/Visuals/Implementation/Nodes/MaterialNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/RenderingContextNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/TextureNode.h"

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.MeshNode", Arcadia_Engine_Visuals_Implementation_MeshNode,
                         u8"Arcadia.Engine.Visuals.MeshNode", Arcadia_Engine_Visuals_MeshNode,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_Implementation_MeshNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value source = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &source);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_isVoidValue(thread, 2)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  self->meshResource = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNodeDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_RenderingContextNode*)) & Arcadia_Engine_Visuals_Implementation_MeshNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_Implementation_MeshNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  )
{
  if (self->backendContext) {
    if (self->meshResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshResource);
      self->meshResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self,
    Arcadia_Engine_Visuals_Implementation_RenderingContextNode* renderingContextNode
  )
{
  // (1) Set the backend context.
  Arcadia_Engine_Node_setVisualsBackendContext(thread, (Arcadia_Engine_Node*)self, (Arcadia_Engine_Visuals_BackendContext*)renderingContextNode->backendContext);
  // (2) Setup resources.
  if (self->backendContext) {
    if (!self->meshResource) {
      Arcadia_Visuals_Implementation_BackendContext* backendContext = self->backendContext;
      // (2.1) vertex buffer resource
      Arcadia_Visuals_Implementation_VertexBufferResource* vertexBufferResource = NULL;
      vertexBufferResource = Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource(thread, backendContext);
      Arcadia_Visuals_Implementation_VertexBufferResource_setData
        (
          thread,
          vertexBufferResource,
          ((Arcadia_Engine_Visuals_MeshNode*)self)->vertexDescriptor,
          ((Arcadia_Engine_Visuals_MeshNode*)self)->numberOfVertices,
          (void*)((Arcadia_Engine_Visuals_MeshNode*)self)->vertices,
          ((Arcadia_Engine_Visuals_MeshNode*)self)->numberOfVertices * ((Arcadia_Engine_Visuals_MeshNode*)self)->vertexDescriptor->stride
        );
      // (2.2) mesh resource
      self->meshResource =
        Arcadia_Visuals_Implementation_BackendContext_createMeshResource
          (
            thread,
            backendContext,
            vertexBufferResource
          );
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshResource);
      // (2.3) Set the mesh ambient color of the mesh resource.
      Arcadia_Visuals_Implementation_MeshResource_setMeshAmbientColor(thread, self->meshResource, ((Arcadia_Engine_Visuals_MeshNode*)self)->ambientColor);
    }
  }
}

static void
Arcadia_Engine_Visuals_Implementation_MeshNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshNode* self,
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
  if (self->meshResource) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshResource);
    self->meshResource = NULL;
  }
  self->backendContext = backendContext;
}

Arcadia_Engine_Visuals_Implementation_MeshNode*
Arcadia_Engine_Visuals_Implementation_MeshNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MeshDefinition* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (source) Arcadia_ValueStack_pushObjectReferenceValue(thread, source); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_MeshNode);
}
