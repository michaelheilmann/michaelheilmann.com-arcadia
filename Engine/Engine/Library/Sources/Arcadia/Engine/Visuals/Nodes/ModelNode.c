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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/Nodes/ModelNode.h"

#include "Arcadia/Engine/Include.h"

static void
Arcadia_Engine_Visuals_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  );

static void
Arcadia_Engine_Visuals_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  );

static void
Arcadia_Engine_Visuals_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  );

static void
Arcadia_Engine_Visuals_ModelNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self,
    Arcadia_Engine_Visuals_EnterPassNode* enterPassNode
  );

static void
Arcadia_Engine_Visuals_ModelNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self,
    Arcadia_Engine_Visuals_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_ModelNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_ModelNode_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Visuals_ModelNode_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_ModelNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.ModelNode", Arcadia_Engine_Visuals_ModelNode,
                         u8"Arcadia.Engine.Visuals.Node", Arcadia_Engine_Visuals_Node,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Visuals_ModelNode);
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  // (1) get the node factory and the model definition
  Arcadia_ADL_ModelDefinition* source = (Arcadia_ADL_ModelDefinition*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_ModelDefinition_getType(thread));

  // (2) link the model definition
  Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)source);
  self->source = source;

  // (3) create the mesh node and the material node
  Arcadia_ADL_MeshDefinition* meshDefinition = (Arcadia_ADL_MeshDefinition*)source->mesh->definition;
  Arcadia_ADL_MaterialDefinition* materialDefinition = (Arcadia_ADL_MaterialDefinition*)source->material->definition;

  Arcadia_Engine* engine = Arcadia_Engine_getOrCreate(thread);
  self->mesh = Arcadia_Engine_Visuals_NodeFactory_createMeshNode(thread, (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory, NULL, meshDefinition);
  self->material = Arcadia_Engine_Visuals_NodeFactory_createMaterialNode(thread, (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory, NULL, materialDefinition);

  //
  if (Arcadia_ValueStack_isVoidValue(thread, 2)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Engine_Visuals_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  //
  self->modelResource = NULL;
  //

  Arcadia_LeaveConstructor(Arcadia_Engine_Visuals_ModelNode);
}

static void
Arcadia_Engine_Visuals_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  )
{
  if (self->backendContext) {
    if (self->modelResource) {
      Arcadia_Engine_Visuals_Implementation_Resource_unref(thread, (Arcadia_Engine_Visuals_Implementation_Resource*)self->modelResource);
      self->modelResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }  
}

static void
Arcadia_Engine_Visuals_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNodeDispatch* self
  )
{ 
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_EnterPassNode*)) & Arcadia_Engine_Visuals_ModelNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_ModelNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self
  )
{
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
  if (self->mesh) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->mesh);
  }
  if (self->material) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->material);
  }
}

static void
Arcadia_Engine_Visuals_ModelNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self,
    Arcadia_Engine_Visuals_EnterPassNode* enterPassNode
  )
{
  // (1) Render the material dependency.
  Arcadia_Engine_Visuals_MaterialNode* materialNode = (Arcadia_Engine_Visuals_MaterialNode*)((Arcadia_Engine_Visuals_ModelNode*)self)->material;
  Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)materialNode, (Arcadia_Engine_Visuals_EnterPassNode*)enterPassNode);
  // (2) Render the mesh dependency.
  Arcadia_Engine_Visuals_MeshNode* meshNode = (Arcadia_Engine_Visuals_MeshNode*)((Arcadia_Engine_Visuals_ModelNode*)self)->mesh;
  Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)meshNode, (Arcadia_Engine_Visuals_EnterPassNode*)enterPassNode);
  // (3) Create the model resource.
  if (self->backendContext) {
    if (!self->modelResource) {
      self->modelResource = Arcadia_Engine_Visuals_BackendContext_createModelResource(thread, (Arcadia_Engine_Visuals_BackendContext*)self->backendContext,
                                                                                              meshNode->meshResource,
                                                                                              materialNode->materialResource);
      Arcadia_Engine_Visuals_Implementation_Resource_ref(thread, (Arcadia_Engine_Visuals_Implementation_Resource*)self->modelResource);
    }
  }
  // (4) Perform actual render to frame buffer.
  if (self->backendContext) {
    // (4.2) Render the mesh resource.
    Arcadia_Engine_Visuals_Implementation_Resource_render(thread, (Arcadia_Engine_Visuals_Implementation_Resource*)self->modelResource,
                                                           ((Arcadia_Engine_Visuals_EnterPassNode*)enterPassNode)->enterPassResource);
  }
}

static void
Arcadia_Engine_Visuals_ModelNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ModelNode* self,
    Arcadia_Engine_Visuals_BackendContext* backendContext
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
    Arcadia_Engine_Visuals_Implementation_Resource_unref(thread, (Arcadia_Engine_Visuals_Implementation_Resource*)self->modelResource);
    self->modelResource = NULL;
  }
  self->backendContext = backendContext;
}

Arcadia_Engine_Visuals_ModelNode*
Arcadia_Engine_Visuals_ModelNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (source) Arcadia_ValueStack_pushObjectReferenceValue(thread, source); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_ModelNode);
}
