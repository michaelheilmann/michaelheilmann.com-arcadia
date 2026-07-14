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
#include "Arcadia/Engine/Visuals/Resources/VertexBufferResource.h"

#include "Arcadia/Engine/Visuals/BackendContext.h"
#include <assert.h>

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResourceDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  );

static Arcadia_SizeValue
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Media_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_VertexBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_VertexBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_VertexBufferResource_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_VertexBufferResource_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.VertexBufferResource", Arcadia_Engine_Visuals_Implementation_VertexBufferResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Engine_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Visuals_Implementation_VertexBufferResource);
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  Arcadia_Media_VertexDescriptorBuilder* vertexDescriptorBuilder = Arcadia_Media_VertexDescriptorBuilder_create(thread);
  self->vertexDescriptor = Arcadia_Media_VertexDescriptorBuilder_build(thread, vertexDescriptorBuilder);
  //
  self->numberOfVertices = 0;
  self->numberOfBytes = 0;
  self->bytes = Arcadia_Memory_allocateUnmanaged(thread, 0);
  //
  self->dirty = Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDataDirty
              | Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty;
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Visuals_Implementation_VertexBufferResource);
}

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResourceDispatch* self
  )
{
  self->setData = Arcadia_Engine_Visuals_Implementation_VertexBufferResource_setDataImpl;
  self->getNumberOVertices = Arcadia_Engine_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  )
{
  if (self->bytes) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->bytes);
    self->bytes = NULL;
  }
}

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  )
{
  if (self->vertexDescriptor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexDescriptor);
  }
}

static Arcadia_SizeValue
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  )
{ return self->numberOfVertices; }

static void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Media_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_Memory_reallocateUnmanaged(thread, (void**)&self->bytes, numberOfBytes);
  Arcadia_Memory_copy(thread, self->bytes, bytes, numberOfBytes);
  self->vertexDescriptor = vertexDescriptor;
  self->numberOfBytes = numberOfBytes;
  self->numberOfVertices = numberOfVertices;
  self->dirty = Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDataDirty
              | Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty;
}

void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_setData
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Media_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Visuals_Implementation_VertexBufferResource, setData, self, vertexDescriptor, numberOfVertices, bytes, numberOfBytes); }

Arcadia_SizeValue
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Visuals_Implementation_VertexBufferResource, getNumberOVertices, self); }
