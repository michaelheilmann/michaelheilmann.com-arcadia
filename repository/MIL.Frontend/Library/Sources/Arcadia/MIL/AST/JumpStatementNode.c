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

#include "Arcadia/MIL/AST/JumpStatementNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(operand:Arcadia.MILOperandAst)
/// @endcode
static void
Arcadia_MIL_AST_JumpStatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpStatementNode* self
  );

static void
Arcadia_MIL_AST_JumpStatementNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpStatementNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_AST_JumpStatementNode_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_JumpStatementNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_AST_JumpStatementNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_AST_JumpStatementNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_AST_JumpStatementNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.JumpStatementNode", Arcadia_MIL_AST_JumpStatementNode,
                         u8"Arcadia.MIL.AST.StatementNode", Arcadia_MIL_AST_StatementNode,
                         &_Arcadia_MIL_AST_JumpStatementNode_typeOperations);

static void
Arcadia_MIL_AST_JumpStatementNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpStatementNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_JumpStatementNode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->labelNode = NULL;
  self->labelName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_AST_JumpStatementNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_JumpStatementNode* self
  )
{
  if (self->labelNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->labelNode);
  }
  if (self->labelName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->labelName);
  }
}

Arcadia_MIL_AST_JumpStatementNode*
Arcadia_MIL_AST_JumpStatementNode_create
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
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_JumpStatementNode);
}
