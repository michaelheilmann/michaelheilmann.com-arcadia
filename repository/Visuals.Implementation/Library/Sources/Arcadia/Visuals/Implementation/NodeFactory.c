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
#include "Arcadia/Visuals/Implementation/NodeFactory.h"

#include "Arcadia/Visuals/Implementation/Nodes/CameraNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/FrameBufferNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/RenderingContextNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/MaterialNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/MeshNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/ModelNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/PixelBufferNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/TextureNode.h"
#include "Arcadia/Visuals/Implementation/Nodes/ViewportNode.h"

static void
Arcadia_Visuals_Implementation_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  );

static void
Arcadia_Visuals_Implementation_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactoryDispatch* self
  );

static void
Arcadia_Visuals_Implementation_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  );

static void
Arcadia_Visuals_Implementation_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  );

static Arcadia_Engine_Visuals_Implementation_CameraNode*
Arcadia_Visuals_Implementation_NodeFactory_createCameraNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Engine_Visuals_Implementation_FrameBufferNode*
Arcadia_Visuals_Implementation_NodeFactory_createFrameBufferNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Engine_Visuals_Implementation_MaterialNode*
Arcadia_Visuals_Implementation_NodeFactory_createMaterialNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MaterialDefinition* source
  );

static Arcadia_Engine_Visuals_Implementation_MeshNode*
Arcadia_Visuals_Implementation_NodeFactory_createMeshNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MeshDefinition* source
  );

static Arcadia_Engine_Visuals_Implementation_ModelNode*
Arcadia_Visuals_Implementation_NodeFactory_createModelNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  );

static Arcadia_Engine_Visuals_Implementation_PixelBufferNode*
Arcadia_Visuals_Implementation_NodeFactory_createPixelBufferNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_PixelBufferDefinition* source
  );

static Arcadia_Engine_Visuals_Implementation_RenderingContextNode*
Arcadia_Visuals_Implementation_NodeFactory_createRenderingContextNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static Arcadia_Engine_Visuals_Implementation_TextureNode*
Arcadia_Visuals_Implementation_NodeFactory_createTextureNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_TextureDefinition* source
  );

static Arcadia_Engine_Visuals_Implementation_ViewportNode*
Arcadia_Visuals_Implementation_NodeFactory_createViewportNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_NodeFactory_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_NodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_NodeFactory_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Visuals.Implementation.NodeFactory", Arcadia_Visuals_Implementation_NodeFactory,
                         u8"Arcadia.Visuals.NodeFactory", Arcadia_Engine_Visuals_NodeFactory,
                         &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_NodeFactory_getType(thread);
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
Arcadia_Visuals_Implementation_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactoryDispatch* self
  )
{
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createCameraNode = (Arcadia_Engine_Visuals_CameraNode *(*)(Arcadia_Thread * thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_NodeFactory_createCameraNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createFrameBufferNode = (Arcadia_Visuals_FrameBufferNode *(*)(Arcadia_Thread * thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_NodeFactory_createFrameBufferNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createRenderingContextNode = (Arcadia_Engine_Visuals_RenderingContextNode * (*)(Arcadia_Thread * thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_NodeFactory_createRenderingContextNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createMaterialNode = (Arcadia_Engine_Visuals_MaterialNode *(*)(Arcadia_Thread*, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*, Arcadia_ADL_MaterialDefinition*)) & Arcadia_Visuals_Implementation_NodeFactory_createMaterialNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createMeshNode = (Arcadia_Engine_Visuals_MeshNode *(*)(Arcadia_Thread* thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*, Arcadia_ADL_MeshDefinition*)) & Arcadia_Visuals_Implementation_NodeFactory_createMeshNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createModelNode = (Arcadia_Engine_Visuals_ModelNode * (*)(Arcadia_Thread * thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*, Arcadia_ADL_ModelDefinition*)) & Arcadia_Visuals_Implementation_NodeFactory_createModelNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createPixelBufferNode = (Arcadia_Engine_Visuals_PixelBufferNode * (*)(Arcadia_Thread * thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*, Arcadia_ADL_PixelBufferDefinition*)) & Arcadia_Visuals_Implementation_NodeFactory_createPixelBufferNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createTextureNode = (Arcadia_Engine_Visuals_TextureNode *(*)(Arcadia_Thread* thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*, Arcadia_ADL_TextureDefinition*)) & Arcadia_Visuals_Implementation_NodeFactory_createTextureNodeImpl;
  ((Arcadia_Engine_Visuals_NodeFactoryDispatch*)self)->createViewportNode = (Arcadia_Engine_Visuals_ViewportNode * (*)(Arcadia_Thread* thread, Arcadia_Engine_Visuals_NodeFactory*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_NodeFactory_createViewportNodeImpl;
}

static void
Arcadia_Visuals_Implementation_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self
  )
{/*Intentionally empty.*/}

static Arcadia_Engine_Visuals_Implementation_CameraNode*
Arcadia_Visuals_Implementation_NodeFactory_createCameraNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Engine_Visuals_Implementation_CameraNode_create(thread, backendContext); }

static Arcadia_Engine_Visuals_Implementation_FrameBufferNode*
Arcadia_Visuals_Implementation_NodeFactory_createFrameBufferNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Engine_Visuals_Implementation_FrameBufferNode_create(thread, backendContext); }

static Arcadia_Engine_Visuals_Implementation_MaterialNode*
Arcadia_Visuals_Implementation_NodeFactory_createMaterialNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MaterialDefinition* source
  )
{ return Arcadia_Engine_Visuals_Implementation_MaterialNode_create(thread, backendContext, source); }

static Arcadia_Engine_Visuals_Implementation_MeshNode*
Arcadia_Visuals_Implementation_NodeFactory_createMeshNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MeshDefinition* source
  )
{ return Arcadia_Engine_Visuals_Implementation_MeshNode_create(thread, backendContext, source); }

static Arcadia_Engine_Visuals_Implementation_ModelNode*
Arcadia_Visuals_Implementation_NodeFactory_createModelNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  )
{ return Arcadia_Engine_Visuals_Implementation_ModelNode_create(thread, backendContext, source); }

static Arcadia_Engine_Visuals_Implementation_PixelBufferNode*
Arcadia_Visuals_Implementation_NodeFactory_createPixelBufferNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_PixelBufferDefinition* source
  )
{ return Arcadia_Engine_Visuals_Implementation_PixelBufferNode_create(thread, backendContext, source); }

static Arcadia_Engine_Visuals_Implementation_RenderingContextNode*
Arcadia_Visuals_Implementation_NodeFactory_createRenderingContextNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Engine_Visuals_Implementation_RenderingContextNode_create(thread, backendContext); }

static Arcadia_Engine_Visuals_Implementation_TextureNode*
Arcadia_Visuals_Implementation_NodeFactory_createTextureNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_TextureDefinition* source
  )
{ return Arcadia_Engine_Visuals_Implementation_TextureNode_create(thread, backendContext, source); }

static Arcadia_Engine_Visuals_Implementation_ViewportNode*
Arcadia_Visuals_Implementation_NodeFactory_createViewportNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_NodeFactory* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Engine_Visuals_Implementation_ViewportNode_create(thread, backendContext); }

Arcadia_Visuals_Implementation_NodeFactory*
Arcadia_Visuals_Implementation_NodeFactory_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_NodeFactory);
}
