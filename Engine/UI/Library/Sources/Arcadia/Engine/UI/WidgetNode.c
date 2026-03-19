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

#define ARCADIA_ENGINE_UI_PRIVATE (1)
#include "Arcadia/Engine/UI/WidgetNode.h"

#include "Arcadia/Engine/UI/Events/WidgetPositionChangedEvent.h"
#include "Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.h"

static void
Arcadia_Engine_UI_WidgetNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self
  );

static void
Arcadia_Engine_UI_WidgetNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNodeDispatch* self
  );

static void
Arcadia_Engine_UI_WidgetNode_getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

static void
Arcadia_Engine_UI_WidgetNode_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
Arcadia_Engine_UI_WidgetNode_setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );

static void
Arcadia_Engine_UI_WidgetNode_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_UI_WidgetNode_raiseSignalImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Engine_UI_WidgetEvent* event
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_UI_WidgetNode_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.UI.WidgetNode", Arcadia_Engine_UI_WidgetNode,
                         u8"Arcadia.Engine.UI.Node", Arcadia_Engine_UI_Node,
                         &_typeOperations);

static void
Arcadia_Engine_UI_WidgetNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_UI_WidgetNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_UI_WidgetNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNodeDispatch* self
  )
{
  self->getPosition = &Arcadia_Engine_UI_WidgetNode_getPositionImpl;
  self->getSize = &Arcadia_Engine_UI_WidgetNode_getSizeImpl;
  self->setPosition = &Arcadia_Engine_UI_WidgetNode_setPositionImpl;
  self->setSize = &Arcadia_Engine_UI_WidgetNode_setSizeImpl;
  self->raiseSignal = &Arcadia_Engine_UI_WidgetNode_raiseSignalImpl;
}

static void
Arcadia_Engine_UI_WidgetNode_getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  *left = self->left;
  *top = self->top;
}

static void
Arcadia_Engine_UI_WidgetNode_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = self->width;
  *height = self->height;
}

static void
Arcadia_Engine_UI_WidgetNode_setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  if (left < Arcadia_Integer32Value_Minimum / 2 || left > Arcadia_Integer32Value_Maximum / 2) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (top < Arcadia_Integer32Value_Minimum / 2 || top > Arcadia_Integer32Value_Maximum / 2) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue changed = Arcadia_BooleanValue_False;
  changed |= self->left != left;
  changed |= self->top != top;
  self->left = left;
  self->top = top;
  if (changed) {
    Arcadia_Engine_UI_WidgetEvent* e = (Arcadia_Engine_UI_WidgetEvent*)Arcadia_Engine_UI_WidgetPositionChangedEvent_create(thread, Arcadia_getTickCount(thread), self, left, top);
    Arcadia_Engine_UI_WidgetNode_raiseSignal(thread, self, e);
  }
}

static void
Arcadia_Engine_UI_WidgetNode_setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  if (width < Arcadia_Integer32Value_Minimum / 2 || width > Arcadia_Integer32Value_Maximum / 2) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (height < Arcadia_Integer32Value_Minimum / 2 || height > Arcadia_Integer32Value_Maximum / 2) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue changed = Arcadia_BooleanValue_False;
  changed |= self->width != width;
  changed |= self->height != height;
  self->width = width;
  self->height = height;
  if (changed) {
    Arcadia_Engine_UI_WidgetEvent* e = (Arcadia_Engine_UI_WidgetEvent*)Arcadia_Engine_UI_WidgetSizeChangedEvent_create(thread, Arcadia_getTickCount(thread), self, width, height);
    Arcadia_Engine_UI_WidgetNode_raiseSignal(thread, self, e);
  }
}

static void
Arcadia_Engine_UI_WidgetNode_raiseSignalImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Engine_UI_WidgetEvent* event
  )
{/*@todo Add implementation.*/}

Arcadia_Engine_UI_WidgetNode*
Arcadia_Engine_UI_WidgetNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_UI_WidgetNode);
}

void
Arcadia_Engine_UI_WidgetNode_getPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value *left,
    Arcadia_Integer32Value *top
  )
{ Arcadia_VirtualCall(Arcadia_Engine_UI_WidgetNode, getPosition, self, left, top); }

void
Arcadia_Engine_UI_WidgetNode_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_VirtualCall(Arcadia_Engine_UI_WidgetNode, getSize, self, width, height); }

void
Arcadia_Engine_UI_WidgetNode_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{ Arcadia_VirtualCall(Arcadia_Engine_UI_WidgetNode, setPosition, self, left, top); }

void
Arcadia_Engine_UI_WidgetNode_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Engine_UI_WidgetNode, setSize, self, width, height); }

void
Arcadia_Engine_UI_WidgetNode_raiseSignal
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_WidgetNode* self,
    Arcadia_Engine_UI_WidgetEvent* event  
  )
{ Arcadia_VirtualCall(Arcadia_Engine_UI_WidgetNode, raiseSignal, self, event); }
