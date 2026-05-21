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

#include "Arcadia/MILC/AST/Operands/VariableOperandNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor(value : Arcadia.String)
/// @endcode
static void
Arcadia_MILC_AST_VariableOperandNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNode* self
  );

static void
Arcadia_MILC_AST_VariableOperandNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNodeDispatch* self
  );

static void
Arcadia_MILC_AST_VariableOperandNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_VariableOperandNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_VariableOperandNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_VariableOperandNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.VariableOperandNode", Arcadia_MILC_AST_VariableOperandNode,
                         u8"Arcadia.MILC.AST.OperandNode", Arcadia_MILC_AST_OperandNode,
                         &_typeOperations);

void
Arcadia_MILC_AST_VariableOperandNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_VariableOperandNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->value = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_VariableOperandNode);
}

static void
Arcadia_MILC_AST_VariableOperandNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_VariableOperandNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VariableOperandNode* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->value); }

Arcadia_MILC_AST_VariableOperandNode*
Arcadia_MILC_AST_VariableOperandNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (value) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, value);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_VariableOperandNode);
}
