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

#include "Arcadia/MILC/AST/StatementNode.h"

#include "Arcadia/MILC/AST/Include.h"

static void
Arcadia_MILC_AST_StatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_StatementNode* self
  );

static void
Arcadia_MILC_AST_StatementNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_StatementNodeDispatch* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MILC_AST_StatementNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_StatementNode_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_StatementNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_MILC_AST_StatementNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MILC_AST_StatementNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.StatementNode", Arcadia_MILC_AST_StatementNode,
                         u8"Arcadia.MILC.AST.Node", Arcadia_MILC_AST_Node,
                         &_Arcadia_MILC_AST_StatementNode_typeOperations);

static void
Arcadia_MILC_AST_StatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_StatementNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_StatementNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_StatementNode);
}

static void
Arcadia_MILC_AST_StatementNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_StatementNodeDispatch* self
  )
{/*Intentionally empty.*/}
