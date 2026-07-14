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

#define ARCADIA_MEDIA_MODULE (1)
#include "Arcadia/Media/VertexBuffer.h"

#include "Arcadia/Media/Include.h"

static void
Arcadia_Media_VertexBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  );

static void
Arcadia_Media_VertexBuffer_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  );

static void
Arcadia_Media_VertexBuffer_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBufferDispatch* self
  );

static void
Arcadia_Media_VertexBuffer_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Media_VertexBuffer_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Media_VertexBuffer_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Media_VertexBuffer_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Media_VertexBuffer_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Media.VertexBuffer", Arcadia_Media_VertexBuffer,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Media_VertexBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Media_VertexBuffer);
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->vertexDescriptor = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Media_VertexDescriptor_getType(thread));
  self->numberOfVertices = Arcadia_ValueStack_getSizeValue(thread, 1);
  Arcadia_SizeValue numberOfBytes = self->vertexDescriptor->stride * self->numberOfVertices;
  self->vertices = Arcadia_Memory_allocateUnmanaged(thread, numberOfBytes);
  //
  Arcadia_LeaveConstructor(Arcadia_Media_VertexBuffer);
}

static void
Arcadia_Media_VertexBuffer_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  )
{
  if (self->vertices) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertices);
    self->vertices = NULL;
  }
}

static void
Arcadia_Media_VertexBuffer_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBufferDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Media_VertexBuffer_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  )
{
  if (self->vertexDescriptor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexDescriptor);
  }
}

Arcadia_Media_VertexBuffer*
Arcadia_Media_VertexBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (vertexDescriptor) Arcadia_ValueStack_pushObjectReferenceValue(thread, vertexDescriptor); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushSizeValue(thread, numberOfVertices);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Media_VertexBuffer);
}

Arcadia_SizeValue
Arcadia_Media_VertexBuffer_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  )
{ return self->numberOfVertices; }

Arcadia_Media_VertexDescriptor*
Arcadia_Media_VertexBuffer_getVertexDescriptor
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexBuffer* self
  )
{ return self->vertexDescriptor; }
