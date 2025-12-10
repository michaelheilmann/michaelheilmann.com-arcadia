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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/RenderingContextResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FrameBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_setTargetFrameBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* frameBuffer
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.RenderingContextResource", Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource,
                         u8"Arcadia.Visuals.Implementation.RenderingContextResource", Arcadia_Visuals_Implementation_RenderingContextResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_getType(thread);
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
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_RenderingContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_renderImpl;
  ((Arcadia_Visuals_Implementation_RenderingContextResourceDispatch*)self)->setTargetFrameBuffer = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Visuals_Implementation_FrameBufferResource*)) & Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_setTargetFrameBufferImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{
  static const Arcadia_Natural8Value matrixMask = Arcadia_Visuals_Implementation_RenderingContextResource_ViewToProjectionMatrixDirty
                                                | Arcadia_Visuals_Implementation_RenderingContextResource_WorldToViewMatrixDirty
                                                ;

  if (((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->dirty & matrixMask) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer, Arcadia_BooleanValue_True, ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewToProjectionMatrix);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer, Arcadia_BooleanValue_True, ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->worldToViewMatrix);
    ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->dirty &= ~matrixMask;
  }
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self
  )
{
  if (((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer);
    ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* renderingContextNode
  )
{
  static const Arcadia_Natural8Value matrixMask = Arcadia_Visuals_Implementation_RenderingContextResource_ViewToProjectionMatrixDirty
                                                | Arcadia_Visuals_Implementation_RenderingContextResource_WorldToViewMatrixDirty
                                                ;

  if (((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->dirty & matrixMask) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer, Arcadia_BooleanValue_True, ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewToProjectionMatrix);
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer, Arcadia_BooleanValue_True, ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->worldToViewMatrix);
    ((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->dirty &= ~matrixMask;
  }
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)((Arcadia_Visuals_Implementation_RenderingContextResource*)self)->viewerConstantBuffer);
}

Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource*
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource_setTargetFrameBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* frameBuffer
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (frameBuffer) {
    gl->glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->frameBufferID);
    gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBuffer->texture->id, 0);
    if (gl->glGetError()) {
      return;
    }
  } else {
    gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}
