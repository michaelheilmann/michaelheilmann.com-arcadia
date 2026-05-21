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

#include "Arcadia/MILC/AST/InstructionStatementNode.h"

#include "Arcadia/MILC/AST/Include.h"

static void
Arcadia_MILC_AST_InstructionStatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InstructionStatementNode* self
  );

static void
Arcadia_MILC_AST_InstructionStatementNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InstructionStatementNodeDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_InstructionStatementNode_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_InstructionStatementNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.InstructionStatementNode", Arcadia_MILC_AST_InstructionStatementNode,
                         u8"Arcadia.MILC.AST.StatementNode", Arcadia_MILC_AST_StatementNode,
                         &_typeOperations);

static void
Arcadia_MILC_AST_InstructionStatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InstructionStatementNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_InstructionStatementNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_InstructionStatementNode);
}

static void
Arcadia_MILC_AST_InstructionStatementNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_InstructionStatementNodeDispatch* self
  )
{/*Intentionally empty.*/}
