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

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"

#include "Arcadia/Visuals/Implementation/Configure.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Backend.h"

#include "Arcadia/VPL/Include.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/EnterPassResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FrameBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MaterialResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ModelResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

static Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*
createConstantBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource*
createFrameBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static Arcadia_Visuals_Implementation_OpenGL4_EnterPassResource*
createEnterPassResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static Arcadia_Visuals_Implementation_OpenGL4_MaterialResource*
createMaterialResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* ambientTexture,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* programResource
  );

static Arcadia_Visuals_Implementation_OpenGL4_MeshResource*
createMeshResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBufferResource
  );

static Arcadia_Visuals_Implementation_OpenGL4_ModelResource*
createModelResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* meshResource,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* materialResource
  );

static Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*
createProgramResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_VPL_Program* program
  );

static Arcadia_Visuals_Implementation_OpenGL4_TextureResource*
createTextureResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*
createVertexBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContextDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_BackendContext_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_BackendContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_BackendContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.Implementation.OpenGL4.BackendContext", Arcadia_Visuals_Implementation_OpenGL4_BackendContext,
                         u8"Arcadia.Engine.Visuals.Implementation.BackendContext", Arcadia_Visuals_Implementation_BackendContext,
                         &_typeOperations);

static Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*
createConstantBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* resource = Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource*
createFrameBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* resource =
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_create
      (
        thread,
        (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self
      );
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_EnterPassResource*
createEnterPassResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_EnterPassResource* resource = Arcadia_Visuals_Implementation_OpenGL4_EnterPassResource_create(thread, self);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_MaterialResource*
createMaterialResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* ambientTexture,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* programResource 
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* resource = Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self, ambientColorSource, ambientTexture, programResource);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_MeshResource*
createMeshResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBufferResource
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_MeshResource* resource = Arcadia_Visuals_Implementation_OpenGL4_MeshResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self, vertexBufferResource);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_ModelResource*
createModelResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* meshResource,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* materialResource
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_ModelResource* resource = Arcadia_Visuals_Implementation_OpenGL4_ModelResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self, meshResource, materialResource);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*
createProgramResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self,
    Arcadia_VPL_Program* program
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* resource = Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self, program);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_TextureResource*
createTextureResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_TextureResource* resource = Arcadia_Visuals_Implementation_OpenGL4_TextureResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*
createVertexBufferResourceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* resource = Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_create(thread, (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)self);
  assert(((Arcadia_Visuals_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  // Create and lock the list of resources.
  self->resources = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_lock(thread, (Arcadia_Object*)self->resources);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContextDispatch* self
  )
{
  self->getFunctions = NULL;

  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createConstantBufferResource = (Arcadia_Visuals_Implementation_ConstantBufferResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*)) & createConstantBufferResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createFrameBufferResource = (Arcadia_Visuals_Implementation_FrameBufferResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*)) & createFrameBufferResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createEnterPassResource = (Arcadia_Visuals_Implementation_EnterPassResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*)) & createEnterPassResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createMaterialResource = (Arcadia_Visuals_Implementation_MaterialResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*, Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_Implementation_ProgramResource*)) & createMaterialResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createMeshResource = (Arcadia_Visuals_Implementation_MeshResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*, Arcadia_Visuals_Implementation_VertexBufferResource*)) & createMeshResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createModelResource = (Arcadia_Visuals_Implementation_ModelResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Visuals_Implementation_MaterialResource*)) & createModelResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createProgramResource = (Arcadia_Visuals_Implementation_ProgramResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*, Arcadia_VPL_Program*)) & createProgramResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createTextureResource = (Arcadia_Visuals_Implementation_TextureResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*)) & createTextureResourceImpl;
  ((Arcadia_Visuals_Implementation_BackendContextDispatch*)self)->createVertexBufferResource = (Arcadia_Visuals_Implementation_VertexBufferResource * (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_BackendContext*)) & createVertexBufferResourceImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{
  // Unlock the list of resources.
  Arcadia_Object_unlock(thread, (Arcadia_Object*)self->resources);
  self->resources = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{/*Intentionally empty.*/}

_Arcadia_Visuals_Implementation_OpenGL4_Functions*
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_OpenGL4_BackendContext, getFunctions, self); }
