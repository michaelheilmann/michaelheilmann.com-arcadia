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
#include "Arcadia/Visuals/Implementation/Scene/ModelNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Resource.h"
#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/RenderingContextResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ViewportResource.h"

#include "Arcadia/Visuals/Implementation/Scene/MeshNode.h"
#include "Arcadia/Visuals/Implementation/Scene/MaterialNode.h"
#include "Arcadia/Visuals/Implementation/Scene/RenderingContextNode.h"
#include "Arcadia/Visuals/Implementation/Scene/TextureNode.h"

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNodeDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ModelNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ModelNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_ModelNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.ModelNode", Arcadia_Visuals_Implementation_Scene_ModelNode,
                         u8"Arcadia.Visuals.Scene.ModelNode", Arcadia_Visuals_Scene_ModelNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_ModelNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value sceneNodeFactory = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_Value source = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &sceneNodeFactory);
    Arcadia_ValueStack_pushValue(thread, &source);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_isVoidValue(thread, 3)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  //
  self->modelResource = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNodeDispatch* self
  )
{
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_Scene_RenderingContextNode*)) & Arcadia_Visuals_Implementation_Scene_ModelNode_renderImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_ModelNode_setBackendContextImpl;
}

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  )
{
  if (self->backendContext) {
    if (self->modelResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->modelResource);
      self->modelResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  )
{
  // (1) Render the material dependency.
  Arcadia_Visuals_Implementation_Scene_MaterialNode* materialNode = (Arcadia_Visuals_Implementation_Scene_MaterialNode*)((Arcadia_Visuals_Scene_ModelNode*)self)->material;
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)materialNode, (Arcadia_Visuals_Scene_RenderingContextNode*)renderingContextNode);
  // (2) Render the mesh dependency.
  Arcadia_Visuals_Implementation_Scene_MeshNode* meshNode = (Arcadia_Visuals_Implementation_Scene_MeshNode*)((Arcadia_Visuals_Scene_ModelNode*)self)->mesh;
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, (Arcadia_Visuals_Scene_RenderingContextNode*)renderingContextNode);
  // (3) Create the model resource.
  if (self->backendContext) {
    if (!self->modelResource) {
      self->modelResource = Arcadia_Visuals_Implementation_BackendContext_createModelResource(thread, self->backendContext,
                                                                                                      meshNode->meshResource,
                                                                                                      materialNode->materialResource);
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->modelResource);
    }
  }
  // (4) Perform actual render to frame buffer.
  if (self->backendContext) {
    // (4.1) Render the rendering context.
    Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)renderingContextNode, (Arcadia_Visuals_Scene_RenderingContextNode*)renderingContextNode);
    // (4.2) Render the mesh resource.
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->modelResource,
                                                   ((Arcadia_Visuals_Implementation_Scene_RenderingContextNode*)renderingContextNode)->renderingContextResource);
  }
}

static void
Arcadia_Visuals_Implementation_Scene_ModelNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_ModelNode* self,
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
  if (self->modelResource) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->modelResource);
    self->modelResource = NULL;
  }
  self->backendContext = backendContext;
}

Arcadia_Visuals_Implementation_Scene_ModelNode*
Arcadia_Visuals_Implementation_Scene_ModelNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_SceneNodeFactory* sceneNodeFactory,
    Arcadia_ADL_ModelDefinition* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (sceneNodeFactory) Arcadia_ValueStack_pushObjectReferenceValue(thread, sceneNodeFactory); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (source) Arcadia_ValueStack_pushObjectReferenceValue(thread, source); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_ModelNode);
}
