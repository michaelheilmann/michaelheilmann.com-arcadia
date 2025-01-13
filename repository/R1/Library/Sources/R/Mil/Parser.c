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

struct R_Mil_Parser {
  Arcadia_Object _parent;
  // The index of the Byte in the input stream at which the current symbol starts.
  R_Mil_Scanner* scanner;
};

static void
R_Mil_Parser_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Mil_Parser_destruct
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static void
R_Mil_Parser_visit
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    R_Mil_Parser* self,
    R_Mil_TokenType type
  );

static void
next
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_Parser_constructImpl,
  .destruct = &R_Mil_Parser_destruct,
  .visit = &R_Mil_Parser_visit,
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

Rex_defineObjectType(u8"R.Mil.Parser", R_Mil_Parser, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Mil_Parser_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Mil_Parser* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_Parser_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->scanner = R_Mil_Scanner_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_Mil_Parser_destruct
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{/*Intentionally empty.*/}

static void
R_Mil_Parser_visit
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{ Arcadia_Object_visit(process, self->scanner); }

static R_Mil_TokenType
getType
  (
    R_Mil_Parser* self
  )
{ return R_Mil_Scanner_getTokenType(self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{ return R_Mil_Scanner_getTokenText(process, self->scanner); }

static Arcadia_BooleanValue
is
  (
    R_Mil_Parser* self,
    R_Mil_TokenType type
  )
{ return type == getType(self); }

static void
next
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  R_Mil_Scanner_step(process, self->scanner);
  while (R_Mil_TokenType_WhiteSpaces == getType(self) || R_Mil_TokenType_SingleLineComment == getType(self) || R_Mil_TokenType_MultiLineComment == getType(self)) {
    R_Mil_Scanner_step(process, self->scanner);
  }
}

R_Mil_Parser*
R_Mil_Parser_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Mil_Parser* self = R_allocateObject(process, _R_Mil_Parser_getType(process), 0, &argumentValues[0]);
  return self;
}

static R_Mil_OperandAst*
onOperand
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ExpressionAst*
onExpression
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static void
onEndOfStatement
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_StatementAst*
onStatement
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static Arcadia_String*
onParameter
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_List*
onParameters
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

static R_Mil_ModuleAst*
onModule
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
static R_Mil_OperandAst*
onOperand
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  switch (getType(self)) {
    case R_Mil_TokenType_BooleanLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_BooleanLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case R_Mil_TokenType_IntegerLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_IntegerLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case R_Mil_TokenType_RealLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_RealLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case R_Mil_TokenType_StringLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_StringLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case R_Mil_TokenType_VoidLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_VoidLiteralOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    case R_Mil_TokenType_Name: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_VariableOperandAst_create(process, getText(process, self));
      next(process, self);
      return operandAst;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  };
}

static R_Mil_InvokeExpressionAst*
onInvokeExpression
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  next(process, self);
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  R_Mil_VariableOperandAst* calleeAst = R_Mil_VariableOperandAst_create(process, getText(process, self));
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (!is(self, R_Mil_TokenType_LeftParenthesis)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  R_List* operands = R_List_create(process);
  if (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightParenthesis)) {
    R_Mil_OperandAst* operand = onOperand(process, self);
    R_List_appendObjectReferenceValue(process, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(self, R_Mil_TokenType_Comma) || is(self, R_Mil_TokenType_LineTerminator)) {
      if (is(self, R_Mil_TokenType_LineTerminator)) {
        continue;
      }
      next(process, self);
      operand = onOperand(process, self);
      R_List_appendObjectReferenceValue(process, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(self, R_Mil_TokenType_RightParenthesis)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  R_Mil_InvokeExpressionAst* invokeExpressionAst = R_Mil_InvokeExpressionAst_create(process, calleeAst, operands);
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
//   
// unaryExpression:
//   <op1>
//   'negate' <op1>
//   'not' <op1>
static R_Mil_ExpressionAst*
onExpression
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  switch (getType(self)) {
    // constantExpression
    case R_Mil_TokenType_BooleanLiteral:
    case R_Mil_TokenType_IntegerLiteral:
    case R_Mil_TokenType_RealLiteral:
    case R_Mil_TokenType_StringLiteral:
    case R_Mil_TokenType_VoidLiteral: 
    case R_Mil_TokenType_Name: {
      R_Mil_OperandAst* operand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_LoadExpressionAst_create(process, operand);
    } break;
    // binaryExpression
    case R_Mil_TokenType_Add: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_And: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_And, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Concatenate: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Divide: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Multiply: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Or: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Or, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Subtract: {
      next(process, self);
      R_Mil_OperandAst* firstOperand = onOperand(process, self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      }
      next(process, self);
      R_Mil_OperandAst* secondOperand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(process, R_Mil_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case R_Mil_TokenType_Negate: {
      next(process, self);
      R_Mil_OperandAst* operand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_UnaryExpressionAst_create(process, R_Mil_UnaryExpressionAstType_Negate, operand);
    } break;
    case R_Mil_TokenType_Not: {
      next(process, self);
      R_Mil_OperandAst* operand = onOperand(process, self);
      return (R_Mil_ExpressionAst*)R_Mil_UnaryExpressionAst_create(process, R_Mil_UnaryExpressionAstType_Not, operand);
    } break;
    case R_Mil_TokenType_Invoke: {
      return (R_Mil_ExpressionAst*)onInvokeExpression(process, self);
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
    R_Mil_Parser* self
  )
{
  if (is(self, R_Mil_TokenType_EndOfInput)) {
    return;
  }
  if (!is(self, R_Mil_TokenType_RightCurlyBracket) && !is(self, R_Mil_TokenType_LineTerminator)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
}

static R_Mil_VariableDefinitionStatementAst*
onVariableDefinitionStatement
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  if (R_Mil_TokenType_Variable != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (R_Mil_TokenType_Name != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  R_Mil_VariableDefinitionStatementAst* variableDefinitionStatementAst = R_Mil_VariableDefinitionStatementAst_create(process, getText(process, self));
  next(process, self);
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  return variableDefinitionStatementAst;
}

/// statement : expressionStatement endOfStatement
///           | labelStatement endOfStatement?
///           | returnStatement endOfStatement
///           | emptyStatement endOfStatement
/// expressionStatement: name '=' expression
/// labelStatement: name ':'
/// variableDefinitionStatement : variableDefinition
/// returnStatement : 'return' operand?
static R_Mil_StatementAst*
onStatement
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  // skip empty statement 
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  // return statement
  if (is(self, R_Mil_TokenType_Return)) {
    next(process, self);
    R_Mil_OperandAst* operandAst = NULL;
    if (is(self, R_Mil_TokenType_BooleanLiteral) || is(self, R_Mil_TokenType_IntegerLiteral) || is(self, R_Mil_TokenType_RealLiteral) || is(self, R_Mil_TokenType_StringLiteral) || is(self, R_Mil_TokenType_Name)) {
      operandAst = onOperand(process, self);
    }
    onEndOfStatement(process, self);
    R_Mil_ReturnStatementAst* statementAst = R_Mil_ReturnStatementAst_create(process, operandAst);
    return (R_Mil_StatementAst*)statementAst;
  }
  // variable definition statement
  if (is(self, R_Mil_TokenType_Variable)) {
    R_Mil_VariableDefinitionStatementAst* statementAst = onVariableDefinitionStatement(process, self);
    onEndOfStatement(process, self);
    return (R_Mil_StatementAst*)statementAst;
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  R_Mil_StatementAst* statementAst = NULL;
  Arcadia_String* nameString = getText(process, self);
  next(process, self);
  switch (getType(self)) {
    case R_Mil_TokenType_EqualsSign: {
      next(process, self);
      R_Mil_ExpressionAst* expressionAst = onExpression(process, self);
      statementAst = (R_Mil_StatementAst*)R_Mil_ExpressionStatementAst_create(process, nameString, expressionAst);
      onEndOfStatement(process, self);
    } break;
    case R_Mil_TokenType_Colon: {
      next(process, self);
      statementAst = (R_Mil_StatementAst*)R_Mil_LabelStatementAst_create(process, nameString);
      // statement terminator injection
      if (is(self, R_Mil_TokenType_EndOfInput) || is(self, R_Mil_TokenType_LineTerminator) || is(self, R_Mil_TokenType_RightCurlyBracket)) {
        if (is(self, R_Mil_TokenType_LineTerminator) || is(self, R_Mil_TokenType_RightCurlyBracket)) {
          next(process, self);
        }
      }
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  return statementAst;
}

static Arcadia_String*
onParameter
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  ) 
{
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* parameter = getText(process, self);
  next(process, self);
  return parameter;
}

// parameters : '(' (name (',' name)*)? ')'
static R_List*
onParameters
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{ 
  R_List* parameters = R_List_create(process);
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LeftParenthesis)) {
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    Arcadia_String* parameter = NULL;
    if (is(self, R_Mil_TokenType_Name)) {
      parameter = onParameter(process, self);
      R_List_appendObjectReferenceValue(process, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(self, R_Mil_TokenType_LineTerminator)) {
        next(process, self);
      }
      while (is(self, R_Mil_TokenType_Comma)) {
        next(process, self);
        while (is(self, R_Mil_TokenType_LineTerminator)) {
          next(process, self);
        }
        parameter = onParameter(process, self);
        R_List_appendObjectReferenceValue(process, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(self, R_Mil_TokenType_LineTerminator)) {
          next(process, self);
        }
      }
    }
    if (!is(self, R_Mil_TokenType_RightParenthesis)) {
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
static R_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Constructor)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  Arcadia_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  R_List* constructorParameters = onParameters(process, self);
  R_List* constructorBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    constructorBody = R_List_create(process);
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(process, self);
      R_List_appendObjectReferenceValue(process, constructorBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LeftParenthesis)) {
    if (!is(self, R_Mil_TokenType_RightParenthesis)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
  }
  R_Mil_ConstructorDefinitionAst* constructorDefinitionAst = R_Mil_ConstructorDefinitionAst_create(process, nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static R_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Method)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  Arcadia_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* methodName = getText(process, self);
  next(process, self);
  R_List* methodParameters = onParameters(process, self);
  R_List* methodBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    methodBody = R_List_create(process);
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(process, self);
      R_List_appendObjectReferenceValue(process, methodBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  R_Mil_MethodDefinitionAst* methodDefinitionAst = R_Mil_MethodDefinitionAst_create(process, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static R_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  if (R_Mil_TokenType_Variable != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (R_Mil_TokenType_Name != getType(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  R_Mil_VariableDefinitionAst* variableDefinitionAst = R_Mil_VariableDefinitionAst_create(process, getText(process, self));
  next(process, self);
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static R_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{ 
  switch (getType(self)) {
    case R_Mil_TokenType_Constructor: {
      return (R_Mil_ClassMemberDefinitionAst*)onConstructorDefinition(process, self);
    } break;
    case R_Mil_TokenType_Method: {
      return (R_Mil_ClassMemberDefinitionAst*)onMethodDefinition(process, self);
    } break;
    case R_Mil_TokenType_Variable: {
      return (R_Mil_ClassMemberDefinitionAst*)onVariableDefinition(process, self);
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static R_Mil_ClassDefinitionAst*
onClassDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Class)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* className = getText(process, self);
  next(process, self);
  Arcadia_String* extendedClassName = NULL;
  if (is(self, R_Mil_TokenType_Extends)) {
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    if (!is(self, R_Mil_TokenType_Name)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    extendedClassName = getText(process, self);
    next(process, self);
  }
  R_List* classBody = NULL;
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    classBody = R_List_create(process);  
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_ClassMemberDefinitionAst* classMemberDefinitionAst = onClassMemberDefinition(process, self);
      R_List_appendObjectReferenceValue(process, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  R_Mil_ClassDefinitionAst* classDefinitionAst = R_Mil_ClassDefinitionAst_create(process, className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static R_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  Arcadia_BooleanValue entry = Arcadia_BooleanValue_False;
  if (!is(self, R_Mil_TokenType_Procedure)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  if (is(self, R_Mil_TokenType_Entry)) {
    next(process, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(process, self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    nativeName = getText(process, self);
    next(process, self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* procedureName = getText(process, self);
  next(process, self);
  R_List* procedureParameters = onParameters(process, self);
  R_List* procedureBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    procedureBody = R_List_create(process);
    next(process, self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(process, self);
      R_List_appendObjectReferenceValue(process, procedureBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
      Arcadia_Process_jump(process);
    }
    next(process, self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(process, self);
  }
  R_Mil_ProcedureDefinitionAst* procedureDefinitionAst = R_Mil_ProcedureDefinitionAst_create(process, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|proceduredefinition)*
static R_Mil_ModuleAst*
onModule
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{
  R_Mil_ModuleAst* moduleAst = R_Mil_ModuleAst_create(process);
  if (!is(self, R_Mil_TokenType_StartOfInput)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  next(process, self);
  while (!is(self, R_Mil_TokenType_EndOfInput)) {
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(process, self);
    }
    R_Mil_DefinitionAst* definitionAst = NULL;
    switch (getType(self)) {
      case R_Mil_TokenType_Class: {
        definitionAst = (R_Mil_DefinitionAst*)onClassDefinition(process, self);
        R_Mil_ModuleAst_appendDefinition(process, moduleAst, definitionAst);
      } break;
      case R_Mil_TokenType_Procedure: {
        definitionAst = (R_Mil_DefinitionAst*)onProcedureDefinition(process, self);
        R_Mil_ModuleAst_appendDefinition(process, moduleAst, definitionAst);
      } break;
      default: {
        Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
        Arcadia_Process_jump(process);
      } break;
    };
  }
  if (!is(self, R_Mil_TokenType_EndOfInput)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SyntacticalError);
    Arcadia_Process_jump(process);
  }
  return moduleAst;
}

R_Mil_ModuleAst*
R_Mil_Parser_run
  (
    Arcadia_Process* process,
    R_Mil_Parser* self
  )
{ 
  R_Mil_ModuleAst* moduleAst = onModule(process, self);
  return moduleAst;
}

void
R_Mil_Parser_setInput
  (
    Arcadia_Process* process,
    R_Mil_Parser* self,
    R_Utf8Reader* input
  )
{
  R_Mil_Scanner_setInput(process, self->scanner, input);
}
