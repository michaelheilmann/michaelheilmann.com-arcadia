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
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_Parser_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static void
Arcadia_Mil_Parser_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Mil_Parser* self,
    Arcadia_Mil_TokenType type
  );

static void
next
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Parser* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_Parser_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->scanner = Arcadia_Mil_Scanner_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_Parser_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Mil_Parser_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{ Arcadia_Object_visit(process, self->scanner); }

static Arcadia_Mil_TokenType
getType
  (
    Arcadia_Mil_Parser* self
  )
{ return Arcadia_Mil_Scanner_getTokenType(self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{ return Arcadia_Mil_Scanner_getTokenText(process, self->scanner); }

static Arcadia_BooleanValue
is
  (
    Arcadia_Mil_Parser* self,
    Arcadia_Mil_TokenType type
  )
{ return type == getType(self); }

static void
next
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_Mil_Scanner_step(process, self->scanner);
  while (Arcadia_Mil_TokenType_WhiteSpaces == getType(self) || Arcadia_Mil_TokenType_SingleLineComment == getType(self) || Arcadia_Mil_TokenType_MultiLineComment == getType(self)) {
    Arcadia_Mil_Scanner_step(process, self->scanner);
  }
}

Arcadia_Mil_Parser*
Arcadia_Mil_Parser_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_Mil_Parser* self = R_allocateObject(process, _Arcadia_Mil_Parser_getType(process), 0, &argumentValues[0]);
  return self;
}

static Arcadia_Mil_OperandAst*
onOperand
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ExpressionAst*
onExpression
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static void
onEndOfStatement
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_StatementAst*
onStatement
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_String*
onParameter
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_List*
onParameters
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  );

static Arcadia_Mil_ModuleAst*
onModule
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  switch (getType(self)) {
    case Arcadia_Mil_TokenType_BooleanLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_BooleanLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_IntegerLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_IntegerLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_RealLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_RealLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_StringLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_StringLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_VoidLiteral: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_VoidLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case Arcadia_Mil_TokenType_Name: {
      Arcadia_Mil_OperandAst* operandAst = (Arcadia_Mil_OperandAst*)Arcadia_Mil_VariableOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  };
}

static Arcadia_Mil_InvokeExpressionAst*
onInvokeExpression
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  next(process, self);
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  if (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  Arcadia_Mil_VariableOperandAst* calleeAst = Arcadia_Mil_VariableOperandAst_create(process, getText(process, self));
  if (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (!is(self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  Arcadia_List* operands = Arcadia_List_create(process);
  if (!is(self, Arcadia_Mil_TokenType_EndOfInput) && !is(self, Arcadia_Mil_TokenType_RightParenthesis)) {
    Arcadia_Mil_OperandAst* operand = onOperand(process, self);
    Arcadia_List_appendObjectReferenceValue(process, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(self, Arcadia_Mil_TokenType_Comma) || is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      if (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
        continue;
      }
      next(process, self);
      operand = onOperand(process, self);
      Arcadia_List_appendObjectReferenceValue(process, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(self, Arcadia_Mil_TokenType_RightParenthesis)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  Arcadia_Mil_InvokeExpressionAst* invokeExpressionAst = Arcadia_Mil_InvokeExpressionAst_create(process, calleeAst, operands);
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
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  switch (getType(self)) {
    // constantExpression
    case Arcadia_Mil_TokenType_BooleanLiteral:
    case Arcadia_Mil_TokenType_IntegerLiteral:
    case Arcadia_Mil_TokenType_RealLiteral:
    case Arcadia_Mil_TokenType_StringLiteral:
    case Arcadia_Mil_TokenType_VoidLiteral: 
    case Arcadia_Mil_TokenType_Name: {
      Arcadia_Mil_OperandAst* operand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_LoadExpressionAst_create(process, operand);
    } break;
    // binaryExpression
    case Arcadia_Mil_TokenType_Add: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_And: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_And, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Concatenate: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Divide: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Multiply: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Or: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Or, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_Subtract: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_Mil_TokenType_IsEqualTo: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsNotEqualTo: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsNotEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsLowerThan: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsLowerThan, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsLowerThanOrEqualTo: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsLowerThanOrEqualTo, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsGreaterThan: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsGreaterThan, firstOperand, secondOperand);
    } break;
    case Arcadia_Mil_TokenType_IsGreaterThanOrEqualTo: {
      next(process, self);
      Arcadia_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, Arcadia_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      Arcadia_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_BinaryExpressionAst_create(process, Arcadia_Mil_BinaryExpressionAstType_IsGreaterThanOrEqualTo, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_Mil_TokenType_Negate: {
      next(process, self);
      Arcadia_Mil_OperandAst* operand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_UnaryExpressionAst_create(process, Arcadia_Mil_UnaryExpressionAstType_Negate, operand);
    } break;
    case Arcadia_Mil_TokenType_Not: {
      next(process, self);
      Arcadia_Mil_OperandAst* operand = onOperand(process, self);
      return (Arcadia_Mil_ExpressionAst*)Arcadia_Mil_UnaryExpressionAst_create(process, Arcadia_Mil_UnaryExpressionAstType_Not, operand);
    } break;
    case Arcadia_Mil_TokenType_Invoke: {
      return (Arcadia_Mil_ExpressionAst*)onInvokeExpression(process, self);
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  }
}

static void
onEndOfStatement
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (is(self, Arcadia_Mil_TokenType_EndOfInput)) {
    return;
  }
  if (!is(self, Arcadia_Mil_TokenType_RightCurlyBracket) && !is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
}

static Arcadia_Mil_VariableDefinitionStatementAst*
onVariableDefinitionStatement
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (Arcadia_Mil_TokenType_Variable != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (Arcadia_Mil_TokenType_Name != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_VariableDefinitionStatementAst* variableDefinitionStatementAst = Arcadia_Mil_VariableDefinitionStatementAst_create(process, getText(process, self));
  next(process, self);
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
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
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  // skip empty statement 
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  // raise statement
  if (is(self, Arcadia_Mil_TokenType_Raise)) {
    next(process, self);
    onEndOfStatement(process, self);
    Arcadia_Mil_RaiseStatementAst* statementAst = Arcadia_Mil_RaiseStatementAst_create(process);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // jump statement
  if (is(self, Arcadia_Mil_TokenType_Jump)) {
    if (!is(self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_String* labelName = getText(process, self);
    next(process, self);
    onEndOfStatement(process, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(process, Arcadia_Mil_JumpStatementAstType_Jump, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  } else if (is(self, Arcadia_Mil_TokenType_JumpIfTrue)) {
    if (!is(self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_String* labelName = getText(process, self);
    next(process, self);
    onEndOfStatement(process, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(process, Arcadia_Mil_JumpStatementAstType_JumpIfTrue, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  } else if (is(self, Arcadia_Mil_TokenType_JumpIfFalse)) {
    if (!is(self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_String* labelName = getText(process, self);
    next(process, self);
    onEndOfStatement(process, self);
    Arcadia_Mil_JumpStatementAst* statementAst = Arcadia_Mil_JumpStatementAst_create(process, Arcadia_Mil_JumpStatementAstType_JumpIfFalse, labelName);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // return statement
  if (is(self, Arcadia_Mil_TokenType_Return)) {
    next(process, self);
    Arcadia_Mil_OperandAst* operandAst = NULL;
    if (is(self, Arcadia_Mil_TokenType_BooleanLiteral) || is(self, Arcadia_Mil_TokenType_IntegerLiteral) || is(self, Arcadia_Mil_TokenType_RealLiteral) || is(self, Arcadia_Mil_TokenType_StringLiteral) || is(self, Arcadia_Mil_TokenType_Name)) {
      operandAst = onOperand(process, self);
    }
    onEndOfStatement(process, self);
    Arcadia_Mil_ReturnStatementAst* statementAst = Arcadia_Mil_ReturnStatementAst_create(process, operandAst);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  // variable definition statement
  if (is(self, Arcadia_Mil_TokenType_Variable)) {
    Arcadia_Mil_VariableDefinitionStatementAst* statementAst = onVariableDefinitionStatement(process, self);
    onEndOfStatement(process, self);
    return (Arcadia_Mil_StatementAst*)statementAst;
  }
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_StatementAst* statementAst = NULL;
  Arcadia_String* nameString = getText(process, self);
  next(process, self);
  switch (getType(self)) {
    case Arcadia_Mil_TokenType_EqualsSign: {
      next(process, self);
      Arcadia_Mil_ExpressionAst* expressionAst = onExpression(process, self);
      statementAst = (Arcadia_Mil_StatementAst*)Arcadia_Mil_ExpressionStatementAst_create(process, nameString, expressionAst);
      onEndOfStatement(process, self);
    } break;
    case Arcadia_Mil_TokenType_Colon: {
      next(process, self);
      statementAst = (Arcadia_Mil_StatementAst*)Arcadia_Mil_LabelStatementAst_create(process, nameString);
      // statement terminator injection
      if (is(self, Arcadia_Mil_TokenType_EndOfInput) || is(self, Arcadia_Mil_TokenType_LineTerminator) || is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
        if (is(self, Arcadia_Mil_TokenType_LineTerminator) || is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
          next(process, self);
        }
      }
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  return statementAst;
}

static Arcadia_String*
onParameter
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  ) 
{
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* parameter = getText(process, self);
  next(process, self);
  return parameter;
}

// parameters : '(' (name (',' name)*)? ')'
static Arcadia_List*
onParameters
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{ 
  Arcadia_List* parameters = Arcadia_List_create(process);
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    Arcadia_String* parameter = NULL;
    if (is(self, Arcadia_Mil_TokenType_Name)) {
      parameter = onParameter(process, self);
      Arcadia_List_appendObjectReferenceValue(process, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
        next(process, self);
      }
      while (is(self, Arcadia_Mil_TokenType_Comma)) {
        next(process, self);
        while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
          next(process, self);
        }
        parameter = onParameter(process, self);
        Arcadia_List_appendObjectReferenceValue(process, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
          next(process, self);
        }
      }
    }
    if (!is(self, Arcadia_Mil_TokenType_RightParenthesis)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  return parameters;
}

// constructorDefinition : 'constructor' ('native' string)? constructorParameters? constructorBody?
// constructorParameters : parameters
// constructorBody : '{' statements '}
static Arcadia_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(self, Arcadia_Mil_TokenType_Constructor)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  Arcadia_String* nativeName = NULL;
  if (is(self, Arcadia_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  Arcadia_List* constructorParameters = onParameters(process, self);
  Arcadia_List* constructorBody = NULL;
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    constructorBody = Arcadia_List_create(process);
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, Arcadia_Mil_TokenType_EndOfInput) && !is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(process, self);
      Arcadia_List_appendObjectReferenceValue(process, constructorBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LeftParenthesis)) {
    if (!is(self, Arcadia_Mil_TokenType_RightParenthesis)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
  }
  Arcadia_Mil_ConstructorDefinitionAst* constructorDefinitionAst = Arcadia_Mil_ConstructorDefinitionAst_create(process, nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static Arcadia_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(self, Arcadia_Mil_TokenType_Method)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  Arcadia_String* nativeName = NULL;
  if (is(self, Arcadia_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* methodName = getText(process, self);
  next(process, self);
  Arcadia_List* methodParameters = onParameters(process, self);
  Arcadia_List* methodBody = NULL;
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    methodBody = Arcadia_List_create(process);
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, Arcadia_Mil_TokenType_EndOfInput) && !is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(process, self);
      Arcadia_List_appendObjectReferenceValue(process, methodBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  Arcadia_Mil_MethodDefinitionAst* methodDefinitionAst = Arcadia_Mil_MethodDefinitionAst_create(process, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static Arcadia_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (Arcadia_Mil_TokenType_Variable != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (Arcadia_Mil_TokenType_Name != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_VariableDefinitionAst* variableDefinitionAst = Arcadia_Mil_VariableDefinitionAst_create(process, getText(process, self));
  next(process, self);
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static Arcadia_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{ 
  switch (getType(self)) {
    case Arcadia_Mil_TokenType_Constructor: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onConstructorDefinition(process, self);
    } break;
    case Arcadia_Mil_TokenType_Method: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onMethodDefinition(process, self);
    } break;
    case Arcadia_Mil_TokenType_Variable: {
      return (Arcadia_Mil_ClassMemberDefinitionAst*)onVariableDefinition(process, self);
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static Arcadia_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  if (!is(self, Arcadia_Mil_TokenType_Class)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* className = getText(process, self);
  next(process, self);
  Arcadia_String* extendedClassName = NULL;
  if (is(self, Arcadia_Mil_TokenType_Extends)) {
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    if (!is(self, Arcadia_Mil_TokenType_Name)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    extendedClassName = getText(process, self);
    next(process, self);
  }
  Arcadia_List* classBody = NULL;
  if (is(self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    classBody = Arcadia_List_create(process);  
    while (!is(self, Arcadia_Mil_TokenType_EndOfInput) && !is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_ClassMemberDefinitionAst* classMemberDefinitionAst = onClassMemberDefinition(process, self);
      Arcadia_List_appendObjectReferenceValue(process, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  Arcadia_Mil_ClassDefinitionAst* classDefinitionAst = Arcadia_Mil_ClassDefinitionAst_create(process, className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static Arcadia_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_BooleanValue entry = Arcadia_BooleanValue_False;
  if (!is(self, Arcadia_Mil_TokenType_Procedure)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (is(self, Arcadia_Mil_TokenType_Entry)) {
    next(process, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(self, Arcadia_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, Arcadia_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  if (!is(self, Arcadia_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* procedureName = getText(process, self);
  next(process, self);
  Arcadia_List* procedureParameters = onParameters(process, self);
  Arcadia_List* procedureBody = NULL;
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, Arcadia_Mil_TokenType_LeftCurlyBracket)) {
    procedureBody = Arcadia_List_create(process);
    next(process, self);
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, Arcadia_Mil_TokenType_EndOfInput) && !is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Mil_StatementAst* statementAst = onStatement(process, self);
      Arcadia_List_appendObjectReferenceValue(process, procedureBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, Arcadia_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  Arcadia_Mil_ProcedureDefinitionAst* procedureDefinitionAst = Arcadia_Mil_ProcedureDefinitionAst_create(process, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|proceduredefinition)*
static Arcadia_Mil_ModuleAst*
onModule
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{
  Arcadia_Mil_ModuleAst* moduleAst = Arcadia_Mil_ModuleAst_create(process);
  if (!is(self, Arcadia_Mil_TokenType_StartOfInput)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  while (!is(self, Arcadia_Mil_TokenType_EndOfInput)) {
    while (is(self, Arcadia_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    Arcadia_Mil_DefinitionAst* definitionAst = NULL;
    switch (getType(self)) {
      case Arcadia_Mil_TokenType_Class: {
        definitionAst = (Arcadia_Mil_DefinitionAst*)onClassDefinition(process, self);
        Arcadia_Mil_ModuleAst_appendDefinition(process, moduleAst, definitionAst);
      } break;
      case Arcadia_Mil_TokenType_Procedure: {
        definitionAst = (Arcadia_Mil_DefinitionAst*)onProcedureDefinition(process, self);
        Arcadia_Mil_ModuleAst_appendDefinition(process, moduleAst, definitionAst);
      } break;
      default: {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      } break;
    };
  }
  if (!is(self, Arcadia_Mil_TokenType_EndOfInput)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  return moduleAst;
}

Arcadia_Mil_ModuleAst*
Arcadia_Mil_Parser_run
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self
  )
{ 
  Arcadia_Mil_ModuleAst* moduleAst = onModule(process, self);
  return moduleAst;
}

void
Arcadia_Mil_Parser_setInput
  (
    Arcadia_Process* process,
    Arcadia_Mil_Parser* self,
    Arcadia_Utf8Reader* input
  )
{
  Arcadia_Mil_Scanner_setInput(process, self->scanner, input);
}
