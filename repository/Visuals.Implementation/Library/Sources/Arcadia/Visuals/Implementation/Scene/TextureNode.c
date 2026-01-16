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
#include "Arcadia/Visuals/Implementation/Scene/TextureNode.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Scene/RenderingContextNode.h"
#include "Arcadia/Visuals/Implementation/Resource.h"

#define AddressModeUDirty (1)
#define AddressModeVDirty (2)
#define HeightDirty (4)
#define MagnificationFilterDirty (8)
#define MinificationFilterDirty (16)
#define WidthDirty (32)

#define DirtyBitsAll (AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty)

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNodeDispatch* self
  );

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self
  );

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_TextureNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_Scene_TextureNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Scene.TextureNode", Arcadia_Visuals_Implementation_Scene_TextureNode,
                         u8"Arcadia.Visuals.Scene.TextureNode", Arcadia_Visuals_Scene_TextureNode,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Scene_TextureNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value sceneNodeFactory = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_Value source = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &sceneNodeFactory);
    Arcadia_ValueStack_pushValue(thread, &source);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 3)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  self->textureResource = NULL;
  self->dirtyBits = DirtyBitsAll;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNodeDispatch* self
  )
{
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_Scene_RenderingContextNode*)) & Arcadia_Visuals_Implementation_Scene_TextureNode_renderImpl;
  ((Arcadia_Visuals_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*)) & Arcadia_Visuals_Implementation_Scene_TextureNode_setBackendContextImpl;
}

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self
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
Arcadia_Visuals_Implementation_Scene_TextureNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self,
    Arcadia_Visuals_Implementation_Scene_RenderingContextNode* renderingContextNode
  )
{
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)((Arcadia_Visuals_Scene_TextureNode*)self)->pixelBuffer, (Arcadia_Visuals_Scene_RenderingContextNode*)renderingContextNode);
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)self, (Arcadia_Visuals_BackendContext*)renderingContextNode->backendContext);
}

static void
Arcadia_Visuals_Implementation_Scene_TextureNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Scene_TextureNode* self,
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
      Arcadia_Visuals_Implementation_TextureResource_setAddressModeU(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getAddressModeU(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~AddressModeUDirty;
    }
    if (AddressModeVDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setAddressModeV(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getAddressModeU(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~AddressModeVDirty;
    }
    if (HeightDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setHeight(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getHeight(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~HeightDirty;
    }
    if (MagnificationFilterDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setMagnificationFilter(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getMagnificationFilter(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~MagnificationFilterDirty;
    }
    if (MinificationFilterDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setMinificationFilter(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getMinificationFilter(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~MinificationFilterDirty;
    }
    if (WidthDirty & self->dirtyBits) {
      Arcadia_Visuals_Implementation_TextureResource_setWidth(thread, self->textureResource, Arcadia_Visuals_Scene_TextureNode_getWidth(thread, (Arcadia_Visuals_Scene_TextureNode*)self));
      self->dirtyBits &= ~WidthDirty;
    }
    Arcadia_Visuals_Scene_PixelBufferNode* pixelBuffer = ((Arcadia_Visuals_Scene_TextureNode*)self)->pixelBuffer;
    Arcadia_Visuals_Implementation_TextureResource_setPixelBuffer(thread, self->textureResource, pixelBuffer->pixelBuffer);
  }
}

Arcadia_Visuals_Implementation_Scene_TextureNode*
Arcadia_Visuals_Implementation_Scene_TextureNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_SceneNodeFactory* sceneNodeFactory,
    Arcadia_ADL_TextureDefinition* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (sceneNodeFactory) Arcadia_ValueStack_pushObjectReferenceValue(thread, sceneNodeFactory); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (source) Arcadia_ValueStack_pushObjectReferenceValue(thread, source); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_Scene_TextureNode);
}
