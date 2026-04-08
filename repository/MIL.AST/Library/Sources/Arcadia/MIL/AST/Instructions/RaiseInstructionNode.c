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

#include "Arcadia/MIL/AST/Instructions/RaiseInstructionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor()
/// @endcode
static void
Arcadia_MIL_AST_RaiseInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNode* self
  );

static void
Arcadia_MIL_AST_RaiseInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNodeDispatch* self
  );

static void
Arcadia_MIL_AST_RaiseInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_AST_RaiseInstructionNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_AST_RaiseInstructionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_AST_RaiseInstructionNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MIL_AST_RaiseInstructionNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_MIL_AST_RaiseInstructionNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_AST_RaiseInstructionNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.RaiseInstructionNode", Arcadia_MIL_AST_RaiseInstructionNode,
                         u8"Arcadia.MIL.AST.InstructionNode", Arcadia_MIL_AST_InstructionNode,
                         &_Arcadia_MIL_AST_RaiseInstructionNode_typeOperations);

static void
Arcadia_MIL_AST_RaiseInstructionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MIL_AST_RaiseInstructionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MIL_AST_RaiseInstructionNode);
}

static void
Arcadia_MIL_AST_RaiseInstructionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_AST_RaiseInstructionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_RaiseInstructionNode* self
  )
{/*Intentionally empty.*/}

Arcadia_MIL_AST_RaiseInstructionNode*
Arcadia_MIL_AST_RaiseInstructionNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_RaiseInstructionNode);
}
