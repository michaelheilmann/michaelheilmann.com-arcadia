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

#include "Arcadia/MILC/AST/Instructions/InvokeInstructionNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor(callee:Arcadia.MIL.VariableOperandAst,operands:Arcadia.List)
/// @endcode
static void
Arcadia_MILC_AST_InvokeInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNode* self
  );

static void
Arcadia_MILC_AST_InvokeInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNodeDispatch* self
  );

static void
Arcadia_MILC_AST_InvokeInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_InvokeInstructionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_InvokeInstructionNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_InvokeInstructionNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.InvokeInstructionNode", Arcadia_MILC_AST_InvokeInstructionNode,
                         u8"Arcadia.MILC.AST.InstructionNode", Arcadia_MILC_AST_InstructionNode,
                         &_typeOperations);

void
Arcadia_MILC_AST_InvokeInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_InvokeInstructionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->callee = (Arcadia_MILC_AST_VariableOperandNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_AST_VariableOperandNode_getType(thread));
  self->operands = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_InvokeInstructionNode);
}

static void
Arcadia_MILC_AST_InvokeInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_InvokeInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InvokeInstructionNode* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->callee);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->operands);
}

Arcadia_MILC_AST_InvokeInstructionNode*
Arcadia_MILC_AST_InvokeInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNode* callee,
    Arcadia_List* operands
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (callee) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, callee);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (operands) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operands);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_InvokeInstructionNode);
}
