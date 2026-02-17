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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.VertexBufferResource", Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource,
                         u8"Arcadia.Visuals.Implementation.VertexBufferResource", Arcadia_Visuals_Implementation_VertexBufferResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_getType(thread);
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

  self->vertexArrayID = 0;
  self->vertexBufferID = 0;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_EnterPassResource*)) & Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{
  assert(0 == self->vertexArrayID);
  assert(0 == self->vertexBufferID);
  assert(NULL == ((Arcadia_Visuals_Implementation_Resource*)self)->context);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  if (0 == self->vertexBufferID) {
    // (1) clear errors
    while (gl->glGetError()) {
    }
    // (2) create buffer
    gl->glGenBuffers(1, &self->vertexBufferID);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
  }

  if (((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->dirty & Arcadia_Visuals_Implementation_VertexBufferResource_VertexDataDirty) {
    // (1) bind the buffer
    gl->glBindBuffer(GL_ARRAY_BUFFER, self->vertexBufferID);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
    // (2) upload the data
    gl->glBufferData(GL_ARRAY_BUFFER, ((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->numberOfBytes,
                                      ((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->bytes, GL_STATIC_DRAW);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
    ((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->dirty &= ~Arcadia_Visuals_Implementation_VertexBufferResource_VertexDataDirty;
  }

  if (0 == self->vertexArrayID) {
    // (1) clear errors
    while (gl->glGetError()) {
    }
    // (2) create vertex array object
    gl->glGenVertexArrays(1, &self->vertexArrayID);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
  }
  if (((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->dirty & Arcadia_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty) {
    // (1) bind the buffer
    gl->glBindBuffer(GL_ARRAY_BUFFER, self->vertexBufferID);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
    // (2) bind the vertex array
    gl->glBindVertexArray(self->vertexArrayID);
    if (GL_NO_ERROR != gl->glGetError()) {
      return;
    }
    // The vertex pointers.
    Arcadia_SizeValue stride = ((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->vertexDescriptor->stride;
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->vertexDescriptor->vertexElementDescriptors); i < n; ++i) {
      Arcadia_Engine_Visuals_VertexElementDescriptor* vertexElementDescriptor = (Arcadia_Engine_Visuals_VertexElementDescriptor*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, (Arcadia_List*)((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->vertexDescriptor->vertexElementDescriptors, i, _Arcadia_Engine_Visuals_VertexElementDescriptor_getType(thread));
      GLint glType;
      GLsizei glSize;
      switch (vertexElementDescriptor->syntactics) {
        case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32: {
          glType = GL_FLOAT;
          glSize = 1;
        } break;
        case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32: {
          glType = GL_FLOAT;
          glSize = 2;
        } break;
        case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32: {
          glType = GL_FLOAT;
          glSize = 3;
        } break;
        case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32Real32: {
          glType = GL_FLOAT;
          glSize = 4;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
      gl->glEnableVertexAttribArray(i);
      gl->glVertexAttribPointer(i, glSize, glType, GL_FALSE, stride, ((const char*)0)+vertexElementDescriptor->offset);
      if (GL_NO_ERROR != gl->glGetError()) {
        return;
      }
    } 
    ((Arcadia_Visuals_Implementation_VertexBufferResource*)self)->dirty &= ~Arcadia_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{
  if (self->vertexArrayID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteVertexArrays(1, &self->vertexArrayID);
    self->vertexArrayID = 0;
  }
  if (self->vertexBufferID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteBuffers(1, &self->vertexBufferID);
    self->vertexBufferID = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self
  )
{
  assert(0 == self->vertexArrayID);
  assert(0 == self->vertexBufferID);
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self);
}

Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*
Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource);
}
