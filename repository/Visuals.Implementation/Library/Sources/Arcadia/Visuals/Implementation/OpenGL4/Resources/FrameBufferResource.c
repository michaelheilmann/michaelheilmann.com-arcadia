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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FrameBufferResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResourceDispatch* self 
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_activateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_deactivateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.FrameBufferResource", Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource,
                         u8"Arcadia.Visuals.Implementation.FrameBufferResource", Arcadia_Visuals_Implementation_FrameBufferResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_getType(thread);
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

  self->texture = NULL;
  self->dirty = Arcadia_BooleanValue_True;
  self->width = 320;
  self->height = 240;
  self->frameBufferID = 0;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_FrameBufferResourceDispatch*)self)->activate = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_activateImpl;
  ((Arcadia_Visuals_Implementation_FrameBufferResourceDispatch*)self)->deactivate = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_deactivateImpl;
  ((Arcadia_Visuals_Implementation_FrameBufferResourceDispatch*)self)->setSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_setSizeImpl;
  ((Arcadia_Visuals_Implementation_FrameBufferResourceDispatch*)self)->getSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_setSizeImpl;


  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_RenderingContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  assert(NULL == self->texture);
  assert(0 == self->frameBufferID);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (!self->texture) {
    self->texture = (Arcadia_Visuals_Implementation_OpenGL4_TextureResource*)Arcadia_Visuals_Implementation_BackendContext_createTextureResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)context);
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->texture);
  }
  if (self->dirty) {
    Arcadia_Visuals_Implementation_TextureResource_setWidth(thread, (Arcadia_Visuals_Implementation_TextureResource*)self->texture, self->width);
    Arcadia_Visuals_Implementation_TextureResource_setHeight(thread, (Arcadia_Visuals_Implementation_TextureResource*)self->texture, self->height);
    self->dirty = Arcadia_BooleanValue_False;
  }
  if (!self->frameBufferID) {
    gl->glGenFramebuffers(1, &self->frameBufferID);
    if (gl->glGetError()) {
      return;
    }
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (self->frameBufferID) {
    gl->glDeleteFramebuffers(1, &self->frameBufferID);
    self->frameBufferID = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  if (self->texture) {
    ((Arcadia_Visuals_Implementation_Resource*)self->texture)->referenceCount--;
    self->texture = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_activateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_loadImpl(thread, self);
  gl->glBindFramebuffer(GL_FRAMEBUFFER, self->frameBufferID);
  gl->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self->texture->id, 0);
  if (gl->glGetError()) {
    return;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_deactivateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (self->frameBufferID) {
    gl->glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  if (self->width != width || self->height != height) {
    self->width = width;
    self->height = height;
    self->dirty = Arcadia_BooleanValue_True;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = self->width;
  *height = self->height;
}

Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource*
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource);
}
