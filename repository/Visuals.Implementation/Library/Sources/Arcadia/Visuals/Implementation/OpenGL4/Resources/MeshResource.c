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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/Utilities.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

#define Arcadia_Visuals_Implementation_OpenGL4_MeshResources_LocalToWorldMatrixDirty (1)
#define Arcadia_Visuals_Implementation_OpenGL4_MeshResources_VerticesDirty (2)
#define Arcadia_Visuals_Implementation_OpenGL4_MeshResources_ViewToProjectionMatrixDirty (4)
#define Arcadia_Visuals_Implementation_OpenGL4_MeshResources_WorldToViewMatrixDirty (8)

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.MeshResource", Arcadia_Visuals_Implementation_OpenGL4_MeshResource,
                         u8"Arcadia.Visuals.Implementation.MeshResource", Arcadia_Visuals_Implementation_MeshResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_MeshResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
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
  
  self->constantBuffer = NULL;
  self->dirty = Arcadia_Visuals_Implementation_OpenGL4_MeshResources_LocalToWorldMatrixDirty
              | Arcadia_Visuals_Implementation_OpenGL4_MeshResources_VerticesDirty
              | Arcadia_Visuals_Implementation_OpenGL4_MeshResources_ViewToProjectionMatrixDirty
              | Arcadia_Visuals_Implementation_OpenGL4_MeshResources_WorldToViewMatrixDirty
              ;
  self->localToWorldMatrix = NULL;
  self->program = NULL;
  self->vertexBuffer = NULL;

  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext =
    Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getType(thread));

  self->localToWorldMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->localToWorldMatrix);

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  self->constantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
  self->program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_getType(thread));
  self->vertexBuffer = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_getType(thread));

  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);

  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl;
  ((Arcadia_Visuals_Implementation_MeshResource*)self)->setLocalToWorldMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl;
  ((Arcadia_Visuals_Implementation_MeshResource*)self)->setViewToProjectionMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setViewToProjectionMatrixImpl;
  ((Arcadia_Visuals_Implementation_MeshResource*)self)->setWorldToViewMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setWorldToViewMatrixImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  assert(NULL == self->constantBuffer);
  assert(NULL == self->vertexBuffer);
  assert(NULL == self->program);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  if (self->localToWorldMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->localToWorldMatrix);
  }
  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  if (self->constantBuffer) {
    ((Arcadia_Visuals_Implementation_Resource*)self->constantBuffer)->referenceCount--;
    self->constantBuffer = NULL;
  }
  if (self->vertexBuffer) {
    ((Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer)->referenceCount--;
    self->vertexBuffer = NULL;
  }
  if (self->program) {
    ((Arcadia_Visuals_Implementation_Resource*)self->program)->referenceCount--;
    self->program = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);
  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);

  static const Arcadia_Natural8Value matrixMask = Arcadia_Visuals_Implementation_OpenGL4_MeshResources_LocalToWorldMatrixDirty
                                                | Arcadia_Visuals_Implementation_OpenGL4_MeshResources_ViewToProjectionMatrixDirty
                                                | Arcadia_Visuals_Implementation_OpenGL4_MeshResources_WorldToViewMatrixDirty
                                                ;

  if (self->dirty & matrixMask) {
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);

    writeMatrix4x4Real32ToBuffer(thread, Arcadia_BooleanValue_True, self->viewToProjectionMatrix, byteBuffer);
    writeMatrix4x4Real32ToBuffer(thread, Arcadia_BooleanValue_True, self->worldToViewMatrix, byteBuffer);
    writeMatrix4x4Real32ToBuffer(thread, Arcadia_BooleanValue_True, self->localToWorldMatrix, byteBuffer);

    Arcadia_Visuals_Implementation_ConstantBufferResource_setData
      (
        thread,
        (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->constantBuffer,
        Arcadia_ByteBuffer_getBytes(thread, byteBuffer),
        Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer)
      );

    self->dirty &= ~matrixMask;
  }
  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
  gl->glUseProgram(self->program->id);
  gl->glBindFragDataLocation(self->program->id, 0, u8"fragmentColor");
  gl->glBindVertexArray(self->vertexBuffer->vertexArrayID);

  GLuint blockIndex;
  while (gl->glGetError()) { }
  blockIndex = gl->glGetUniformBlockIndex(self->program->id, "matrices");
  if (GL_INVALID_INDEX == blockIndex) {
    return;
  }
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 0, self->constantBuffer->bufferID);
  gl->glUniformBlockBinding(self->program->id, blockIndex, 0);
  if (gl->glGetError()) {
    return;
  }
  gl->glDrawArrays(GL_TRIANGLES, 0, Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVertices(thread, (Arcadia_Visuals_Implementation_VertexBufferResource*)self->vertexBuffer));
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  )
{
  self->localToWorldMatrix = localToWorldMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_OpenGL4_MeshResources_LocalToWorldMatrixDirty;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setViewToProjectionMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  )
{
  self->viewToProjectionMatrix = viewToProjectionMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_OpenGL4_MeshResources_ViewToProjectionMatrixDirty;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setWorldToViewMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  )
{
  self->worldToViewMatrix = worldToViewMatrix;
  self->dirty |= Arcadia_Visuals_Implementation_OpenGL4_MeshResources_WorldToViewMatrixDirty;
}

Arcadia_Visuals_Implementation_OpenGL4_MeshResource*
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBuffer,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* program
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (program) Arcadia_ValueStack_pushObjectReferenceValue(thread, program); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (vertexBuffer) Arcadia_ValueStack_pushObjectReferenceValue(thread, vertexBuffer); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_MeshResource);
}
