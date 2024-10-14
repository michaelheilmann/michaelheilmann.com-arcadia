// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Cilc/Parser.h"

#include "Cilc/Scanner.h"
#include "Cilc/Ast.h"

struct Cil_Parser {
  R_Object _parent;
  // The index of the Byte in the input stream at which the current symbol starts.
  Cil_Scanner* scanner;
};

static void
Cil_Parser_destruct
  (
    Cil_Parser* self
  );

static void
Cil_Parser_visit
  (
    Cil_Parser* self
  );

static R_BooleanValue
is
  (
    Cil_Parser* self,
    Cil_TokenType type
  );

static void
next
  (
    Cil_Parser* self
  );

static void
Cil_Parser_destruct
  (
    Cil_Parser* self
  )
{/*Intentionally empty.*/}

static void
Cil_Parser_visit
  (
    Cil_Parser* self
  )
{
  R_Object_visit(self->scanner);
}

static Cil_TokenType
getType
  (
    Cil_Parser* self
  )
{ return Cil_Scanner_getTokenType(self->scanner); }

static R_String*
getText
  (
    Cil_Parser* self
  )
{ return Cil_Scanner_getTokenText(self->scanner); }

static R_BooleanValue
is
  (
    Cil_Parser* self,
    Cil_TokenType type
  )
{ return type == getType(self); }

static void
next
  (
    Cil_Parser* self
  )
{
  Cil_Scanner_step(self->scanner);
  while (Cil_TokenType_WhiteSpaces == getType(self) || Cil_TokenType_SingleLineComment == getType(self) || Cil_TokenType_MultiLineComment == getType(self)) {
    Cil_Scanner_step(self->scanner);
  }
}

Rex_defineObjectType("Cil.Parser", Cil_Parser, "R.Object", R_Object, &Cil_Parser_visit, &Cil_Parser_destruct);

void
Cil_Parser_construct
  (
    Cil_Parser* self
  )
{
  R_Type* _type = _Cil_Parser_getType();
  R_Object_construct((R_Object*)self);
  self->scanner = Cil_Scanner_create();
  R_Object_setType((R_Object*)self, _type);
}

Cil_Parser*
Cil_Parser_create
  (
  )
{
  Cil_Parser* self = R_allocateObject(_Cil_Parser_getType());
  Cil_Parser_construct(self);
  return self;
}

static Cil_OperandAst*
onOperand
  (
    Cil_Parser* self
  );

static Cil_ExpressionAst*
onExpression
  (
    Cil_Parser* self
  );

static Cil_StatementAst*
onStatement
  (
    Cil_Parser* self
  );

static Cil_ProgramAst*
onProgram
  (
    Cil_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
static Cil_OperandAst*
onOperand
  (
    Cil_Parser* self
  )
{
  switch (getType(self)) {
    case Cil_TokenType_BooleanLiteral: {
      Cil_OperandAst* operandAst = (Cil_OperandAst*)Cil_BooleanLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case Cil_TokenType_NumberLiteral: {
      Cil_OperandAst* operandAst = (Cil_OperandAst*)Cil_NumberLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case Cil_TokenType_StringLiteral: {
      Cil_OperandAst* operandAst = (Cil_OperandAst*)Cil_StringLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case Cil_TokenType_VoidLiteral: {
      Cil_OperandAst* operandAst = (Cil_OperandAst*)Cil_VoidLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case Cil_TokenType_Name: {
      Cil_OperandAst* operandAst = (Cil_OperandAst*)Cil_VariableOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  };
}

/// expression :
///   unaryExpression
///   binaryExpression
///   
/// binaryExpression :
///   'add' <op1>, <op2>
///   'concatenate' <op1>, <op2>
///   'divide' <op1>, <op2>
///   'multiply' <op1>, <op2>
///   'subtract' <op1>, <op2>
///
/// unaryExpression:
///   'load' <op1>
///   'negate' <op1>
///   'not' <op1>
static Cil_ExpressionAst*
onExpression
  (
    Cil_Parser* self
  )
{
  switch (getType(self)) {
    // constantExpression
    case Cil_TokenType_BooleanLiteral:
    case Cil_TokenType_NumberLiteral:
    case Cil_TokenType_StringLiteral:
    case Cil_TokenType_VoidLiteral: 
    case Cil_TokenType_Name: {
      Cil_OperandAst* operand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_LoadExpressionAst_create(operand);
    } break;
    // binaryExpression
    case Cil_TokenType_Add: {
      next(self);
      Cil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, Cil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      Cil_OperandAst* secondOperand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_BinaryExpressionAst_create(Cil_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case Cil_TokenType_Concatenate: {
      next(self);
      Cil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, Cil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      Cil_OperandAst* secondOperand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_BinaryExpressionAst_create(Cil_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case Cil_TokenType_Divide: {
      next(self);
      Cil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, Cil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      Cil_OperandAst* secondOperand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_BinaryExpressionAst_create(Cil_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case Cil_TokenType_Multiply: {
      next(self);
      Cil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, Cil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      Cil_OperandAst* secondOperand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_BinaryExpressionAst_create(Cil_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case Cil_TokenType_Subtract: {
      next(self);
      Cil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, Cil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      Cil_OperandAst* secondOperand = onOperand(self);
      return (Cil_ExpressionAst*)Cil_BinaryExpressionAst_create(Cil_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Cil_TokenType_Negate: {
      next(self);
      Cil_OperandAst* operand = NULL;
      return (Cil_ExpressionAst*)Cil_UnaryExpressionAst_create(Cil_UnaryExpressionAstType_Negate, operand);
    } break;
    case Cil_TokenType_Not: {
      next(self);
      Cil_OperandAst* operand = NULL;
      return (Cil_ExpressionAst*)Cil_UnaryExpressionAst_create(Cil_UnaryExpressionAstType_Not, operand);
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  }
}

static Cil_StatementAst*
onStatement
  (
    Cil_Parser* self
  )
{
  // empty statements 
  while (is(self, Cil_TokenType_LineTerminator)) {
    next(self);
  }
  if (!is(self, Cil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  Cil_StatementAst* statementAst = NULL;
  R_String* nameString = getText(self);
  next(self);
  switch (getType(self)) {
    case Cil_TokenType_EqualsSign: {
      next(self);
      Cil_ExpressionAst* expressionAst = onExpression(self);
      statementAst = (Cil_StatementAst*)Cil_ExpressionStatementAst_create(nameString, expressionAst);
    } break;
    case Cil_TokenType_Colon: {
      next(self);
      statementAst = (Cil_StatementAst*)Cil_LabelStatementAst_create(nameString);
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  }
  while (is(self, Cil_TokenType_LineTerminator)) {
    next(self);
  }
  return NULL;
}

/// program : statement*
/// statement : expressionStatement
///           | labelStatement
/// expressionStatement: name '=' expression 
/// labelStatement: name ':'
static Cil_ProgramAst*
onProgram
  (
    Cil_Parser* self
  )
{
  Cil_ProgramAst* program = Cil_ProgramAst_create();
  if (!is(self, Cil_TokenType_StartOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  while (!is(self, Cil_TokenType_EndOfInput)) {
    Cil_StatementAst* statement = onStatement(self);
  }
  if (!is(self, Cil_TokenType_EndOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  return program;
}

void
Cil_Parser_run
  (
    Cil_Parser* self
  )
{ 
  Cil_ProgramAst* program = onProgram(self);
}

void
Cil_Parser_setInput
  (
    Cil_Parser* self,
    R_Utf8Reader* input
  )
{
  Cil_Scanner_setInput(self->scanner, input);
}
