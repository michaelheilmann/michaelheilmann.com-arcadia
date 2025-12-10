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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

#define Arcadia_Visuals_Implementation_OpenGL4_MeshResource_LocalToWorldMatrixDirty (1)
#define Arcadia_Visuals_Implementation_OpenGL4_MeshResource_MeshAmbientColorDirty (2)
#define Arcadia_Visuals_Implementation_OpenGL4_MeshResource_VerticesDirty (4)

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResourceDispatch* self
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
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl
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
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setMeshAmbientColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Color4Real32* meshAmbientColor
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl,
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

  self->meshConstantBuffer = NULL;

  self->dirty = Arcadia_Visuals_Implementation_OpenGL4_MeshResource_LocalToWorldMatrixDirty
              | Arcadia_Visuals_Implementation_OpenGL4_MeshResource_MeshAmbientColorDirty
              | Arcadia_Visuals_Implementation_OpenGL4_MeshResource_VerticesDirty
              ;

  self->localToWorldMatrix = NULL;

  self->program = NULL;
  self->vertexBuffer = NULL;

  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext =
    Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getType(thread));

  self->meshAmbientColor = Arcadia_Math_Color4Real32_create(thread);
  self->localToWorldMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->localToWorldMatrix);

  self->meshConstantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
  self->program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_getType(thread));
  self->vertexBuffer = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_getType(thread));

  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshConstantBuffer);
  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
  Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}


static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_MeshResourceDispatch*)self)->setLocalToWorldMatrix = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl;

  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_RenderingContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  assert(NULL == self->meshConstantBuffer);
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
  if (self->meshAmbientColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshAmbientColor);
  }
  if (self->localToWorldMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->localToWorldMatrix);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{/*Intentionally empty.*/}

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
  if (self->meshConstantBuffer) {
    ((Arcadia_Visuals_Implementation_Resource*)self->meshConstantBuffer)->referenceCount--;
    self->meshConstantBuffer = NULL;
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
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);

  if (self->dirty & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_MeshAmbientColorDirty) {
    self->dirty &= ~Arcadia_Visuals_Implementation_OpenGL4_MeshResource_MeshAmbientColorDirty;
  }
  if (self->dirty & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_LocalToWorldMatrixDirty) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->meshConstantBuffer);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->meshConstantBuffer, Arcadia_BooleanValue_True, self->localToWorldMatrix);
    self->dirty &= ~Arcadia_Visuals_Implementation_OpenGL4_MeshResource_LocalToWorldMatrixDirty;
  }

  Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* viewerConstantBuffer = NULL;
  viewerConstantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)renderingContextNode->viewerConstantBuffer;
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->meshConstantBuffer);
  gl->glUseProgram(self->program->id);
  gl->glBindFragDataLocation(self->program->id, 0, u8"fragmentColor");
  gl->glBindVertexArray(self->vertexBuffer->vertexArrayID);

  GLuint blockIndex;
  //
  while (gl->glGetError()) { }
  blockIndex = gl->glGetUniformBlockIndex(self->program->id, "viewer");
  if (GL_INVALID_INDEX == blockIndex) {
    return;
  }
  gl->glUniformBlockBinding(self->program->id, blockIndex, 0);
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 0, viewerConstantBuffer->bufferID);
  if (gl->glGetError()) {
    return;
  }
  //
  while (gl->glGetError()) { }
  blockIndex = gl->glGetUniformBlockIndex(self->program->id, "mesh");
  if (GL_INVALID_INDEX == blockIndex) {
    return;
  }
  gl->glUniformBlockBinding(self->program->id, blockIndex, 1);
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 1, self->meshConstantBuffer->bufferID);
  if (gl->glGetError()) {
    return;
  }
  gl->glDrawArrays(GL_TRIANGLES, 0, Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVertices(thread, (Arcadia_Visuals_Implementation_VertexBufferResource*)self->vertexBuffer));
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setMeshAmbientColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Color4Real32* meshAmbientColor
  )
{
#if 0
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(meshAmbientColor);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->meshAmbientColor, &t))
#endif
  {
    Arcadia_Math_Color4Real32_assign(thread, self->meshAmbientColor, meshAmbientColor);
    self->dirty |= Arcadia_Visuals_Implementation_OpenGL4_MeshResource_MeshAmbientColorDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setLocalToWorldMatrixImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  )
{
#if 0
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(localToWorldMatrix);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->localToWorldMatrix, &t))
#endif
  {
    Arcadia_Math_Matrix4Real32_assign(thread, self->localToWorldMatrix, localToWorldMatrix);
    self->dirty |= Arcadia_Visuals_Implementation_OpenGL4_MeshResource_LocalToWorldMatrixDirty;
  }
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
