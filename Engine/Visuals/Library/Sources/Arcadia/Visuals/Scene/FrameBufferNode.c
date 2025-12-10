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
#include "Arcadia/Visuals/Scene/FrameBufferNode.h"

static void
Arcadia_Visuals_Scene_FrameBufferNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self
  );

static void
Arcadia_Visuals_Scene_FrameBufferNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_FrameBufferNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_FrameBufferNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_FrameBufferNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.FrameBufferNode", Arcadia_Visuals_Scene_FrameBufferNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_FrameBufferNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_FrameBufferNode_getType(thread);
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
Arcadia_Visuals_Scene_FrameBufferNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_Scene_FrameBufferNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Visuals_Scene_FrameBufferNode_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_FrameBufferNode, getSize, self, width, height); }

void
Arcadia_Visuals_Scene_FrameBufferNode_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Scene_FrameBufferNode, setSize, self, width, height); }
