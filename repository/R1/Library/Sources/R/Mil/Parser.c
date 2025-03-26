// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-22

#include "R/Mil/Parser.h"

#include "R/Mil/Scanner.h"
#include "R/Mil/Ast.h"

struct Arcadia_Mil_Parser {
  Arcadia_Object _parent;
  // The index of the Byte in the input stream at which the current symbol starts.
  Arcadia_Mil_Scanner* scanner;
};

static void
Arcadia_Mil_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static void
Arcadia_Mil_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self,
    Arcadia_Mil_TokenType type
  );

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Mil_Parser_constructImpl,
  .destruct = &Arcadia_Mil_Parser_destruct,
  .visit = &Arcadia_Mil_Parser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Arcadia.Mil.Parser", Arcadia_Mil_Parser, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Mil_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Parser* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_Parser_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->scanner = Arcadia_Mil_Scanner_create(thread);
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Mil_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{ Arcadia_Object_visit(thread, self->scanner); }

static Arcadia_Mil_TokenType
getType
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{ return Arcadia_Mil_Scanner_getTokenType(thread, self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{ return Arcadia_Mil_Scanner_getTokenText(thread, self->scanner); }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self,
    Arcadia_Mil_TokenType type
  )
{ return type == getType(thread, self); }

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_Mil_Scanner_step(thread, self->scanner);
  while (Arcadia_Mil_TokenType_WhiteSpaces == getType(thread, self) || Arcadia_Mil_TokenType_SingleLineComment == getType(thread, self) || Arcadia_Mil_TokenType_MultiLineComment == getType(thread, self)) {
    Arcadia_Mil_Scanner_step(thread, self->scanner);
  }
}

Arcadia_Mil_Parser*
Arcadia_Mil_Parser_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_Mil_Parser* self = Arcadia_allocateObject(thread, _Arcadia_Mil_Parser_getType(thread), 0, &argumentValues[0]);
  return self;
}

static Arcadia_Mil_OperandAst*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ExpressionAst*
onExpression
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static void
onEndOfStatement
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_StatementAst*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_String*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_List*
onParameters
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ModuleAst*
onModule
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
static Arcadia_Mil_OperandAst*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_Mil_TokenType_BooleanLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_BooleanLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_IntegerLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_IntegerLiteralOperandAst_create(Arcadia_Thread_getProcess(thread), getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_RealLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_RealLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_StringLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_StringLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_VoidLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_VoidLiteralOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_Name: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_VariableOperandAst_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static Arcadia_Mil_InvokeExpressionAst*
onInvokeExpression
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  next(thread, self);
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_Mil_VariableOperandAst* calleeAst = Arcadia_Mil_VariableOperandAst_create(thread, getText(thread, self));
  if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_List* operands = Arcadia_List_create(thread);
  if (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput) && !is(thread, self, Arcadia_Mil_TokenType_RightParenthesis)) {
    Arcadia_Mil_OperandAst* operand = onOperand(thread, self);
    Arcadia_List_appendObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(thread, self, Arcadia_Mil_TokenType_Comma) || is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
        continue;
      }
      next(thread, self);
      operand = onOperand(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_RightParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_Mil_InvokeExpressionAst* invokeExpressionAst = Arcadia_Mil_InvokeExpressionAst_create(Arcadia_Thread_getProcess(thread), calleeAst, operands);
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
static Arcadia_Mil_ExpressionAst*
onExpression
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  switch (getType(thread, self)) {
    // constantExpression
    case Arcadia_Mil_TokenType_BooleanLiteral:
    case Arcadia_Mil_TokenType_IntegerLiteral:
    case Arcadia_Mil_TokenType_RealLiteral:
    case Arcadia_Mil_TokenType_StringLiteral:
    case Arcadia_Mil_TokenType_VoidLiteral: 
    case Arcadia_Mil_TokenType_Name: {
      Arcadia_Mil_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_LoadExpressionAst_create(thread, operand);
    } break;
    // binaryExpression
    case Arcadia_Mil_TokenType_Add: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_And: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_And, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Concatenate: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Divide: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Multiply: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Or: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Or, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Subtract: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_Mil_TokenType_IsEqualTo: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsNotEqualTo: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsNotEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsLowerThan: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsLowerThan, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsLowerThanOrEqualTo: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsLowerThanOrEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsGreaterThan: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsGreaterThan, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsGreaterThanOrEqualTo: {
      next(thread, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(thread, Arcadia_Mil_BinaryExpressionAstType_IsGreaterThanOrEqualTo, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_Mil_TokenType_Negate: {
      next(thread, self);
      Arcadia_Mil_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_UnaryExpressionAst_create(thread, Arcadia_Mil_UnaryExpressionAstType_Negate, operand);
    } break;
    case Arcadia_Mil_TokenType_Not: {
      next(thread, self);
      Arcadia_Mil_OperandAst* operand = onOperand(thread, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_UnaryExpressionAst_create(thread, Arcadia_Mil_UnaryExpressionAstType_Not, operand);
    } break;
    case Arcadia_Mil_TokenType_Invoke: {
      return (Arcadia_Mil_ExpressionAst*)onInvokeExpression(thread, self);
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
    Arcadia_Mil_Parser* self
  )
{
  if (is(thread, self, Arcadia_Mil_TokenType_EndOfInput)) {
    return;
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket) && !is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
}

static Arcadia_Mil_VariableDefinitionStatementAst*
onVariableDefinitionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  if (Arcadia_Mil_TokenType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_Mil_TokenType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Mil_VariableDefinitionStatementAst* variableDefinitionStatementAst = Arcadia_Mil_VariableDefinitionStatementAst_create(thread, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
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
static Arcadia_Mil_StatementAst*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  // skip empty statement 
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  // raise statement
  if (is(thread, self, Arcadia_Mil_TokenType_Raise)) {
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_Mil_RaiseStatementAst* statementAst = Arcadia_Mil_RaiseStatementAst_create(thread);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // jump statement
  if (is(thread, self, Arcadia_Mil_TokenType_Jump)) {
    if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(Arcadia_Thread_getProcess(thread), Arcadia_Mil_JumpStatementAstType_Jump, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  } else if (is(thread, self, Arcadia_Mil_TokenType_JumpIfTrue)) {
    if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(Arcadia_Thread_getProcess(thread), Arcadia_Mil_JumpStatementAstType_JumpIfTrue, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  } else if (is(thread, self, Arcadia_Mil_TokenType_JumpIfFalse)) {
    if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(Arcadia_Thread_getProcess(thread), Arcadia_Mil_JumpStatementAstType_JumpIfFalse, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // return statement
  if (is(thread, self, Arcadia_Mil_TokenType_Return)) {
    next(thread, self);
    Arcadia_Mil_OperandAst* operandAst = NULL;
    if (is(thread, self, Arcadia_Mil_TokenType_BooleanLiteral) || is(thread, self, Arcadia_Mil_TokenType_IntegerLiteral) || is(thread, self, Arcadia_Mil_TokenType_RealLiteral) || is(thread, self, Arcadia_Mil_TokenType_StringLiteral) || is(thread, self, Arcadia_Mil_TokenType_Name)) {
      operandAst = onOperand(thread, self);
    }
    onEndOfStatement(thread, self);
    Arcadia_Mil_ReturnStatementAst* statementAst = Arcadia_Mil_ReturnStatementAst_create(thread, operandAst);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // variable definition statement
  if (is(thread, self, Arcadia_Mil_TokenType_Variable)) {
    Arcadia_Mil_VariableDefinitionStatementAst* statementAst = onVariableDefinitionStatement(thread, self);
    onEndOfStatement(thread, self);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Mil_StatementAst* statementAst = NULL;
  Arcadia_String* nameString = getText(thread, self);
  next(thread, self);
  switch (getType(thread, self)) {
    case Arcadia_Mil_TokenType_EqualsSign: {
      next(thread, self);
      Arcadia_Mil_ExpressionAst* expressionAst = onExpression(thread, self);
      statementAst = (Arcadia_Mil_StatementAst*)Arcadia_Mil_ExpressionStatementAst_create(Arcadia_Thread_getProcess(thread), nameString, expressionAst);
      onEndOfStatement(thread, self);
    } break;
    case Arcadia_Mil_TokenType_Colon: {
      next(thread, self);
      statementAst = (Arcadia_Mil_StatementAst*)Arcadia_Mil_LabelStatementAst_create(thread, nameString);
      // statement terminator injection
      if (is(thread, self, Arcadia_Mil_TokenType_EndOfInput) || is(thread, self, Arcadia_Mil_TokenType_LineTerminator) || is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
        if (is(thread, self, Arcadia_Mil_TokenType_LineTerminator) || is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
          next(thread, self);
        }
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return statementAst;
}

// variable <name>
static Arcadia_String*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  ) 
{
  if (!is(thread, self, Arcadia_Mil_TokenType_Variable)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
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
    Arcadia_Mil_Parser* self
  )
{ 
  Arcadia_List* parameters = Arcadia_List_create(thread);
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_String* parameter = NULL;
    if (is(thread, self, Arcadia_Mil_TokenType_Variable)) {
      parameter = onParameter(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
        next(thread, self);
      }
      while (is(thread, self, Arcadia_Mil_TokenType_Comma)) {
        next(thread, self);
        while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
          next(thread, self);
        }
        parameter = onParameter(thread, self);
        Arcadia_List_appendObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
          next(thread, self);
        }
      }
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_RightParenthesis)) {
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
static Arcadia_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(thread, self, Arcadia_Mil_TokenType_Constructor)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_Mil_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* constructorParameters = onParameters(thread, self);
  Arcadia_List* constructorBody = NULL;
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    constructorBody = Arcadia_List_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput) && !is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, constructorBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    if (!is(thread, self, Arcadia_Mil_TokenType_RightParenthesis)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
  }
  Arcadia_Mil_ConstructorDefinitionAst* constructorDefinitionAst = Arcadia_Mil_ConstructorDefinitionAst_create(Arcadia_Thread_getProcess(thread), nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static Arcadia_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(thread, self, Arcadia_Mil_TokenType_Method)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_Mil_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* methodName = getText(thread, self);
  next(thread, self);
  Arcadia_List* methodParameters = onParameters(thread, self);
  Arcadia_List* methodBody = NULL;
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    methodBody = Arcadia_List_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput) && !is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, methodBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_Mil_MethodDefinitionAst* methodDefinitionAst = Arcadia_Mil_MethodDefinitionAst_create(thread, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static Arcadia_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  if (Arcadia_Mil_TokenType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_Mil_TokenType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Mil_VariableDefinitionAst* variableDefinitionAst = Arcadia_Mil_VariableDefinitionAst_create(thread, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static Arcadia_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{ 
  switch (getType(thread, self)) {
    case Arcadia_Mil_TokenType_Constructor: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onConstructorDefinition(thread, self);
    } break;
    case Arcadia_Mil_TokenType_Method: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onMethodDefinition(thread, self);
    } break;
    case Arcadia_Mil_TokenType_Variable: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onVariableDefinition(thread, self);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static Arcadia_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(thread, self, Arcadia_Mil_TokenType_Class)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* className = getText(thread, self);
  next(thread, self);
  Arcadia_String* extendedClassName = NULL;
  if (is(thread, self, Arcadia_Mil_TokenType_Extends)) {
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    extendedClassName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* classBody = NULL;
  if (is(thread, self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    classBody = Arcadia_List_create(thread);
    while (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput) && !is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_ClassMemberDefinitionAst* classMemberDefinitionAst = onClassMemberDefinition(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_Mil_ClassDefinitionAst* classDefinitionAst = Arcadia_Mil_ClassDefinitionAst_create(Arcadia_Thread_getProcess(thread), className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static Arcadia_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_BooleanValue entry = Arcadia_BooleanValue_False;
  if (!is(thread, self, Arcadia_Mil_TokenType_Procedure)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_Mil_TokenType_Entry)) {
    next(thread, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_Mil_TokenType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* procedureName = getText(thread, self);
  next(thread, self);
  Arcadia_List* procedureParameters = onParameters(thread, self);
  Arcadia_List* procedureBody = NULL;
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    procedureBody = Arcadia_List_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput) && !is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(thread, self);
      Arcadia_List_appendObjectReferenceValue(thread, procedureBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_Mil_ProcedureDefinitionAst* procedureDefinitionAst = Arcadia_Mil_ProcedureDefinitionAst_create(thread, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|proceduredefinition)*
static Arcadia_Mil_ModuleAst*
onModule
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_Mil_ModuleAst* moduleAst = Arcadia_Mil_ModuleAst_create(thread);
  if (!is(thread, self, Arcadia_Mil_TokenType_StartOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput)) {
    while (is(thread, self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_Mil_DefinitionAst* definitionAst = NULL;
    switch (getType(thread, self)) {
      case Arcadia_Mil_TokenType_Class: {
        definitionAst = (Arcadia_Mil_DefinitionAst*)onClassDefinition(thread, self);
        Arcadia_Mil_ModuleAst_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      case Arcadia_Mil_TokenType_Procedure: {
        definitionAst = (Arcadia_Mil_DefinitionAst*)onProcedureDefinition(thread, self);
        Arcadia_Mil_ModuleAst_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
  if (!is(thread, self, Arcadia_Mil_TokenType_EndOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return moduleAst;
}

Arcadia_Mil_ModuleAst*
Arcadia_Mil_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  )
{ 
  Arcadia_Mil_ModuleAst* moduleAst = onModule(thread, self);
  return moduleAst;
}

void
Arcadia_Mil_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self,
    Arcadia_Utf8Reader* input
  )
{
  Arcadia_Mil_Scanner_setInput(thread, self->scanner, input);
}
