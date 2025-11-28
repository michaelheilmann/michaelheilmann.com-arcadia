// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/Utilities.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_writeMatrix4x4Real32Impl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    Arcadia_BooleanValue transpose,
    Arcadia_Math_Matrix4Real32 const* source
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ConstantBufferResource", Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource,
                         u8"Arcadia.Visuals.Implementation.ConstantBufferResource", Arcadia_Visuals_Implementation_ConstantBufferResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_getType(thread);
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
  self->dirty = Arcadia_BooleanValue_True;
  self->byteBuffer = Arcadia_ByteBuffer_create(thread);
  self->bufferID = 0;

  ((Arcadia_Visuals_Implementation_Resource*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_loadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_MeshContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_renderImpl;
  ((Arcadia_Visuals_Implementation_ConstantBufferResource*)self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_clearImpl;
  ((Arcadia_Visuals_Implementation_ConstantBufferResource*)self)->writeMatrix4x4Real32 = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*, Arcadia_BooleanValue, Arcadia_Math_Matrix4Real32 const*)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_writeMatrix4x4Real32Impl;
  ((Arcadia_Visuals_Implementation_ConstantBufferResource*)self)->setData = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*, const void*, Arcadia_SizeValue)) & Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_setDataImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  assert(0 == self->bufferID);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  if (self->byteBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->byteBuffer);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  if (0 == self->bufferID) {
    gl->glGenBuffers(1, &self->bufferID);
  }
  if (self->dirty) {
    gl->glBindBuffer(GL_UNIFORM_BUFFER, self->bufferID);
    gl->glBufferData(GL_UNIFORM_BUFFER, Arcadia_ByteBuffer_getNumberOfBytes(thread, self->byteBuffer), Arcadia_ByteBuffer_getBytes(thread, self->byteBuffer), GL_STATIC_DRAW);
    if (gl->glGetError()) {
      return;
    }
    self->dirty = Arcadia_BooleanValue_False;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  if (self->bufferID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteBuffers(1, &self->bufferID);
    self->bufferID = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{
  assert(0 == self->bufferID);
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  if (0 == self->bufferID) {
    gl->glGenBuffers(1, &self->bufferID);
  }
  if (self->dirty) {
    gl->glBindBuffer(GL_UNIFORM_BUFFER, self->bufferID);
    gl->glBufferData(GL_UNIFORM_BUFFER, Arcadia_ByteBuffer_getNumberOfBytes(thread, self->byteBuffer), Arcadia_ByteBuffer_getBytes(thread, self->byteBuffer), GL_STATIC_DRAW);
    if (gl->glGetError()) {
      return;
    }
    self->dirty = Arcadia_BooleanValue_False;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_setDataImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_ByteBuffer_clear(thread, self->byteBuffer);
  Arcadia_ByteBuffer_insertBackBytes(thread, self->byteBuffer, bytes, numberOfBytes);
  self->dirty = Arcadia_BooleanValue_True;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self
  )
{ Arcadia_ByteBuffer_clear(thread, self->byteBuffer); self->dirty = Arcadia_BooleanValue_True; }

static inline void
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_writeMatrix4x4Real32Impl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* self,
    Arcadia_BooleanValue transpose,
    Arcadia_Math_Matrix4Real32 const* source
  )
{
  if (transpose) {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        Arcadia_ByteBuffer_insertBackBytes(thread, self->byteBuffer, &(source->elements[j][i]), sizeof(float));
      }
    }
  } else {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        Arcadia_ByteBuffer_insertBackBytes(thread, self->byteBuffer, &(source->elements[i][j]), sizeof(float));
      }
    }
  }
  self->dirty = Arcadia_BooleanValue_True;
}

Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*
Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource);
}
