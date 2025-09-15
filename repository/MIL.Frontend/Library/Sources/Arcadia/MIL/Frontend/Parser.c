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

#include "Arcadia/MIL/Frontend/Parser.h"

#include "Arcadia/MIL/Frontend/Include.h"

struct Arcadia_MIL_Parser {
  Arcadia_Object _parent;
  // The index of the Byte in the input stream at which the current symbol starts.
  Arcadia_MIL_Scanner* scanner;
};

static void
Arcadia_MIL_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static void
Arcadia_MIL_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_MIL_TokenType type
  );

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_MIL_Parser_constructImpl,
  .destruct = &Arcadia_MIL_Parser_destruct,
  .visit = &Arcadia_MIL_Parser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Parser", Arcadia_MIL_Parser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_Parser* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_Parser_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner); }

static Arcadia_MIL_TokenType
getType
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ return Arcadia_MIL_Scanner_getTokenType(thread, self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ return Arcadia_MIL_Scanner_getTokenText(thread, self->scanner); }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_MIL_TokenType type
  )
{ return type == getType(thread, self); }

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_Scanner_step(thread, self->scanner);
  while (Arcadia_MIL_TokenType_WhiteSpaces == getType(thread, self) || Arcadia_MIL_TokenType_SingleLineComment == getType(thread, self) || Arcadia_MIL_TokenType_MultiLineComment == getType(thread, self)) {
    Arcadia_MIL_Scanner_step(thread, self->scanner);
  }
}

Arcadia_MIL_Parser*
Arcadia_MIL_Parser_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Parser);
}

static Arcadia_MIL_OperandAst*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_ExpressionAst*
onExpression
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static void
onEndOfStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_StatementAst*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_String*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_List*
onParameters
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_Ast*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_ModuleAst*
onModule
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
static Arcadia_MIL_OperandAst*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_BooleanLiteral: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_BooleanLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_IntegerLiteral: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_IntegerLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_RealLiteral: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_RealLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_StringLiteral: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_StringLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_VoidLiteral: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_VoidLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_Name: {
      Arcadia_MIL_OperandAst* operandAst = (Arcadia_MIL_OperandAst*)Arcadia_MIL_VariableOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static Arcadia_MIL_InvokeExpressionAst*
onInvokeExpression
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  next(thread, self);
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_VariableOperandAst* calleeAst = Arcadia_MIL_VariableOperandAst_create(thread, getText(thread, self));
  if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_LeftParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_List* operands = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  if (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput) && !is(thread, self, Arcadia_MIL_TokenType_RightParenthesis)) {
    Arcadia_MIL_OperandAst* operand = onOperand(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(thread, self, Arcadia_MIL_TokenType_Comma) || is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
        continue;
      }
      next(thread, self);
      operand = onOperand(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_RightParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_MIL_InvokeExpressionAst* invokeExpressionAst = Arcadia_MIL_InvokeExpressionAst_create(thread, calleeAst, operands);
  return invokeExpressionAst;
}

// expression :
//   unaryExpression
//   binaryExpression
//   invokeExpression
//
// invokeExpression :
//  'invoke' variableOperand '(' ( operand (',' operand)* )? ')'
//
// binaryExpression :
//   'add' <op1>, <op2>
//   'and' <op1>, <op2>
//   'concatenate' <op1>, <op2>
//   'divide' <op1>, <op2>
//   'multiply' <op1>, <op2>
//   'or' <op1>, <op2>
//   'subtract' <op1>, <op2>
//   'isEqualTo' <op1>, <op2>
//   'isNotEqualTo' <op1>, <op2>
//   'isLowerThan' <op1>, <op2>
//   'isLowerThanOrEqualTo' <op1>, <op2>
//   'isGreaterThan' <op1>, <op2>
//   'isGreaterThanOrEqualTo' <op1>, <op2>
//
// unaryExpression:
//   <op1>
//   'negate' <op1>
//   'not' <op1>
static Arcadia_MIL_ExpressionAst*
onExpression
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    // constantExpression
    case Arcadia_MIL_TokenType_BooleanLiteral:
    case Arcadia_MIL_TokenType_IntegerLiteral:
    case Arcadia_MIL_TokenType_RealLiteral:
    case Arcadia_MIL_TokenType_StringLiteral:
    case Arcadia_MIL_TokenType_VoidLiteral:
    case Arcadia_MIL_TokenType_Name: {
      Arcadia_MIL_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_LoadExpressionAst_create(thread, operand);
    } break;
    // binaryExpression
    case Arcadia_MIL_TokenType_Add: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_And: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_And, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Concatenate: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Divide: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Multiply: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Or: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Or, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Subtract: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_MIL_TokenType_IsEqualTo: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsNotEqualTo: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsNotEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsLowerThan: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsLowerThan, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsLowerThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsLowerThanOrEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsGreaterThan: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsGreaterThan, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsGreaterThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_BinaryExpressionAst_create(thread, Arcadia_MIL_BinaryExpressionAstType_IsGreaterThanOrEqualTo, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_MIL_TokenType_Negate: {
      next(thread, self);
      Arcadia_MIL_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_UnaryExpressionAst_create(thread, Arcadia_MIL_UnaryExpressionAstType_Negate, operand);
    } break;
    case Arcadia_MIL_TokenType_Not: {
      next(thread, self);
      Arcadia_MIL_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_MIL_ExpressionAst*)Arcadia_MIL_UnaryExpressionAst_create(thread, Arcadia_MIL_UnaryExpressionAstType_Not, operand);
    } break;
    case Arcadia_MIL_TokenType_Invoke: {
      return (Arcadia_MIL_ExpressionAst*)onInvokeExpression(thread, self);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static void
onEndOfStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (is(thread, self, Arcadia_MIL_TokenType_EndOfInput)) {
    return;
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket) && !is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
}

static Arcadia_MIL_VariableDefinitionStatementAst*
onVariableDefinitionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (Arcadia_MIL_TokenType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MIL_TokenType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_VariableDefinitionStatementAst* variableDefinitionStatementAst = Arcadia_MIL_VariableDefinitionStatementAst_create(thread, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return variableDefinitionStatementAst;
}

/// statement : expressionStatement endOfStatement
///           | labelStatement endOfStatement?
///           | returnStatement endOfStatement
///           | emptyStatement endOfStatement
///           | jumpStatement endOfStatement
/// expressionStatement: name '=' expression
/// labelStatement: name ':'
/// variableDefinitionStatement : variableDefinition
/// returnStatement : 'return' operand?
/// jumpStatement : 'jump'|'jumpIfTrue'|'jumpIfFalse' name
/// raiseStatement : 'raise'
static Arcadia_MIL_StatementAst*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  // skip empty statement
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  // raise statement
  if (is(thread, self, Arcadia_MIL_TokenType_Raise)) {
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_RaiseStatementAst* statementAst = Arcadia_MIL_RaiseStatementAst_create(thread);
    return (Arcadia_MIL_StatementAst*)statementAst;
  }
  // jump statement
  if (is(thread, self, Arcadia_MIL_TokenType_Jump)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_JumpStatementAst* statementAst = Arcadia_MIL_JumpStatementAst_create(thread, Arcadia_MIL_JumpStatementAstType_Jump, labelName);
    return (Arcadia_MIL_StatementAst*)statementAst;
  } else if (is(thread, self, Arcadia_MIL_TokenType_JumpIfTrue)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_JumpStatementAst* statementAst = Arcadia_MIL_JumpStatementAst_create(thread, Arcadia_MIL_JumpStatementAstType_JumpIfTrue, labelName);
    return (Arcadia_MIL_StatementAst*)statementAst;
  } else if (is(thread, self, Arcadia_MIL_TokenType_JumpIfFalse)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_JumpStatementAst* statementAst = Arcadia_MIL_JumpStatementAst_create(thread, Arcadia_MIL_JumpStatementAstType_JumpIfFalse, labelName);
    return (Arcadia_MIL_StatementAst*)statementAst;
  }
  // return statement
  if (is(thread, self, Arcadia_MIL_TokenType_Return)) {
    next(thread, self);
    Arcadia_MIL_OperandAst* operandAst = NULL;
    if (is(thread, self, Arcadia_MIL_TokenType_BooleanLiteral) || is(thread, self, Arcadia_MIL_TokenType_IntegerLiteral) || is(thread, self, Arcadia_MIL_TokenType_RealLiteral) || is(thread, self, Arcadia_MIL_TokenType_StringLiteral) || is(thread, self, Arcadia_MIL_TokenType_Name)) {
      operandAst = onOperand(thread, self);
    }
    onEndOfStatement(thread, self);
    Arcadia_MIL_ReturnStatementAst* statementAst = Arcadia_MIL_ReturnStatementAst_create(thread, operandAst);
    return (Arcadia_MIL_StatementAst*)statementAst;
  }
  // variable definition statement
  if (is(thread, self, Arcadia_MIL_TokenType_Variable)) {
    Arcadia_MIL_VariableDefinitionStatementAst* statementAst = onVariableDefinitionStatement(thread, self);
    onEndOfStatement(thread, self);
    return (Arcadia_MIL_StatementAst*)statementAst;
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_StatementAst* statementAst = NULL;
  Arcadia_String* nameString = getText(thread, self);
  next(thread, self);
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_EqualsSign: {
      next(thread, self);
      Arcadia_MIL_ExpressionAst* expressionAst = onExpression(thread, self);
      statementAst = (Arcadia_MIL_StatementAst*)Arcadia_MIL_ExpressionStatementAst_create(thread, nameString, expressionAst);
      onEndOfStatement(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Colon: {
      next(thread, self);
      statementAst = (Arcadia_MIL_StatementAst*)Arcadia_MIL_LabelStatementAst_create(thread, nameString);
      // statement terminator injection
      if (is(thread, self, Arcadia_MIL_TokenType_EndOfInput) || is(thread, self, Arcadia_MIL_TokenType_LineTerminator) || is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
        if (is(thread, self, Arcadia_MIL_TokenType_LineTerminator) || is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
          next(thread, self);
        }
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return statementAst;
}

// variable <name>
static Arcadia_String*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MIL_TokenType_Variable)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* parameter = getText(thread, self);
  next(thread, self);
  return parameter;
}

// parameters : '(' (parameter (',' parameter)*)? ')'
static Arcadia_List*
onParameters
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_List* parameters = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LeftParenthesis)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_String* parameter = NULL;
    if (is(thread, self, Arcadia_MIL_TokenType_Variable)) {
      parameter = onParameter(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
        next(thread, self);
      }
      while (is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        next(thread, self);
        while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
          next(thread, self);
        }
        parameter = onParameter(thread, self);
        Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
          next(thread, self);
        }
      }
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_RightParenthesis)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  return parameters;
}

// constructorDefinition : 'constructor' ('native' string)? constructorParameters? constructorBody?
// constructorParameters : parameters
// constructorBody : '{' statements '}
static Arcadia_MIL_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MIL_TokenType_Constructor)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* constructorParameters = onParameters(thread, self);
  Arcadia_List* constructorBody = NULL;
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LeftCurlyBracket)) {
    constructorBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput) && !is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_MIL_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, constructorBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LeftParenthesis)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_RightParenthesis)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
  }
  Arcadia_MIL_ConstructorDefinitionAst* constructorDefinitionAst = Arcadia_MIL_ConstructorDefinitionAst_create(thread, nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static Arcadia_MIL_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MIL_TokenType_Method)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* methodName = getText(thread, self);
  next(thread, self);
  Arcadia_List* methodParameters = onParameters(thread, self);
  Arcadia_List* methodBody = NULL;
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LeftCurlyBracket)) {
    methodBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput) && !is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_MIL_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, methodBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_MethodDefinitionAst* methodDefinitionAst = Arcadia_MIL_MethodDefinitionAst_create(thread, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static Arcadia_MIL_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (Arcadia_MIL_TokenType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MIL_TokenType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_VariableDefinitionAst* variableDefinitionAst = Arcadia_MIL_VariableDefinitionAst_create(thread, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static Arcadia_MIL_Ast*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_Constructor: {
      return (Arcadia_MIL_Ast*)onConstructorDefinition(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Method: {
      return (Arcadia_MIL_Ast*)onMethodDefinition(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Variable: {
      return (Arcadia_MIL_Ast*)onVariableDefinition(thread, self);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static Arcadia_MIL_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MIL_TokenType_Class)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* className = getText(thread, self);
  next(thread, self);
  Arcadia_String* extendedClassName = NULL;
  if (is(thread, self, Arcadia_MIL_TokenType_Extends)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    extendedClassName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* classBody = NULL;
  if (is(thread, self, Arcadia_MIL_TokenType_LeftCurlyBracket)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    classBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    while (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput) && !is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_MIL_Ast* classMemberDefinitionAst = onClassMemberDefinition(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_ClassDefinitionAst* classDefinitionAst = Arcadia_MIL_ClassDefinitionAst_create(thread, className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static Arcadia_MIL_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_BooleanValue entry = Arcadia_BooleanValue_False;
  if (!is(thread, self, Arcadia_MIL_TokenType_Procedure)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MIL_TokenType_Entry)) {
    next(thread, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* procedureName = getText(thread, self);
  next(thread, self);
  Arcadia_List* procedureParameters = onParameters(thread, self);
  Arcadia_List* procedureBody = NULL;
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_TokenType_LeftCurlyBracket)) {
    procedureBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput) && !is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_MIL_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, procedureBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_ProcedureDefinitionAst* procedureDefinitionAst = Arcadia_MIL_ProcedureDefinitionAst_create(thread, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|proceduredefinition)*
static Arcadia_MIL_ModuleAst*
onModule
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_ModuleAst* moduleAst = Arcadia_MIL_ModuleAst_create(thread);
  if (!is(thread, self, Arcadia_MIL_TokenType_StartOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput)) {
    while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_MIL_DefinitionAst* definitionAst = NULL;
    switch (getType(thread, self)) {
      case Arcadia_MIL_TokenType_Class: {
        definitionAst = (Arcadia_MIL_DefinitionAst*)onClassDefinition(thread, self);
        Arcadia_MIL_ModuleAst_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      case Arcadia_MIL_TokenType_Procedure: {
        definitionAst = (Arcadia_MIL_DefinitionAst*)onProcedureDefinition(thread, self);
        Arcadia_MIL_ModuleAst_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_EndOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return moduleAst;
}

Arcadia_MIL_ModuleAst*
Arcadia_MIL_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_ModuleAst* moduleAst = onModule(thread, self);
  return moduleAst;
}

void
Arcadia_MIL_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_Utf8Reader* input
  )
{
  Arcadia_MIL_Scanner_setInput(thread, self->scanner, input);
}
