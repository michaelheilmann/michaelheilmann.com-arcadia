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

#include "Arcadia/MILC/AST/Instructions/BinaryInstructionNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor(kind : Arcadia.MILC.AST.BinaryInstructionKind, target, operand1, operand2 : Arcadia.MILC.AST.OperandNode)
/// @endcode
static void
Arcadia_MILC_AST_BinaryInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNode* self
  );

static void
Arcadia_MILC_AST_BinaryInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNodeDispatch* self
  );

static void
Arcadia_MILC_AST_BinaryInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MILC_AST_BinaryInstructionNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_BinaryInstructionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_BinaryInstructionNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_BinaryInstructionNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_MILC_AST_BinaryInstructionNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MILC_AST_BinaryInstructionNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.BinaryInstructionNode", Arcadia_MILC_AST_BinaryInstructionNode,
                         u8"Arcadia.MILC.AST.InstructionNode", Arcadia_MILC_AST_InstructionNode,
                         &_Arcadia_MILC_AST_BinaryInstructionNode_typeOperations);

static void
Arcadia_MILC_AST_BinaryInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_BinaryInstructionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (4 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->kind = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->target = (Arcadia_MILC_AST_OperandNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_MILC_AST_OperandNode_getType(thread));
  self->operand1 = (Arcadia_MILC_AST_OperandNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_AST_OperandNode_getType(thread));
  self->operand2 = (Arcadia_MILC_AST_OperandNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_AST_OperandNode_getType(thread));

  Arcadia_LeaveConstructor(Arcadia_MILC_AST_BinaryInstructionNode);
}

static void
Arcadia_MILC_AST_BinaryInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_BinaryInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionNode* self
  )
{
  if (self->target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->target);
  }
  if (self->operand1) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->operand1);
  }
  if (self->operand2) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->operand2);
  }
}

Arcadia_MILC_AST_BinaryInstructionNode*
Arcadia_MILC_AST_BinaryInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionKind kind,
    Arcadia_MILC_AST_OperandNode* target,
    Arcadia_MILC_AST_OperandNode* operand1,
    Arcadia_MILC_AST_OperandNode* operand2
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, kind);
  if (target) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, target);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (operand1) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operand1);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (operand2) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operand2);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_BinaryInstructionNode);
}
