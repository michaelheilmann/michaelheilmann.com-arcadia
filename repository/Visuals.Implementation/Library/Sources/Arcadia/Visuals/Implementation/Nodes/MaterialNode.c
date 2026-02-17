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
#include "Arcadia/Visuals/Implementation/Nodes/MaterialNode.h"

#include "Arcadia/Visuals/Implementation/Nodes/TextureNode.h"
#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Nodes/EnterPassNode.h"
#include "Arcadia/Visuals/Implementation/Resource.h"

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  );

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MaterialNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MaterialNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.MaterialNode", Arcadia_Engine_Visuals_Implementation_MaterialNode,
                         u8"Arcadia.Engine.Visuals.MaterialNode", Arcadia_Engine_Visuals_MaterialNode,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_Implementation_MaterialNode_getType(thread);
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
  self->materialResource = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNodeDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_EnterPassNode*)) & Arcadia_Engine_Visuals_Implementation_MaterialNode_renderImpl;
  ((Arcadia_Engine_NodeDispatch*)self)->setVisualsBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*)) & Arcadia_Engine_Visuals_Implementation_MaterialNode_setVisualsBackendContextImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self
  )
{
  if (self->backendContext) {
    if (self->materialResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->materialResource);
      self->materialResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self,
    Arcadia_Engine_Visuals_Implementation_EnterPassNode* renderingContextNode
  )
{
  Arcadia_Engine_Node_setVisualsBackendContext(thread, (Arcadia_Engine_Node*)self, (Arcadia_Engine_Visuals_BackendContext*)renderingContextNode->backendContext);
  Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)((Arcadia_Engine_Visuals_MaterialNode*)self)->ambientColorTexture, (Arcadia_Engine_Visuals_EnterPassNode*)renderingContextNode);
  if (self->backendContext) {
    if (!self->materialResource) {
      Arcadia_Visuals_Implementation_BackendContext* backendContext = self->backendContext;
      //
      Arcadia_Visuals_Implementation_ProgramResource* programResource = 
        Arcadia_Visuals_Implementation_BackendContext_createProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext,
                                                                                    ((Arcadia_Engine_Visuals_MaterialNode*)self)->program);
      //
      Arcadia_Visuals_Implementation_TextureResource* textureResource =
        ((Arcadia_Engine_Visuals_Implementation_TextureNode*)((Arcadia_Engine_Visuals_MaterialNode*)self)->ambientColorTexture)->textureResource;

      Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource = Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource_Mesh;
      switch (((Arcadia_Engine_Visuals_MaterialNode*)self)->source->ambientColorSource) {
        case Arcadia_ADL_AmbientColorSource_Mesh: {
          ambientColorSource = Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource_Mesh;
        } break;
        case Arcadia_ADL_AmbientColorSource_Vertex: {
          ambientColorSource = Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource_Vertex;
        } break;
        case Arcadia_ADL_AmbientColorSource_Texture: {
          ambientColorSource = Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource_Texture;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
 
      self->materialResource = Arcadia_Visuals_Implementation_BackendContext_createMaterialResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext, ambientColorSource, textureResource, programResource);
      Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->materialResource);
    }
  }
}

static void
Arcadia_Engine_Visuals_Implementation_MaterialNode_setVisualsBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MaterialNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  if (((Arcadia_Engine_Visuals_MaterialNode*)self)->ambientColorTexture) {
    Arcadia_Engine_Node_setVisualsBackendContext(thread, (Arcadia_Engine_Node*)((Arcadia_Engine_Visuals_MaterialNode*)self)->ambientColorTexture, (Arcadia_Engine_Visuals_BackendContext*)backendContext);
  }
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
  if (self->materialResource) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->materialResource);
    self->materialResource = NULL;
  }
  self->backendContext = backendContext;
}

Arcadia_Engine_Visuals_Implementation_MaterialNode*
Arcadia_Engine_Visuals_Implementation_MaterialNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MaterialDefinition* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (source) Arcadia_ValueStack_pushObjectReferenceValue(thread, source); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_MaterialNode);
}
