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

#include "Arcadia/MIL/AST/ExpressionStatementAst.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(targetVariableName : Arcadia.String, expression : MIL.ExpressionAst)
/// @endcode
static void
Arcadia_MIL_ExpressionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  );

static void
Arcadia_MIL_ExpressionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_ExpressionStatementAst_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_ExpressionStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_ExpressionStatementAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_ExpressionStatementAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_ExpressionStatementAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.ExpressionStatementAst", Arcadia_MIL_ExpressionStatementAst,
                         u8"Arcadia.MIL.AST.StatementNode", Arcadia_MIL_AST_StatementNode,
                         &_Arcadia_MIL_ExpressionStatementAst_typeOperations);

static void
Arcadia_MIL_ExpressionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_ExpressionStatementAst_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->targetVariableName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->expression = (Arcadia_MIL_AST_ExpressionNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MIL_AST_ExpressionNode_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_ExpressionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->targetVariableName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->expression);
}

Arcadia_MIL_ExpressionStatementAst*
Arcadia_MIL_ExpressionStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* targetVariableName,
    Arcadia_MIL_AST_ExpressionNode* expression
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (targetVariableName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, targetVariableName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (expression) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, expression);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_ExpressionStatementAst);
}

Arcadia_String*
Arcadia_MIL_ExpressionStatementAst_getTargetVariableName
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  )
{ return self->targetVariableName; }

Arcadia_MIL_AST_ExpressionNode*
Arcadia_MIL_ExpressionStatementAst_getExpression
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  )
{ return self->expression; }
