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

#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  );

static Arcadia_SizeValue
Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_VertexBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Visuals_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_VertexBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_VertexBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_VertexBufferResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.VertexBufferResource", Arcadia_Visuals_Implementation_VertexBufferResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_VertexBufferResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
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
  Arcadia_Visuals_VertexDescriptorBuilder* vertexDescriptorBuilder = Arcadia_Visuals_VertexDescriptorBuilder_create(thread);
  self->vertexDescriptor = Arcadia_Visuals_VertexDescriptorBuilder_build(thread, vertexDescriptorBuilder);
  //
  self->numberOfVertices = 0;
  self->numberOfBytes = 0;
  self->bytes = Arcadia_Memory_allocateUnmanaged(thread, 0);
  //
  self->dirty = Arcadia_Visuals_Implementation_VertexBufferResource_VertexDataDirty
              | Arcadia_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResourceDispatch* self
  )
{
  self->setData = Arcadia_Visuals_Implementation_VertexBufferResource_setDataImpl;
  self->getNumberOVertices = Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl;
}

static void
Arcadia_Visuals_Implementation_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  )
{
  if (self->bytes) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->bytes);
    self->bytes = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  )
{
  if (self->vertexDescriptor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexDescriptor);
  }
}

static Arcadia_SizeValue
Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVerticesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  )
{ return self->numberOfVertices; }

static void
Arcadia_Visuals_Implementation_VertexBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Visuals_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_Memory_reallocateUnmanaged(thread, &self->bytes, numberOfBytes);
  Arcadia_Memory_copy(thread, self->bytes, bytes, numberOfBytes);
  self->vertexDescriptor = vertexDescriptor;
  self->numberOfBytes = numberOfBytes;
  self->numberOfVertices = numberOfVertices;
  self->dirty = Arcadia_Visuals_Implementation_VertexBufferResource_VertexDataDirty
              | Arcadia_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty;
}

void
Arcadia_Visuals_Implementation_VertexBufferResource_setData
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Visuals_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_VertexBufferResource, setData, self, vertexDescriptor, numberOfVertices, bytes, numberOfBytes); }

Arcadia_SizeValue
Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_VertexBufferResource* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_VertexBufferResource, getNumberOVertices, self); }
