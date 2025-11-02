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

#include "Arcadia/Visuals/Scene/MeshNode.h"

static void
Arcadia_Visuals_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Scene_MeshNode_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Scene_MeshNode_destructImpl,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_MeshNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->baseColor.red = 1;
  self->baseColor.green = 1;
  self->baseColor.blue = 1;
  self->baseColor.alpha = 1;
  self->numberOfVertices = 3;
  self->vertexPositions = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Real32Value) * 3 * 3);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    self->vertexColors = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Real32Value) * 4 * 3);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertexPositions);
    self->vertexPositions = NULL;
    Arcadia_Thread_jump(thread);
  }
  static const Arcadia_Real32Value POSITIONS[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
  };
  Arcadia_Memory_copy(thread, self->vertexPositions, &POSITIONS[0], sizeof(Arcadia_Real32Value) * 3 * 3);
  static const Arcadia_Real32Value COLORS[] = {
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
  };
  Arcadia_Memory_copy(thread, self->vertexColors, &COLORS[0], sizeof(Arcadia_Real32Value) * 4 * 3);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{ 
  if (self->vertexPositions) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertexPositions);
    self->vertexPositions = NULL;
  }
  if (self->vertexColors) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertexColors);
    self->vertexColors = NULL;
  }
}
