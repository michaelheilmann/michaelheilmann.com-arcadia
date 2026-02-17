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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ModelResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MaterialResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ModelResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ModelResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ModelResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ModelResource", Arcadia_Visuals_Implementation_OpenGL4_ModelResource,
                         u8"Arcadia.Visuals.Implementation.ModelResource", Arcadia_Visuals_Implementation_ModelResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_ModelResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 3);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->constantBuffer = NULL;
  self->mesh = NULL;
  self->material = NULL;

  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext =
    Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getType(thread));


  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Object* o;

    o = (Arcadia_Object*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->constantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)o;

    o = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_MeshResource_getType(thread));
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->mesh = (Arcadia_Visuals_Implementation_OpenGL4_MeshResource*)o;

    o = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_getType(thread));
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->material = (Arcadia_Visuals_Implementation_OpenGL4_MaterialResource*)o; 

   Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->material) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->material);
      self->material = NULL;
    }
    if (self->mesh) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->mesh);
      self->mesh = NULL;
    }
    if (self->constantBuffer) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
      self->constantBuffer = NULL;
    }
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}


static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ModelResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_EnterPassResource*)) & Arcadia_Visuals_Implementation_OpenGL4_ModelResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{
  assert(NULL == self->constantBuffer);
  assert(NULL == self->mesh);
  assert(NULL == self->material);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->mesh);
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->material);
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->material);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self
  )
{
  if (self->constantBuffer) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
    self->constantBuffer = NULL;
  }
  if (self->mesh) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->mesh);
    self->mesh = NULL;
  }
  if (self->material) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->material);
    self->material = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ModelResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextResource
  )
{
  // Invoke our load function.
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self);

  if (((Arcadia_Visuals_Implementation_ModelResource*)self)->dirty & (Arcadia_Visuals_Implementation_ModelResource_LocalToWorldMatrixDirty)) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->constantBuffer);
    // @todo We need to ability to do sub-range updates:
    // There is no need to rewrite every value if only one value is dirty.
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->constantBuffer, Arcadia_BooleanValue_True, ((Arcadia_Visuals_Implementation_ModelResource*)self)->localToWorldMatrix);
    ((Arcadia_Visuals_Implementation_ModelResource*)self)->dirty &= ~Arcadia_Visuals_Implementation_ModelResource_LocalToWorldMatrixDirty;
    
    Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
  }


  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->material, renderingContextResource);
  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->mesh, renderingContextResource);

  Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* viewerConstantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)renderingContextResource->viewerConstantBuffer;
  //
  gl->glUseProgram(self->material->program->programID);
  gl->glBindFragDataLocation(self->material->program->programID, 0, u8"_2_fragmentColor");
  gl->glBindVertexArray(self->mesh->vertexBuffer->vertexArrayID);

  //
  if (self->material->ambientColorSource == Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource_Texture) {
    while (gl->glGetError()) { }
    assert(0 != self->material->ambientColorTexture->id);
    gl->glBindTexture(GL_TEXTURE_2D, self->material->ambientColorTexture->id);
    if (gl->glGetError()) {
      return;
    }
  }
  GLuint uniformBlockIndex;
  // Bind the "viewer" constant block.
  // @todo "viewer" is the GLSL block name. This name should be querified from the program object using the VPL names.
  while (gl->glGetError()) { }
  uniformBlockIndex = gl->glGetUniformBlockIndex(self->material->program->programID, "viewer");
  if (GL_INVALID_INDEX == uniformBlockIndex) {
    return;
  }
  gl->glUniformBlockBinding(self->material->program->programID, uniformBlockIndex, 0);
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 0, viewerConstantBuffer->bufferID);
  if (gl->glGetError()) {
    return;
  }
  // Bind the "mesh" constant block.
  // @todo "mesh" is the GLSL block name. This name should be querified from the program object using the VPL names.
  while (gl->glGetError()) { }
  uniformBlockIndex = gl->glGetUniformBlockIndex(self->material->program->programID, "mesh");
  if (GL_INVALID_INDEX == uniformBlockIndex) {
    return;
  }
  gl->glUniformBlockBinding(self->material->program->programID, uniformBlockIndex, 1);
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 1, self->mesh->constantBuffer->bufferID);
  if (gl->glGetError()) {
    return;
  }
  // Bind the "model" constant block.
  // @todo "model" is the GLSL block name. This name should be querified from the program object using the VPL names.
  while (gl->glGetError()) { }
  uniformBlockIndex = gl->glGetUniformBlockIndex(self->material->program->programID, "model");
  if (GL_INVALID_INDEX == uniformBlockIndex) {
    return;
  }
  gl->glUniformBlockBinding(self->material->program->programID, uniformBlockIndex, 2);
  gl->glBindBufferBase(GL_UNIFORM_BUFFER, 2, self->constantBuffer->bufferID);
  if (gl->glGetError()) {
    return;
  }
  //
  gl->glDrawArrays(GL_TRIANGLES, 0, Arcadia_Visuals_Implementation_VertexBufferResource_getNumberOfVertices(thread, (Arcadia_Visuals_Implementation_VertexBufferResource*)self->mesh->vertexBuffer));
}

Arcadia_Visuals_Implementation_OpenGL4_ModelResource*
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* mesh,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* material
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (mesh) Arcadia_ValueStack_pushObjectReferenceValue(thread, mesh); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (material) Arcadia_ValueStack_pushObjectReferenceValue(thread, material); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_ModelResource);
}
