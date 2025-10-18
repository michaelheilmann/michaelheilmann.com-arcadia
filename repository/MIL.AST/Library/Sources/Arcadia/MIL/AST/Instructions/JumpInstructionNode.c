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

#include "Arcadia/MIL/AST/Instructions/JumpInstructionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(operand:Arcadia.MIL.AST.OperandNode)
/// @endcode
static void
Arcadia_MIL_AST_JumpInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpInstructionNode* self
  );

static void
Arcadia_MIL_AST_JumpInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpInstructionNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_AST_JumpInstructionNode_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_JumpInstructionNode_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_AST_JumpInstructionNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_AST_JumpInstructionNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_AST_JumpInstructionNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.JumpInstructionNode", Arcadia_MIL_AST_JumpInstructionNode,
                         u8"Arcadia.MIL.AST.InstructionNode", Arcadia_MIL_AST_InstructionNode,
                         &_Arcadia_MIL_AST_JumpInstructionNode_typeOperations);

static void
Arcadia_MIL_AST_JumpInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpInstructionNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_JumpInstructionNode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->labelName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_AST_JumpInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpInstructionNode* self
  )
{
  if (self->labelName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->labelName);
  }
}

Arcadia_MIL_AST_JumpInstructionNode*
Arcadia_MIL_AST_JumpInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* labelName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (labelName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, labelName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_JumpInstructionNode);
}
