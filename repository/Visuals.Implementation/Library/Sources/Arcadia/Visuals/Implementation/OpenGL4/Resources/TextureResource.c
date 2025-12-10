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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include <assert.h>

#define AddressModeUDirty (1)
#define AddressModeVDirty (2)
#define HeightDirty (4)
#define MagnificationFilterDirty (8)
#define MinificationFilterDirty (16)
#define WidthDirty (32)

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  );

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureFilter magnificationFilter
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureFilter minificationFilter
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Integer32Value width
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_TextureResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_TextureResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_TextureResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.TextureResource", Arcadia_Visuals_Implementation_OpenGL4_TextureResource,
                         u8"Arcadia.Visuals.Implementation.TextureResource", Arcadia_Visuals_Implementation_TextureResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getType(thread);
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
  self->addressModeU = Arcadia_Visuals_TextureAddressMode_Repeat;
  self->addressModeV = Arcadia_Visuals_TextureAddressMode_Repeat;
  self->dirtyBits = AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty;
  self->height = 240;
  self->id = 0;
  self->magnificationFilter = Arcadia_Visuals_TextureFilter_Linear;
  self->minificationFilter = Arcadia_Visuals_TextureFilter_Linear;
  self->width = 320;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResourceDispatch* self
  )
{
  //
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getAddressModeU = (Arcadia_Visuals_TextureAddressMode(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeUImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getAddressModeV = (Arcadia_Visuals_TextureAddressMode(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeVImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getHeight = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getHeightImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getMagnificationFilter = (Arcadia_Visuals_TextureFilter(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMagnificationFilterImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getMinificationFilter = (Arcadia_Visuals_TextureFilter(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMinificationFilterImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->getWidth = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getWidthImpl;
  //
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setAddressModeU = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureAddressMode)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeUImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setAddressModeV = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureAddressMode)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeVImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setHeight = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Integer32Value)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setHeightImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setMagnificationFilter = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureFilter)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMagnificationFilterImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setMinificationFilter = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureFilter)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMinificationFilterImpl;
  ((Arcadia_Visuals_Implementation_TextureResourceDispatch*)self)->setWidth = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Integer32Value)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setWidthImpl;
  //
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_RenderingContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_TextureResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{
  assert(0 == self->id);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (!self->id) {
    gl->glGenTextures(1, &self->id);
    if (gl->glGetError()) {
      return;
    }
  }

  if (self->dirtyBits & (AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty)) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      gl->glBindTexture(GL_TEXTURE_2D, self->id);
      if (gl->glGetError()) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      if (self->dirtyBits & AddressModeUDirty) {
        GLint addressMode;
        switch (self->addressModeU) {
          case Arcadia_Visuals_TextureAddressMode_ClampToBorder: {
            addressMode = GL_CLAMP_TO_BORDER;
          } break;
          case Arcadia_Visuals_TextureAddressMode_ClampToEdge: {
            addressMode = GL_CLAMP_TO_EDGE;
          } break;
          case Arcadia_Visuals_TextureAddressMode_MirroredRepeat: {
            addressMode = GL_MIRRORED_REPEAT;
          } break;
          case Arcadia_Visuals_TextureAddressMode_Repeat: {
            addressMode = GL_REPEAT;
          } break;
          default: {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
            Arcadia_Thread_jump(thread);
          } break;
        };
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, addressMode);
        if (gl->glGetError()) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        self->dirtyBits &= ~AddressModeUDirty;
      }
      if (self->dirtyBits & AddressModeVDirty) {
        GLint addressMode;
        switch (self->addressModeV) {
          case Arcadia_Visuals_TextureAddressMode_ClampToBorder: {
            addressMode = GL_CLAMP_TO_BORDER;
          } break;
          case Arcadia_Visuals_TextureAddressMode_ClampToEdge: {
            addressMode = GL_CLAMP_TO_EDGE;
          } break;
          case Arcadia_Visuals_TextureAddressMode_MirroredRepeat: {
            addressMode = GL_MIRRORED_REPEAT;
          } break;
          case Arcadia_Visuals_TextureAddressMode_Repeat: {
            addressMode = GL_REPEAT;
          } break;
          default: {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
            Arcadia_Thread_jump(thread);
          } break;
        };
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, addressMode);
        if (gl->glGetError()) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        self->dirtyBits &= ~AddressModeVDirty;
      }
      if (self->dirtyBits & MagnificationFilterDirty) {
        GLint magnificationFilter;
        switch (self->magnificationFilter) {
          case Arcadia_Visuals_TextureFilter_Linear: {
            magnificationFilter = GL_LINEAR;
          } break;
          case Arcadia_Visuals_TextureFilter_Nearest: {
            magnificationFilter = GL_NEAREST;
          } break;
          default: {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
            Arcadia_Thread_jump(thread);
          } break;
        }
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnificationFilter);
        if (gl->glGetError()) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        self->dirtyBits &= ~MagnificationFilterDirty;
      }
      if (self->dirtyBits & MinificationFilterDirty) {
        GLint minificationFilter;
        switch (self->minificationFilter) {
          case Arcadia_Visuals_TextureFilter_Linear: {
            minificationFilter = GL_LINEAR;
          } break;
          case Arcadia_Visuals_TextureFilter_Nearest: {
            minificationFilter = GL_NEAREST;
          } break;
          default: {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
            Arcadia_Thread_jump(thread);
          } break;
        }
        gl->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minificationFilter);
        if (gl->glGetError()) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        self->dirtyBits &= ~MinificationFilterDirty;
      }
      if (self->dirtyBits & (HeightDirty | WidthDirty)) {
        gl->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, self->width, self->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        if (gl->glGetError()) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        }
        self->dirtyBits &= ~(HeightDirty | WidthDirty);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      gl->glDeleteTextures(1, &self->id);
      self->id = 0;
      self->dirtyBits = AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty;
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (self->id) {
    gl->glDeleteTextures(1, &self->id);
    self->id = 0;
    self->dirtyBits = AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ }

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  )
{ }

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->addressModeU; }

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->addressModeV; }

static Arcadia_Integer32Value
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->height; }

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->magnificationFilter; }

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->minificationFilter; }

static Arcadia_Integer32Value
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self
  )
{ return self->width; }

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressModeU
  )
{
  if (self->addressModeU != addressModeU) {
    self->addressModeU = addressModeU;
    self->dirtyBits |= AddressModeUDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressModeV
  )
{
  if (self->addressModeV != addressModeV) {
    self->addressModeV = addressModeV;
    self->dirtyBits |= AddressModeVDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Integer32Value height
  )
{
  if (self->height != height) {
    self->height = height;
    self->dirtyBits |= HeightDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureFilter magnificationFilter
  )
{
  if (self->magnificationFilter != magnificationFilter) {
    self->magnificationFilter = magnificationFilter;
    self->dirtyBits |= MagnificationFilterDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Visuals_TextureFilter minificationFilter
  )
{
  if (self->minificationFilter != minificationFilter) {
    self->minificationFilter = minificationFilter;
    self->dirtyBits|= MinificationFilterDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_setWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* self,
    Arcadia_Integer32Value width
  )
{
  if (self->width != width) {
    self->width = width;
    self->dirtyBits |= WidthDirty;
  }
}

Arcadia_Visuals_Implementation_OpenGL4_TextureResource*
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_TextureResource);
}
