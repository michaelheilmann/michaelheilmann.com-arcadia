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

#include "Arcadia/MIL/AST/InstructionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor()
/// @endcode
static void
Arcadia_MIL_AST_ExpressionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ExpressionNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_AST_ExpressionNode_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_ExpressionNode_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _Arcadia_MIL_AST_ExpressionNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_AST_ExpressionNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.ExpressionNode", Arcadia_MIL_AST_ExpressionNode,
                         u8"Arcadia.MIL.AST.Node", Arcadia_MIL_AST_Node,
                         &_Arcadia_MIL_AST_ExpressionNode_typeOperations);

void
Arcadia_MIL_AST_ExpressionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ExpressionNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_ExpressionNode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

