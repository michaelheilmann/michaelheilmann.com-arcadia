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
#include "Arcadia/Visuals/Scene/MaterialNode.h"

#include "Arcadia/Visuals/Include.h"

static void
Arcadia_Visuals_Scene_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.MaterialNode", Arcadia_Visuals_Scene_MaterialNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_MaterialNode_getType(thread);
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
  self->source = (Arcadia_ADL_MaterialDefinition*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_MaterialDefinition_getType(thread));
  Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)self->source);
  switch (self->source->ambientColorSource) {
    case Arcadia_ADL_AmbientColorSource_Mesh: {
      self->program = Arcadia_Visuals_VPL_Program_create(thread, Arcadia_Visuals_VPL_ProgramFlags_MeshAmbientColor);
    } break;
    case Arcadia_ADL_AmbientColorSource_Vertex: {
      self->program = Arcadia_Visuals_VPL_Program_create(thread, Arcadia_Visuals_VPL_ProgramFlags_VertexAmbientColor);
    } break;
    case Arcadia_ADL_AmbientColorSource_Texture: {
      self->program = Arcadia_Visuals_VPL_Program_create(thread, Arcadia_Visuals_VPL_ProgramFlags_TextureAmbientColor);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "unknown/unsupported ADL value for Mesh.ambientSource\n");
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    } break;
  };
  self->ambientColorTexture = Arcadia_Visuals_SceneNodeFactory_createTextureNode(thread, ((Arcadia_Visuals_Scene_Node*)self)->sceneNodeFactory, NULL, (Arcadia_ADL_TextureDefinition*)self->source->ambientColorTexture->definition);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_MaterialNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
  if (self->ambientColorTexture) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->ambientColorTexture);
  }
  if (self->program) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->program);
  }
}
