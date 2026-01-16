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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Scene/ModelNode.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/VertexDescriptorBuilder.h"

static void
Arcadia_Visuals_Scene_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
  );

static void
Arcadia_Visuals_Scene_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
  );

static void
Arcadia_Visuals_Scene_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_ModelNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_ModelNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_ModelNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.ModelNode", Arcadia_Visuals_Scene_ModelNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_ModelNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_ModelNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value sceneNodeFactory = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &sceneNodeFactory);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  // (1) get the scene node factory and the model definition
  Arcadia_Visuals_SceneNodeFactory* sceneNodeFactory =
    (Arcadia_Visuals_SceneNodeFactory*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_SceneNodeFactory_getType(thread));
  Arcadia_ADL_ModelDefinition* source =
    (Arcadia_ADL_ModelDefinition*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_ModelDefinition_getType(thread));

  // (2) link the model definition
  Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)source);
  self->source = source;

  // (3) create the mesh node and the material node
  Arcadia_ADL_MeshDefinition* meshDefinition = (Arcadia_ADL_MeshDefinition*)source->mesh->definition;
  Arcadia_ADL_MaterialDefinition* materialDefinition = (Arcadia_ADL_MaterialDefinition*)source->material->definition;
  
  self->mesh = Arcadia_Visuals_SceneNodeFactory_createMeshNode(thread, sceneNodeFactory, NULL, meshDefinition);
  self->material = Arcadia_Visuals_SceneNodeFactory_createMaterialNode(thread, sceneNodeFactory, NULL, materialDefinition); 

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_ModelNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_Scene_ModelNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
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
Arcadia_Visuals_Scene_ModelNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ModelNode* self
  )
{/*Intentionally empty.*/}
