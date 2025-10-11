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

#include "Arcadia/MIL/AST/InstructionStatementNode.h"

#include "Arcadia/MIL/AST/Include.h"

static void
Arcadia_MIL_AST_InstructionStatementNode2_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_InstructionStatementNode2* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_InstructionStatementNode2_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.InstructionStatementNode2", Arcadia_MIL_AST_InstructionStatementNode2,
                         u8"Arcadia.MIL.AST.StatementNode", Arcadia_MIL_AST_StatementNode,
                         &_typeOperations);

static void
Arcadia_MIL_AST_InstructionStatementNode2_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_InstructionStatementNode2* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_InstructionStatementNode2_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}
