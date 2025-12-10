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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/Texture.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Resource.h"

#define AddressModeUDirty (1)
#define AddressModeVDirty (2)
#define HeightDirty (4)
#define MagnificationFilterDirty (8)
#define MinificationFilterDirty (16)
#define WidthDirty (32)

#define DirtyBitsAll (AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty)

static void
Arcadia_Visuals_Implementation_Texture_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self
  );

static void
Arcadia_Visuals_Implementation_Texture_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Texture_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self
  );

static void
Arcadia_Visuals_Implementation_Texture_uploadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Texture_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Texture_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Texture", Arcadia_Visuals_Implementation_Texture,
                         u8"Arcadia.Visuals.Texture", Arcadia_Visuals_Texture,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Texture_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Texture_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  self->textureResource = NULL;
  self->dirtyBits = DirtyBitsAll;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Texture_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureDispatch* self
  )
{ }

static void
Arcadia_Visuals_Implementation_Texture_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self
  )
{
  if (self->backendContext) {
    if (self->textureResource) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->textureResource);
      self->textureResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
    self->dirtyBits = DirtyBitsAll;
  }
}

static void
Arcadia_Visuals_Implementation_Texture_uploadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Texture* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_BooleanValue backendContextChanged = backendContext != self->backendContext;
  if (backendContextChanged) {
    if (backendContext) {
      Arcadia_Object_lock(thread, (Arcadia_Object*)backendContext);
    }
    if (self->backendContext) {
      if (self->textureResource) {
        Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->textureResource);
        self->textureResource = NULL;
      }
      Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    }
    self->backendContext = backendContext;
    self->dirtyBits = DirtyBitsAll;
  }
  if (!self->textureResource && self->backendContext) {
    self->textureResource = Arcadia_Visuals_Implementation_BackendContext_createTextureResource(thread, self->backendContext);
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)self->textureResource);
  }
  if ((DirtyBitsAll & self->dirtyBits) && self->textureResource) {
    if (AddressModeUDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setAddressModeU(thread, self->textureResource, Arcadia_Visuals_Texture_getAddressModeU(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~AddressModeUDirty;
    }
    if (AddressModeVDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setAddressModeV(thread, self->textureResource, Arcadia_Visuals_Texture_getAddressModeU(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~AddressModeVDirty;
    }
    if (HeightDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setHeight(thread, self->textureResource, Arcadia_Visuals_Texture_getHeight(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~HeightDirty;
    }
    if (MagnificationFilterDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setMagnificationFilter(thread, self->textureResource, Arcadia_Visuals_Texture_getMagnificationFilter(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~MagnificationFilterDirty;
    }
    if (MinificationFilterDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setMinificationFilter(thread, self->textureResource, Arcadia_Visuals_Texture_getMinificationFilter(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~MinificationFilterDirty;
    }
    if (WidthDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setWidth(thread, self->textureResource, Arcadia_Visuals_Texture_getWidth(thread, (Arcadia_Visuals_Texture*)self));
      self->dirtyBits &= ~WidthDirty;
    }
  }
}

Arcadia_Visuals_Implementation_Texture*
Arcadia_Visuals_Implementation_Texture_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Texture);
}
