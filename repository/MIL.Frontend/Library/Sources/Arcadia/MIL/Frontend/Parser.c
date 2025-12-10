// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

struct Arcadia_MIL_ParserDispatch {
  Arcadia_ObjectDispatch _parent;
};

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
Arcadia_MIL_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ParserDispatch* self
  );

static void
Arcadia_MIL_Parser_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static void
Arcadia_MIL_Parser_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_MIL_WordType type
  );

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_Parser_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MIL_Parser_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Parser_visitImpl,
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
Arcadia_MIL_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ParserDispatch* self
  )
{ }

static void
Arcadia_MIL_Parser_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_Parser_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner); }

static Arcadia_MIL_WordType
getType
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ return Arcadia_Languages_Scanner_getWordType(thread, (Arcadia_Languages_Scanner*)self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{ return Arcadia_Languages_Scanner_getWordText(thread, (Arcadia_Languages_Scanner*)self->scanner); }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_MIL_WordType type
  )
{ return type == getType(thread, self); }

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_Languages_Scanner_step(thread, (Arcadia_Languages_Scanner*)self->scanner);
  while (Arcadia_MIL_WordType_WhiteSpaces == getType(thread, self) || Arcadia_MIL_WordType_SingleLineComment == getType(thread, self) || Arcadia_MIL_WordType_MultiLineComment == getType(thread, self)) {
    Arcadia_Languages_Scanner_step(thread, (Arcadia_Languages_Scanner*)self->scanner);
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

static Arcadia_MIL_AST_InstructionNode*
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

static Arcadia_MIL_AST_FieldDefinitionNode*
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
onFieldDefinition
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

static Arcadia_MIL_AST_ModuleNode*
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
    case Arcadia_MIL_WordType_BooleanLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_BooleanLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_IntegerLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_IntegerLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_RealLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_RealLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_StringLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_StringLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_VoidLiteral: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_LiteralOperandNode_create(thread, (Arcadia_MIL_AST_Node*)Arcadia_MIL_AST_VoidLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_Name: {
      Arcadia_MIL_AST_OperandNode* operandAst = (Arcadia_MIL_AST_OperandNode*)Arcadia_MIL_AST_VariableOperandNode_create(thread, getText(thread, self));
      next(thread, self);
      return operandAst;
    } break;
    case Arcadia_MIL_WordType_Register: {
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
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_AST_VariableOperandNode* calleeAst = Arcadia_MIL_AST_VariableOperandNode_create(thread, getText(thread, self));
  if (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_WordType_LeftParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_List* operands = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  if (!is(thread, self, Arcadia_MIL_WordType_EndOfInput) && !is(thread, self, Arcadia_MIL_WordType_RightParenthesis)) {
    Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(thread, self, Arcadia_MIL_WordType_Comma) || is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      if (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
        continue;
      }
      next(thread, self);
      operand = onOperand(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(thread, self, Arcadia_MIL_WordType_RightParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_MIL_AST_InvokeInstructionNode* invokeInstructionNode = Arcadia_MIL_AST_InvokeInstructionNode_create(thread, calleeAst, operands);
  return invokeInstructionNode;
}

// instruction :
//   | unaryInstruction
//   | binaryInstruction
//   | invokeInstruction
//   | jumpInstruction
//   | raiseInstruction
//   | returnInstruction
//
// raiseInstruction :
//   'raise'
// returnInstruction :
//   'return' <operand>?
//
// invokeInstruction :
//   'invoke' variableOperand '(' ( <operand> (',' <operand>)* )? ')'
//
// jumpInstruction :
//   | 'jump' <label>
//   | 'jumpIfTrue' <operand> <label>
//   | 'jumpIfFalse' <operand> <label>
//
// binaryInstruction :
//   | 'add' <target> ',' <first operand> ',' <second operand>
//   | 'and' <target> ',' <first operand> ',' <second operand>
//   | 'concatenate' <target> ',' <first operand> ',' <second operand>
//   | 'divide' <target> ',' <first operand> ',' <second operand>
//   | 'multiply' <target> ',' <first operand> ',' <second operand>
//   | 'or' <target> ',' <first operand> ',' <second operand>
//   | 'subtract' <target> ',' <first operand> ',' <second operand>
//   | 'isEqualTo' <target> ',' <first operand> ',' <second operand>
//   | 'isNotEqualTo' <target> ',' <first operand> ',' <second operand>
//   | 'isLowerThan' <target> ',' <first operand> ',' <second operand>
//   | 'isLowerThanOrEqualTo' <target> ',' <first operand> ',' <second operand>
//   | 'isGreaterThan' <target> ',' <first operand> ',' <second operand>
//   | 'isGreaterThanOrEqualTo' <target> ',' <first operand> ',' <second operand>
//
// unaryInstruction:
//   | 'negate' <target> <operand>
//   | 'not' <target> <operand>
//   | 'set' <target> <operand>
static Arcadia_MIL_AST_InstructionNode*
onInstruction
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  switch (getType(thread, self)) {
    // binaryExpression
    case Arcadia_MIL_WordType_Add: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Add, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_And: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_And, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_Concatenate: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Concatenate, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_Divide: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Divide, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_Multiply: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Multiply, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_Or: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Or, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_Subtract: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_Subtract, target, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_MIL_WordType_IsEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_IsNotEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsNotEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_IsLowerThan: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_IsLowerThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_IsGreaterThan: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MIL_WordType_IsGreaterThanOrEqualTo: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_BinaryInstructionNode_create(thread, Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_MIL_WordType_Negate: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Negate, target, operand);
    } break;
    case Arcadia_MIL_WordType_Not: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Not, target, operand);
    } break;
    case Arcadia_MIL_WordType_Invoke: {
      return (Arcadia_MIL_AST_InstructionNode*)onInvokeInstruction(thread, self);
    } break;
    case Arcadia_MIL_WordType_Set: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_UnaryInstructionNode_create(thread, Arcadia_MIL_AST_UnaryInstructionKind_Set, target, operand);
    } break;
    case Arcadia_MIL_WordType_Raise: {
      next(thread, self);
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_RaiseInstructionNode_create(thread);
    } break;
    case Arcadia_MIL_WordType_Return: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = NULL;
      if (is(thread, self, Arcadia_MIL_WordType_BooleanLiteral) || is(thread, self, Arcadia_MIL_WordType_IntegerLiteral) || is(thread, self, Arcadia_MIL_WordType_RealLiteral) || is(thread, self, Arcadia_MIL_WordType_StringLiteral) || is(thread, self, Arcadia_MIL_WordType_Name)) {
        operand = onOperand(thread, self);
      }
      return (Arcadia_MIL_AST_InstructionNode*)Arcadia_MIL_AST_ReturnInstructionNode_create(thread, operand);
    } break;
    case Arcadia_MIL_WordType_Jump: {
      next(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      onEndOfStatement(thread, self);
      Arcadia_MIL_AST_JumpInstructionNode* jumpNode = Arcadia_MIL_AST_JumpInstructionNode_create(thread, labelName);
      return (Arcadia_MIL_AST_InstructionNode*)jumpNode;
    } break;
    case Arcadia_MIL_WordType_JumpIfFalse: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      Arcadia_MIL_AST_JumpInstructionNode* jumpNode = Arcadia_MIL_AST_JumpInstructionNode_create(thread, labelName);
      operand = NULL;
      return (Arcadia_MIL_AST_InstructionNode*)jumpNode;
    } break;
    case Arcadia_MIL_WordType_JumpIfTrue: {
      next(thread, self);
      Arcadia_MIL_AST_OperandNode* operand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      Arcadia_MIL_AST_JumpInstructionNode* jumpNode = Arcadia_MIL_AST_JumpInstructionNode_create(thread, labelName);
      operand = NULL;
      return (Arcadia_MIL_AST_InstructionNode*)jumpNode;
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
  if (is(thread, self, Arcadia_MIL_WordType_EndOfInput)) {
    return;
  }
  if (!is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket) && !is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
}

// instructionStatement : instruction endOfStatement
static Arcadia_MIL_AST_InstructionStatementNode*
onInstructionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_AST_InstructionNode* instruction = onInstruction(thread, self);
  Arcadia_MIL_AST_InstructionStatementNode* statement = (Arcadia_MIL_AST_InstructionStatementNode*)instruction;
  onEndOfStatement(thread, self);
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  return statement;
}

/// variableDefinitionStatement : 'variable' name endOfStatement
static Arcadia_MIL_VariableDefinitionStatementNode*
onVariableDefinitionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (Arcadia_MIL_WordType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MIL_WordType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_VariableDefinitionStatementNode* statement = Arcadia_MIL_VariableDefinitionStatementNode_create(thread, getText(thread, self));
  next(thread, self);
  onEndOfStatement(thread, self);
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  return statement;
}

/// statement : instructionStatement
///           | labelDefinitionStatement endOfStatement?
///           | variableDefinitionStatement
///           | emptyStatement endOfStatement
/// labelDefinitionStatement : name ':'
static Arcadia_MIL_AST_StatementNode*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  // skip empty statement
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  // variableDefinitionStatement : 'variable' name
  if (is(thread, self, Arcadia_MIL_WordType_Variable)) {
    Arcadia_MIL_VariableDefinitionStatementNode* statementAst = onVariableDefinitionStatement(thread, self);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  }
  // labelDefinitionStatement : name ':'
  if (is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_MIL_AST_StatementNode* statementAst = NULL;
    Arcadia_String* name = getText(thread, self);
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_WordType_Colon)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
    statementAst = (Arcadia_MIL_AST_StatementNode*)Arcadia_MIL_AST_LabelDefinitionStatementNode_create(thread, name);
    onEndOfStatement(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    return statementAst;
  }
  // instruction statement
  {
    Arcadia_MIL_AST_InstructionStatementNode* statementAst = onInstructionStatement(thread, self);
    return (Arcadia_MIL_AST_StatementNode*)statementAst;
  }
}

// parameter : <name> ':' <type>
// <name> : lexical.name
// <type> : lexical.name
static Arcadia_MIL_AST_FieldDefinitionNode*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MIL_WordType_Variable)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* name = getText(thread, self);
  next(thread, self);
  if (!is(thread, self, Arcadia_MIL_WordType_Colon)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* type = getText(thread, self);
  next(thread, self);
  return Arcadia_MIL_AST_FieldDefinitionNode_create(thread, name, type);
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
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LeftParenthesis)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_MIL_AST_FieldDefinitionNode* parameter = NULL;
    if (is(thread, self, Arcadia_MIL_WordType_Variable)) {
      parameter = onParameter(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
        next(thread, self);
      }
      while (is(thread, self, Arcadia_MIL_WordType_Comma)) {
        next(thread, self);
        while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
          next(thread, self);
        }
        parameter = onParameter(thread, self);
        Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
          next(thread, self);
        }
      }
    }
    if (!is(thread, self, Arcadia_MIL_WordType_RightParenthesis)) {
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
  if (!is(thread, self, Arcadia_MIL_WordType_Constructor)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* constructorParameters = onParameters(thread, self);
  Arcadia_List* constructorBody = NULL;
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LeftCurlyBracket)) {
    constructorBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_WordType_EndOfInput) && !is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, constructorBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LeftParenthesis)) {
    if (!is(thread, self, Arcadia_MIL_WordType_RightParenthesis)) {
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
  if (!is(thread, self, Arcadia_MIL_WordType_Method)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* methodName = getText(thread, self);
  next(thread, self);
  Arcadia_List* methodParameters = onParameters(thread, self);
  Arcadia_List* methodBody = NULL;
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LeftCurlyBracket)) {
    methodBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_WordType_EndOfInput) && !is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, methodBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_MethodDefinitionNode* methodDefinitionAst = Arcadia_MIL_MethodDefinitionNode_create(thread, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' name ':' type
static Arcadia_MIL_AST_FieldDefinitionNode*
onFieldDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  if (Arcadia_MIL_WordType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MIL_WordType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* name = getText(thread, self);
  next(thread, self);
  if (Arcadia_MIL_WordType_Colon != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* type = getText(thread, self);
  next(thread, self);
  Arcadia_MIL_AST_FieldDefinitionNode* variableDefinitionAst = Arcadia_MIL_AST_FieldDefinitionNode_create(thread, name, type);
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
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
    case Arcadia_MIL_WordType_Constructor: {
      return (Arcadia_MIL_AST_Node*)onConstructorDefinition(thread, self);
    } break;
    case Arcadia_MIL_WordType_Method: {
      return (Arcadia_MIL_AST_Node*)onMethodDefinition(thread, self);
    } break;
    case Arcadia_MIL_WordType_Variable: {
      return (Arcadia_MIL_AST_Node*)onFieldDefinition(thread, self);
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
  if (!is(thread, self, Arcadia_MIL_WordType_Class)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* className = getText(thread, self);
  next(thread, self);
  Arcadia_String* extendedClassName = NULL;
  if (is(thread, self, Arcadia_MIL_WordType_Extends)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    extendedClassName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* classBody = NULL;
  if (is(thread, self, Arcadia_MIL_WordType_LeftCurlyBracket)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    classBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    while (!is(thread, self, Arcadia_MIL_WordType_EndOfInput) && !is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_MIL_AST_Node* classMemberDefinitionAst = onClassMemberDefinition(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
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
  if (!is(thread, self, Arcadia_MIL_WordType_Procedure)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MIL_WordType_Entry)) {
    next(thread, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MIL_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MIL_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MIL_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* procedureName = getText(thread, self);
  next(thread, self);
  Arcadia_List* procedureParameters = onParameters(thread, self);
  Arcadia_List* procedureBody = NULL;
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MIL_WordType_LeftCurlyBracket)) {
    procedureBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MIL_WordType_EndOfInput) && !is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_MIL_AST_StatementNode* statementAst = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, procedureBody, (Arcadia_ObjectReferenceValue)statementAst);
    }
    if (!is(thread, self, Arcadia_MIL_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MIL_AST_ProcedureDefinitionNode* procedureDefinitionAst = Arcadia_MIL_AST_ProcedureDefinitionNode_create(thread, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|enumerationDefinition|proceduredefinition)*
static Arcadia_MIL_AST_ModuleNode*
onModule
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_AST_ModuleNode* moduleAst = Arcadia_MIL_AST_ModuleNode_create(thread);
  if (!is(thread, self, Arcadia_MIL_WordType_StartOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (!is(thread, self, Arcadia_MIL_WordType_EndOfInput)) {
    while (is(thread, self, Arcadia_MIL_WordType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_MIL_DefinitionAst* definitionAst = NULL;
    switch (getType(thread, self)) {
      case Arcadia_MIL_WordType_Class: {
        definitionAst = (Arcadia_MIL_DefinitionAst*)onClassDefinition(thread, self);
        Arcadia_MIL_AST_ModuleNode_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      case Arcadia_MIL_WordType_Procedure: {
        definitionAst = (Arcadia_MIL_DefinitionAst*)onProcedureDefinition(thread, self);
        Arcadia_MIL_AST_ModuleNode_appendDefinition(thread, moduleAst, definitionAst);
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
  if (!is(thread, self, Arcadia_MIL_WordType_EndOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return moduleAst;
}

Arcadia_MIL_AST_ModuleNode*
Arcadia_MIL_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self
  )
{
  Arcadia_MIL_AST_ModuleNode* moduleAst = onModule(thread, self);
  return moduleAst;
}

void
Arcadia_MIL_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Parser* self,
    Arcadia_String* input
  )
{
  Arcadia_Languages_Scanner_setInput(thread, (Arcadia_Languages_Scanner*)self->scanner, input);
}
