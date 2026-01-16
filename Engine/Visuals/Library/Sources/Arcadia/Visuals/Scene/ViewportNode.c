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
#include "Arcadia/Visuals/Scene/ViewportNode.h"

static void
Arcadia_Visuals_Scene_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self
  );

static void
Arcadia_Visuals_Scene_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNodeDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_ViewportNode_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.ViewportNode", Arcadia_Visuals_Scene_ViewportNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_ViewportNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value sceneNodeFactory = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &sceneNodeFactory);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_ViewportNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNodeDispatch* self
  )
{ }

void
Arcadia_Visuals_Scene_ViewportNode_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_ViewportNode, setClearColor, self, clearColor); }

void
Arcadia_Visuals_Scene_ViewportNode_setClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Real32Value depth
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_ViewportNode, setClearDepth, self, depth); }

void
Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_ViewportNode, setRelativeViewportRectangle, self, left, bottom, right, top); }

void
Arcadia_Visuals_Scene_ViewportNode_setCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_ViewportNode, setCanvasSize, self, width, height); }
