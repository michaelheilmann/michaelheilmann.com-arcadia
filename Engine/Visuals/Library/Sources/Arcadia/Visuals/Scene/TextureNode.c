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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Scene/TextureNode.h"

#include "Arcadia/Visuals/SceneNodeFactory.h"

#define AddressModeUDirty (1)
#define AddressModeVDirty (2)
#define HeightDirty (4)
#define MagnificationFilterDirty (8)
#define MinificationFilterDirty (16)
#define WidthDirty (32)

static void
Arcadia_Visuals_Scene_TextureNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static void
Arcadia_Visuals_Scene_TextureNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_TextureNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_TextureNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_TextureNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

static Arcadia_Imaging_PixelBuffer*
makePixelBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferDefinition* source
  )
{
  Arcadia_Imaging_PixelBuffer* target = Arcadia_Imaging_PixelBuffer_create(thread, 0, source->width, source->height, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source->operations); i < n; ++i) {
    Arcadia_ADL_Reference* e = (Arcadia_ADL_Reference*)Arcadia_List_getObjectReferenceValueAt(thread, source->operations, i);
    Arcadia_Imaging_Operation* operation;
    if (!e->definition) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationFailed);
      Arcadia_Thread_jump(thread);
    }
    if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)e->definition, _Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_getType(thread))) {
      operation = (Arcadia_Imaging_Operation*)Arcadia_Imaging_Operations_CheckerboardFill_create(thread, (Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition*)e->definition);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)e->definition, _Arcadia_ADL_PixelBufferOperations_FillOperationDefinition_getType(thread))) {
      operation = (Arcadia_Imaging_Operation*)Arcadia_Imaging_Operations_Fill_create(thread, (Arcadia_ADL_PixelBufferOperations_FillOperationDefinition*)e->definition);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Imaging_Operation_apply(thread, operation, target);
  }

  return target;
}

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.TextureNode", Arcadia_Visuals_Scene_TextureNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_TextureNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_TextureNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value sceneNodeFactory = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &sceneNodeFactory);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->source = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_TextureDefinition_getType(thread));
  Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)self->source);
  //
  self->addressModeU = Arcadia_Visuals_TextureAddressMode_Repeat;
  self->addressModeV = Arcadia_Visuals_TextureAddressMode_Repeat;
  self->height = 240;
  self->magnificationFilter = Arcadia_Visuals_TextureFilter_Linear;
  self->minificationFilter = Arcadia_Visuals_TextureFilter_Linear;
  self->width = 320;
  //
  self->pixelBuffer = Arcadia_Visuals_SceneNodeFactory_createPixelBufferNode(thread, ((Arcadia_Visuals_Scene_Node*)self)->sceneNodeFactory, NULL,
                                                                             (Arcadia_ADL_PixelBufferDefinition*)self->source->pixelBuffer->definition);
  //
  self->dirtyBits = AddressModeUDirty | AddressModeVDirty | HeightDirty | MagnificationFilterDirty | MinificationFilterDirty | WidthDirty;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_TextureNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNodeDispatch* self
  )
{
  self->getAddressModeU = (Arcadia_Visuals_TextureAddressMode(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getAddressModeUImpl;
  self->getAddressModeV = (Arcadia_Visuals_TextureAddressMode(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getAddressModeVImpl;
  self->getHeight = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getHeightImpl;
  self->getMagnificationFilter = (Arcadia_Visuals_TextureFilter(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getMagnificationFilterImpl;
  self->getMinificationFilter = (Arcadia_Visuals_TextureFilter(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getMinificationFilterImpl;
  self->getWidth = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_Scene_TextureNode*)) & Arcadia_Visuals_Scene_TextureNode_getWidthImpl;
}

static void
Arcadia_Visuals_Scene_TextureNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{
  if (self->pixelBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->pixelBuffer);
  }
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
}

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeUImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->addressModeU; }

static Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeVImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->addressModeV; }

static Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getHeightImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->height; }

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMagnificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->magnificationFilter; }

static Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMinificationFilterImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->minificationFilter; }

static Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getWidthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ return self->width; }

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getAddressModeU, self); }

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Scene_TextureNode_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getAddressModeV, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getHeight, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getMagnificationFilter, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Scene_TextureNode_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getMinificationFilter, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Scene_TextureNode_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_TextureNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Scene_TextureNode, getWidth, self); }
