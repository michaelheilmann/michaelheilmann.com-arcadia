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

#include "Arcadia/Visuals/Scene/ViewportNode.h"

static void
Arcadia_Visuals_Scene_ViewportNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Scene_ViewportNode_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)NULL,
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
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->setCanvasSize = NULL;
  self->setClearColor = NULL;
  self->setRelativeViewportRectangle = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

void
Arcadia_Visuals_Scene_ViewportNode_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  )
{ self->setClearColor(thread, self, red, green, blue, alpha); }

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
{ self->setRelativeViewportRectangle(thread, self, left, bottom, right, top); }

void
Arcadia_Visuals_Scene_ViewportNode_setCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{ self->setCanvasSize(thread, self, width, height); }
