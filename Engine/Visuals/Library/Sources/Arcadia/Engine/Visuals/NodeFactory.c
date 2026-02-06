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
#include "Arcadia/Engine/Visuals/NodeFactory.h"

static void
Arcadia_Engine_Visuals_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  );

static void
Arcadia_Engine_Visuals_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactoryDispatch* self
  );

static void
Arcadia_Engine_Visuals_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  );

static void
Arcadia_Engine_Visuals_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Visuals_NodeFactory_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Engine_Visuals_NodeFactory_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_NodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_NodeFactory_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Visuals_NodeFactory_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Visuals_NodeFactory_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.NodeFactory", Arcadia_Engine_Visuals_NodeFactory,
                         u8"Arcadia.Engine.NodeFactory", Arcadia_Engine_NodeFactory,
                         &_Arcadia_Engine_Visuals_NodeFactory_typeOperations);

static void
Arcadia_Engine_Visuals_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_NodeFactory_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Engine_Visuals_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactoryDispatch* self
  )
{ }

static void
Arcadia_Engine_Visuals_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self
  )
{/*Intentionally empty.*/}

Arcadia_Engine_Visuals_CameraNode*
Arcadia_Engine_Visuals_NodeFactory_createCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createCameraNode, self, backendContext); }

Arcadia_Visuals_FrameBufferNode*
Arcadia_Engine_Visuals_NodeFactory_createFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createFrameBufferNode, self, backendContext); }

Arcadia_Engine_Visuals_RenderingContextNode*
Arcadia_Engine_Visuals_NodeFactory_createRenderingContextNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createRenderingContextNode, self, backendContext); }

Arcadia_Engine_Visuals_MaterialNode*
Arcadia_Engine_Visuals_NodeFactory_createMaterialNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_ADL_MaterialDefinition* source
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createMaterialNode, self, backendContext, source); }

Arcadia_Engine_Visuals_MeshNode*
Arcadia_Engine_Visuals_NodeFactory_createMeshNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_ADL_MeshDefinition* source
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createMeshNode, self, backendContext, source); }

Arcadia_Engine_Visuals_ModelNode*
Arcadia_Engine_Visuals_NodeFactory_createModelNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createModelNode, self, backendContext, source); }

Arcadia_Engine_Visuals_PixelBufferNode*
Arcadia_Engine_Visuals_NodeFactory_createPixelBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_ADL_PixelBufferDefinition* source
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createPixelBufferNode, self, backendContext, source); }

Arcadia_Engine_Visuals_TextureNode*
Arcadia_Engine_Visuals_NodeFactory_createTextureNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_ADL_TextureDefinition* source
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createTextureNode, self, backendContext, source); }

Arcadia_Engine_Visuals_ViewportNode*
Arcadia_Engine_Visuals_NodeFactory_createViewportNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_NodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_NodeFactory, createViewportNode, self, backendContext); }
