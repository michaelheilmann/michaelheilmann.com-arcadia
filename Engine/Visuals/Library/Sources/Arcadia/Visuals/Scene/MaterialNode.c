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
#include "Arcadia/Visuals/Scene/MaterialNode.h"

#include "Arcadia/Visuals/Include.h"

static void
Arcadia_Visuals_Scene_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static void
Arcadia_Visuals_Scene_MaterialNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_MaterialNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.MaterialNode", Arcadia_Visuals_Scene_MaterialNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_MaterialNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_MaterialNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->program = (Arcadia_Visuals_VPL_Program*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_VPL_Program_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_MaterialNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_MaterialNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_MaterialNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MaterialNode* self
  )
{
  if (self->program) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->program);
  }
}

Arcadia_Visuals_Scene_MaterialNode*
Arcadia_Visuals_Scene_MaterialNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* program
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)program);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Scene_MaterialNode);
}
