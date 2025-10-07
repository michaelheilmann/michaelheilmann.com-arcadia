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
    Arcadia_MIL_Parser* self
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
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_Parser_constructImpl,
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
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Parser_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
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

static Arcadia_MIL_AST_OperandNode*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_AST_ExpressionNode*
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

static Arcadia_MIL_AST_StatementNode*
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

static Arcadia_MIL_AST_ConstructorDefinitionNode*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_MethodDefinitionNode*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_AST_FieldDefinitionNode*
onVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_AST_Node*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_AST_ClassDefinitionNode*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_MIL_AST_ProcedureDefinitionNode*
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
///   registerOperand
static Arcadia_MIL_AST_OperandNode*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_BooleanLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_BooleanLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_IntegerLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_IntegerLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_RealLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_RealLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_StringLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_StringLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_VoidLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_VoidLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_Name: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_VariableOperandNode_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_TokenType_Register: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static Arcadia_MIL_AST_InvokeInstructionNode*
onInvokeInstruction
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
  Arcadia_MIL_AST_VariableOperandNode* calleeAst = Arcadia_MIL_AST_VariableOperandNode_create(thread, getText(thread, self));
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
    Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
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
  Arcadia_MIL_AST_InvokeInstructionNode* invokeInstructionNode = Arcadia_MIL_AST_InvokeInstructionNode_create(thread, calleeAst, operands);
  return invokeInstructionNode;
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
//   'add' <target> ',' <first operand> ',' <second operand>
//   'and' <target> ',' <first operand> ',' <second operand>
//   'concatenate' <target> ',' <first operand> ',' <second operand>
//   'divide' <target> ',' <first operand> ',' <second operand>
//   'multiply' <target> ',' <first operand> ',' <second operand>
//   'or' <target> ',' <first operand> ',' <second operand>
//   'subtract' <target> ',' <first operand> ',' <second operand>
//   'isEqualTo' <target> ',' <first operand> ',' <second operand>
//   'isNotEqualTo' <target> ',' <first operand> ',' <second operand>
//   'isLowerThan' <target> ',' <first operand> ',' <second operand>
//   'isLowerThanOrEqualTo' <target> ',' <first operand> ',' <second operand>
//   'isGreaterThan' <target> ',' <first operand> ',' <second operand>
//   'isGreaterThanOrEqualTo' <target> ',' <first operand> ',' <second operand>
//
// unaryExpression:
//   'negate' <target> <operand>
//   'not' <target> <operand>
//   'set' <target> <operand>
static Arcadia_MIL_AST_ExpressionNode*
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
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_LoadExpressionAst_create(thread, operand);
    } break;
    // binaryExpression
    case Arcadia_MIL_TokenType_Add: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Add, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_And: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_And, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Concatenate: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Concatenate, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Divide: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Divide, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Multiply: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Multiply, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Or: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Or, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_Subtract: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Subtract, target, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_MIL_TokenType_IsEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsNotEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsNotEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsLowerThan: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsLowerThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsGreaterThan: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_TokenType_IsGreaterThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_TokenType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_BinaryExpressionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_MIL_TokenType_Negate: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Negate, target, operand);
    } break;
    case Arcadia_MIL_TokenType_Not: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Not, target, operand);
    } break;
    case Arcadia_MIL_TokenType_Invoke: {
      return (Arcadia_MIL_AST_ExpressionNode*)onInvokeInstruction(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Set: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_RegisterOperandNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"$0"));
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_ExpressionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Set, target, operand);
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
static Arcadia_MIL_AST_StatementNode*
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
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
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
    Arcadia_MIL_AST_JumpStatementNode* statementAst = Arcadia_MIL_AST_JumpStatementNode_create(thread, labelName);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  } else if (is(thread, self, Arcadia_MIL_TokenType_JumpIfTrue)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_AST_JumpStatementNode* statementAst = Arcadia_MIL_AST_JumpStatementNode_create(thread, labelName);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  } else if (is(thread, self, Arcadia_MIL_TokenType_JumpIfFalse)) {
    if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* labelName = getText(thread, self);
    next(thread, self);
    onEndOfStatement(thread, self);
    Arcadia_MIL_AST_JumpStatementNode* statementAst = Arcadia_MIL_AST_JumpStatementNode_create(thread, labelName);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  }
  // return statement
  if (is(thread, self, Arcadia_MIL_TokenType_Return)) {
    next(thread, self);
    Arcadia_MIL_AST_OperandNode* operandAst = NULL;
    if (is(thread, self, Arcadia_MIL_TokenType_BooleanLiteral) || is(thread, self, Arcadia_MIL_TokenType_IntegerLiteral) || is(thread, self, Arcadia_MIL_TokenType_RealLiteral) || is(thread, self, Arcadia_MIL_TokenType_StringLiteral) || is(thread, self, Arcadia_MIL_TokenType_Name)) {
      operandAst = onOperand(thread, self);
    }
    onEndOfStatement(thread, self);
    Arcadia_MIL_ReturnStatementAst* statementAst = Arcadia_MIL_ReturnStatementAst_create(thread, operandAst);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  }
  // variable definition statement
  if (is(thread, self, Arcadia_MIL_TokenType_Variable)) {
    Arcadia_MIL_VariableDefinitionStatementAst* statementAst = onVariableDefinitionStatement(thread, self);
    onEndOfStatement(thread, self);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  }
  if (!is(thread, self, Arcadia_MIL_TokenType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_AST_StatementNode* statementAst = NULL;
  Arcadia_String* nameString = getText(thread, self);
  next(thread, self);
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_EqualsSign: {
      next(thread, self);
      Arcadia_MIL_AST_ExpressionNode* expressionAst = onExpression(thread, self);
      statementAst = (Arcadia_MIL_AST_StatementNode*)Arcadia_MIL_ExpressionStatementAst_create(thread, nameString, expressionAst);
      onEndOfStatement(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Colon: {
      next(thread, self);
      statementAst = (Arcadia_MIL_AST_StatementNode*)Arcadia_MIL_AST_LabelStatementNode_create(thread, nameString);
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
static Arcadia_MIL_AST_ConstructorDefinitionNode*
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
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
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
  Arcadia_MIL_AST_ConstructorDefinitionNode* constructorDefinitionAst = Arcadia_MIL_AST_ConstructorDefinitionNode_create(thread, nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static Arcadia_MIL_MethodDefinitionNode*
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
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
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
  Arcadia_MIL_MethodDefinitionNode* methodDefinitionAst = Arcadia_MIL_MethodDefinitionNode_create(thread, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static Arcadia_MIL_AST_FieldDefinitionNode*
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
  Arcadia_MIL_AST_FieldDefinitionNode* variableDefinitionAst = Arcadia_MIL_AST_FieldDefinitionNode_create(thread, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_MIL_TokenType_LineTerminator)) {
    next(thread, self);
  }
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static Arcadia_MIL_AST_Node*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MIL_TokenType_Constructor: {
      return (Arcadia_MIL_AST_Node*)onConstructorDefinition(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Method: {
      return (Arcadia_MIL_AST_Node*)onMethodDefinition(thread, self);
    } break;
    case Arcadia_MIL_TokenType_Variable: {
      return (Arcadia_MIL_AST_Node*)onVariableDefinition(thread, self);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static Arcadia_MIL_AST_ClassDefinitionNode*
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
      Arcadia_MIL_AST_Node* classMemberDefinitionAst = onClassMemberDefinition(thread, self);
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
  Arcadia_MIL_AST_ClassDefinitionNode* classDefinitionAst = Arcadia_MIL_AST_ClassDefinitionNode_create(thread, className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static Arcadia_MIL_AST_ProcedureDefinitionNode*
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
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
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
  Arcadia_MIL_AST_ProcedureDefinitionNode* procedureDefinitionAst = Arcadia_MIL_AST_ProcedureDefinitionNode_create(thread, entry, nativeName, procedureName, procedureParameters, procedureBody);
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
