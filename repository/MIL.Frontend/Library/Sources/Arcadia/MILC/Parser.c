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

#define ARCADIA_MILC_PRIVATE (1)
#include "Arcadia/MILC/Parser.h"

#include "Arcadia/MILC/Include.h"
#include "Arcadia/MILC/AST/Include.h"
#include <assert.h>

struct Arcadia_MILC_ParserDispatch {
  Arcadia_Languages_ParserDispatch _parent;
};

struct Arcadia_MILC_Parser {
  Arcadia_Languages_Parser _parent;

  Arcadia_MILC_Context* context;

  Arcadia_Languages_StringTable* stringTable;
  Arcadia_Languages_Diagnostics* diagnostics;
  Arcadia_MILC_Scanner* scanner;
};

static void
Arcadia_MILC_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static void
Arcadia_MILC_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_ParserDispatch* self
  );

static void
Arcadia_MILC_Parser_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static void
Arcadia_MILC_Parser_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self,
    Arcadia_MILC_WordType type
  );

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_Value
Arcadia_MILC_Parser_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self,
    Arcadia_RuntimeByteArray* input
  );

static Arcadia_Languages_StringTable*
Arcadia_MILC_Parser_getStringTableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_Languages_Diagnostics*
Arcadia_MILC_Parser_getDiagnosticsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_Parser_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_Parser_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_Parser_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_Parser_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Parser", Arcadia_MILC_Parser,
                         u8"Arcadia.Languages.Parser", Arcadia_Languages_Parser,
                         &_typeOperations);

static void
Arcadia_MILC_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Parser);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->context = (Arcadia_MILC_Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_Context_getType(thread));
  self->scanner = self->context->scanner;
  self->stringTable = self->context->stringTable;
  self->diagnostics = self->context->diagnostics;
  Arcadia_LeaveConstructor(Arcadia_MILC_Parser);
}

static void
Arcadia_MILC_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_ParserDispatch* self
  )
{
  ((Arcadia_Languages_ParserDispatch*)self)->run = (Arcadia_Value (*)(Arcadia_Thread*, Arcadia_Languages_Parser*, Arcadia_RuntimeByteArray*)) & Arcadia_MILC_Parser_runImpl;
  ((Arcadia_Languages_ParserDispatch*)self)->getStringTable = (Arcadia_Languages_StringTable * (*)(Arcadia_Thread*, Arcadia_Languages_Parser*)) & Arcadia_MILC_Parser_getStringTableImpl;
  ((Arcadia_Languages_ParserDispatch*)self)->getDiagnostics = (Arcadia_Languages_Diagnostics * (*)(Arcadia_Thread*, Arcadia_Languages_Parser*)) & Arcadia_MILC_Parser_getDiagnosticsImpl;
}

static void
Arcadia_MILC_Parser_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_Parser_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (self->context) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  }
  if (self->stringTable) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->stringTable);
  }
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics);
  }
  if (self->scanner) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner);
  }
}

static Arcadia_MILC_WordType
getType
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{ return Arcadia_Languages_Scanner_getWordType(thread, (Arcadia_Languages_Scanner*)self->scanner); }

static Arcadia_String*
getText
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{ return Arcadia_Languages_Scanner_getWordText(thread, (Arcadia_Languages_Scanner*)self->scanner); }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self,
    Arcadia_MILC_WordType type
  )
{ return type == getType(thread, self); }

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_Languages_Scanner_step(thread, (Arcadia_Languages_Scanner*)self->scanner);
  while (Arcadia_MILC_WordType_WhiteSpaces == getType(thread, self) || Arcadia_MILC_WordType_SingleLineComment == getType(thread, self) || Arcadia_MILC_WordType_MultiLineComment == getType(thread, self)) {
    Arcadia_Languages_Scanner_step(thread, (Arcadia_Languages_Scanner*)self->scanner);
  }
}

Arcadia_MILC_Parser*
Arcadia_MILC_Parser_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (context) Arcadia_ValueStack_pushObjectReferenceValue(thread, context); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_Parser);
}

static Arcadia_MILC_AST_OperandNode*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_IdentifierNode*
onIdentifier
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_InvokeInstructionNode*
onInvokeInstruction
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_InstructionNode*
onInstruction
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static void
onEndOfStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_StatementNode*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_FieldDefinitionNode*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_List*
onParameters
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_ConstructorDefinitionNode*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_MethodDefinitionNode*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_FieldDefinitionNode*
onFieldDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_Node*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_ClassDefinitionNode*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_Node*
onEnumerationMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_EnumerationDefinitionNode*
onEnumerationDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_ModuleDefinitionNode*
onModuleDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_ProcedureDefinitionNode*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

static Arcadia_MILC_AST_CompilationUnitNode*
onCompilationUnit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
///   registerOperand
static Arcadia_MILC_AST_OperandNode*
onOperand
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MILC_WordType_BooleanLiteral: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_LiteralOperandNode_create(thread, (Arcadia_MILC_AST_Node*)Arcadia_MILC_AST_BooleanLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_IntegerLiteral: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_LiteralOperandNode_create(thread, (Arcadia_MILC_AST_Node*)Arcadia_MILC_AST_IntegerLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_RealLiteral: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_LiteralOperandNode_create(thread, (Arcadia_MILC_AST_Node*)Arcadia_MILC_AST_RealLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_StringLiteral: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_LiteralOperandNode_create(thread, (Arcadia_MILC_AST_Node*)Arcadia_MILC_AST_StringLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_VoidLiteral: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_LiteralOperandNode_create(thread, (Arcadia_MILC_AST_Node*)Arcadia_MILC_AST_VoidLiteralNode_create(thread, getText(thread, self)));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_Name: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_VariableOperandNode_create(thread, getText(thread, self));
      next(thread, self);
      return operandNode;
    } break;
    case Arcadia_MILC_WordType_Register: {
      Arcadia_MILC_AST_OperandNode* operandNode = (Arcadia_MILC_AST_OperandNode*)Arcadia_MILC_AST_RegisterOperandNode_create(thread, getText(thread, self));
      next(thread, self);
      return operandNode;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static Arcadia_MILC_AST_IdentifierNode*
onIdentifier
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_List* names = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, names, getText(thread, self));
  next(thread, self);
  while (is(thread, self, Arcadia_MILC_WordType_Period)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_List_insertBackObjectReferenceValue(thread, names, getText(thread, self));
    next(thread, self);
  }
  Arcadia_MILC_AST_IdentifierNode* node = Arcadia_MILC_AST_IdentifierNode_create(thread, Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(names)));
  return node;
}

static Arcadia_MILC_AST_InvokeInstructionNode*
onInvokeInstruction
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  next(thread, self);
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_VariableOperandNode* calleeNode = Arcadia_MILC_AST_VariableOperandNode_create(thread, getText(thread, self));
  if (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MILC_WordType_LeftParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_List* operands = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  if (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightParenthesis)) {
    Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    while (is(thread, self, Arcadia_MILC_WordType_Comma) || is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      if (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
        continue;
      }
      next(thread, self);
      operand = onOperand(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, operands, (Arcadia_ObjectReferenceValue)operand);
    }
  }
  if (!is(thread, self, Arcadia_MILC_WordType_RightParenthesis)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_MILC_AST_InvokeInstructionNode* invokeInstructionNode = Arcadia_MILC_AST_InvokeInstructionNode_create(thread, calleeNode, operands);
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
static Arcadia_MILC_AST_InstructionNode*
onInstruction
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  switch (getType(thread, self)) {
    // binaryExpression
    case Arcadia_MILC_WordType_Add: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Add, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_And: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_And, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_Concatenate: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Concatenate, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_Divide: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Divide, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_Multiply: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Multiply, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_Or: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Or, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_Subtract: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_Subtract, target, firstOperand, secondOperand);
    } break;
    // relational operations
    case Arcadia_MILC_WordType_IsEqualTo: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_IsNotEqualTo: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsNotEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_IsLowerThan: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsLowerThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_IsLowerThanOrEqualTo: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsLowerThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_IsGreaterThan: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsGreaterThan, target, firstOperand, secondOperand);
    } break;
    case Arcadia_MILC_WordType_IsGreaterThanOrEqualTo: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* firstOperand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* secondOperand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_BinaryInstructionNode_create(thread, Arcadia_MILC_AST_BinaryInstructionKind_IsGreaterThanOrEqualTo, target, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case Arcadia_MILC_WordType_Negate: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_UnaryInstructionNode_create(thread, Arcadia_MILC_AST_UnaryInstructionKind_Negate, target, operand);
    } break;
    case Arcadia_MILC_WordType_Not: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_UnaryInstructionNode_create(thread, Arcadia_MILC_AST_UnaryInstructionKind_Not, target, operand);
    } break;
    case Arcadia_MILC_WordType_Invoke: {
      return (Arcadia_MILC_AST_InstructionNode*)onInvokeInstruction(thread, self);
    } break;
    case Arcadia_MILC_WordType_Set: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* target = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_UnaryInstructionNode_create(thread, Arcadia_MILC_AST_UnaryInstructionKind_Set, target, operand);
    } break;
    case Arcadia_MILC_WordType_Raise: {
      next(thread, self);
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_RaiseInstructionNode_create(thread);
    } break;
    case Arcadia_MILC_WordType_Return: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = NULL;
      if (is(thread, self, Arcadia_MILC_WordType_BooleanLiteral) || is(thread, self, Arcadia_MILC_WordType_IntegerLiteral) || is(thread, self, Arcadia_MILC_WordType_RealLiteral) || is(thread, self, Arcadia_MILC_WordType_StringLiteral) || is(thread, self, Arcadia_MILC_WordType_Name)) {
        operand = onOperand(thread, self);
      }
      return (Arcadia_MILC_AST_InstructionNode*)Arcadia_MILC_AST_ReturnInstructionNode_create(thread, operand);
    } break;
    case Arcadia_MILC_WordType_Jump: {
      next(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      onEndOfStatement(thread, self);
      Arcadia_MILC_AST_JumpInstructionNode* jumpNode = Arcadia_MILC_AST_JumpInstructionNode_create(thread, labelName);
      return (Arcadia_MILC_AST_InstructionNode*)jumpNode;
    } break;
    case Arcadia_MILC_WordType_JumpIfFalse: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      Arcadia_MILC_AST_JumpInstructionNode* jumpNode = Arcadia_MILC_AST_JumpInstructionNode_create(thread, labelName);
      operand = NULL;
      return (Arcadia_MILC_AST_InstructionNode*)jumpNode;
    } break;
    case Arcadia_MILC_WordType_JumpIfTrue: {
      next(thread, self);
      Arcadia_MILC_AST_OperandNode* operand = onOperand(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Comma)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      next(thread, self);
      if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_String* labelName = getText(thread, self);
      next(thread, self);
      Arcadia_MILC_AST_JumpInstructionNode* jumpNode = Arcadia_MILC_AST_JumpInstructionNode_create(thread, labelName);
      operand = NULL;
      return (Arcadia_MILC_AST_InstructionNode*)jumpNode;
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
    Arcadia_MILC_Parser* self
  )
{
  if (is(thread, self, Arcadia_MILC_WordType_EndOfInput)) {
    return;
  }
  if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket) && !is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
}

// instructionStatement : instruction endOfStatement
static Arcadia_MILC_AST_InstructionStatementNode*
onInstructionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_MILC_AST_InstructionNode* instruction = onInstruction(thread, self);
  Arcadia_MILC_AST_InstructionStatementNode* statement = (Arcadia_MILC_AST_InstructionStatementNode*)instruction;
  onEndOfStatement(thread, self);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  return statement;
}

/// variableDefinitionStatement : 'variable' name endOfStatement
static Arcadia_MILC_AST_VariableDefinitionStatementNode*
onVariableDefinitionStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (Arcadia_MILC_WordType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MILC_WordType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MILC_AST_VariableDefinitionStatementNode* statement = Arcadia_MILC_AST_VariableDefinitionStatementNode_create(thread, getText(thread, self));
  next(thread, self);
  onEndOfStatement(thread, self);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  return statement;
}

/// statement : instructionStatement
///           | labelDefinitionStatement endOfStatement?
///           | variableDefinitionStatement
///           | emptyStatement endOfStatement
/// labelDefinitionStatement : name ':'
static Arcadia_MILC_AST_StatementNode*
onStatement
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  // skip empty statement
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  // variableDefinitionStatement : 'variable' name
  if (is(thread, self, Arcadia_MILC_WordType_Variable)) {
    Arcadia_MILC_AST_VariableDefinitionStatementNode* statementNode = onVariableDefinitionStatement(thread, self);
    return (Arcadia_MILC_AST_StatementNode*)statementNode;
  }
  // labelDefinitionStatement : name ':'
  if (is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_MILC_AST_StatementNode* statementNode = NULL;
    Arcadia_String* name = getText(thread, self);
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_Colon)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
    statementNode = (Arcadia_MILC_AST_StatementNode*)Arcadia_MILC_AST_LabelDefinitionStatementNode_create(thread, name);
    onEndOfStatement(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    return statementNode;
  }
  // instruction statement
  {
    Arcadia_MILC_AST_InstructionStatementNode* statementNode = onInstructionStatement(thread, self);
    return (Arcadia_MILC_AST_StatementNode*)statementNode;
  }
}

// parameter : <name> ':' <type>
// <name> : lexical.name
// <type> : lexical.name
static Arcadia_MILC_AST_FieldDefinitionNode*
onParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Variable)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* name = getText(thread, self);
  next(thread, self);
  if (!is(thread, self, Arcadia_MILC_WordType_Colon)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MILC_AST_IdentifierNode* type = onIdentifier(thread, self);
  return Arcadia_MILC_AST_FieldDefinitionNode_create(thread, name, type);
}

// parameters : '(' (parameter (',' parameter)*)? ')'
static Arcadia_List*
onParameters
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_List* parameters = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftParenthesis)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_MILC_AST_FieldDefinitionNode* parameter = NULL;
    if (is(thread, self, Arcadia_MILC_WordType_Variable)) {
      parameter = onParameter(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
      while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
        next(thread, self);
      }
      while (is(thread, self, Arcadia_MILC_WordType_Comma)) {
        next(thread, self);
        while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
          next(thread, self);
        }
        parameter = onParameter(thread, self);
        Arcadia_List_insertBackObjectReferenceValue(thread, parameters, (Arcadia_ObjectReferenceValue)parameter);
        while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
          next(thread, self);
        }
      }
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightParenthesis)) {
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
static Arcadia_MILC_AST_ConstructorDefinitionNode*
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Constructor)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_List* constructorParameters = onParameters(thread, self);
  Arcadia_List* constructorBody = NULL;
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    constructorBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_MILC_AST_StatementNode* statementNode = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, constructorBody, (Arcadia_ObjectReferenceValue)statementNode);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftParenthesis)) {
    if (!is(thread, self, Arcadia_MILC_WordType_RightParenthesis)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
  }
  Arcadia_MILC_AST_ConstructorDefinitionNode* constructorDefinitionNode = Arcadia_MILC_AST_ConstructorDefinitionNode_create(thread, nativeName, constructorParameters, constructorBody);
  return constructorDefinitionNode;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static Arcadia_MILC_AST_MethodDefinitionNode*
onMethodDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Method)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* methodName = getText(thread, self);
  next(thread, self);
  Arcadia_List* methodParameters = onParameters(thread, self);
  Arcadia_List* methodBody = NULL;
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    methodBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_MILC_AST_StatementNode* statementNode = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, methodBody, (Arcadia_ObjectReferenceValue)statementNode);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_MethodDefinitionNode* methodDefinitionNode = Arcadia_MILC_AST_MethodDefinitionNode_create(thread, nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionNode;
}

// variableDefinition : 'variable' name ':' type
static Arcadia_MILC_AST_FieldDefinitionNode*
onFieldDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (Arcadia_MILC_WordType_Variable != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (Arcadia_MILC_WordType_Name != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* name = getText(thread, self);
  next(thread, self);
  if (Arcadia_MILC_WordType_Colon != getType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  Arcadia_MILC_AST_IdentifierNode* type = onIdentifier(thread, self);
  Arcadia_MILC_AST_FieldDefinitionNode* variableDefinitionNode = Arcadia_MILC_AST_FieldDefinitionNode_create(thread, name, type);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  return variableDefinitionNode;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static Arcadia_MILC_AST_Node*
onClassMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  switch (getType(thread, self)) {
    case Arcadia_MILC_WordType_Constructor: {
      return (Arcadia_MILC_AST_Node*)onConstructorDefinition(thread, self);
    } break;
    case Arcadia_MILC_WordType_Method: {
      return (Arcadia_MILC_AST_Node*)onMethodDefinition(thread, self);
    } break;
    case Arcadia_MILC_WordType_Variable: {
      return (Arcadia_MILC_AST_Node*)onFieldDefinition(thread, self);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static Arcadia_MILC_AST_ClassDefinitionNode*
onClassDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Class)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_IdentifierNode* className = onIdentifier(thread, self);
  Arcadia_MILC_AST_IdentifierNode* extendedClassName = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_Extends)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    extendedClassName = onIdentifier(thread, self);
  }
  Arcadia_List* classBody = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    classBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_MILC_AST_Node* classMemberDefinitionNode = onClassMemberDefinition(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, classBody, (Arcadia_ObjectReferenceValue)classMemberDefinitionNode);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_ClassDefinitionNode* classDefinitionNode = Arcadia_MILC_AST_ClassDefinitionNode_create(thread, className, extendedClassName, classBody);
  return classDefinitionNode;
}

static Arcadia_MILC_AST_Node*
onEnumerationMemberDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{ 
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* enumerationConstantName = getText(thread, self);
  next(thread, self);
  Arcadia_MILC_AST_IntegerLiteralNode* enumerationConstantInitializer = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_EqualsSign)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_IntegerLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    enumerationConstantInitializer = Arcadia_MILC_AST_IntegerLiteralNode_create(thread, getText(thread, self));
    next(thread, self);
  }
  Arcadia_MILC_AST_EnumerationConstantDefinitionNode* enumerationConstantDefinitionNode = Arcadia_MILC_AST_EnumerationConstantDefinitionNode_create(thread, enumerationConstantName, enumerationConstantInitializer);

  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  return (Arcadia_MILC_AST_Node*)enumerationConstantDefinitionNode;
}

// enumerationDefinition : 'enumeration' identifier enumerationBody
// enumerationBody : '{' enumerationBodyDefinition* '}'
static Arcadia_MILC_AST_EnumerationDefinitionNode*
onEnumerationDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Enumeration)) {
    Arcadia_Languages_Diagnostics_add(thread,
                                      self->diagnostics,
                                      (Arcadia_Languages_Diagnostic*)
                                      Arcadia_MILC_Diagnostics_UnexpectedWordDiagnostic_create(thread,
                                                                                               Arcadia_Languages_DiagnosticType_Error,
                                                                                               getType(thread, self)));
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_IdentifierNode* enumerationName = onIdentifier(thread, self);
  Arcadia_List* enumerationBody = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    enumerationBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_MILC_AST_Node* enumerationMemberDefinitionNode = onEnumerationMemberDefinition(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, enumerationBody, (Arcadia_ObjectReferenceValue)enumerationMemberDefinitionNode);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_EnumerationDefinitionNode* enumerationDefinitionNode = Arcadia_MILC_AST_EnumerationDefinitionNode_create(thread, enumerationName, enumerationBody);
  return enumerationDefinitionNode;
}


// moduleDefinition : 'module' name moduleBody
// moduleBody : '{' '}'
static Arcadia_MILC_AST_ModuleDefinitionNode*
onModuleDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  if (!is(thread, self, Arcadia_MILC_WordType_Module)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (!is(thread, self, Arcadia_MILC_WordType_Name)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MILC_AST_IdentifierNode* moduleName = onIdentifier(thread, self);
  Arcadia_List* moduleBody = NULL;
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    moduleBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_ModuleDefinitionNode* moduleDefinitionNode = Arcadia_MILC_AST_ModuleDefinitionNode_create(thread, moduleName, moduleBody);
  return moduleDefinitionNode;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static Arcadia_MILC_AST_ProcedureDefinitionNode*
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_BooleanValue entry = Arcadia_BooleanValue_False;
  if (!is(thread, self, Arcadia_MILC_WordType_Procedure)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  if (is(thread, self, Arcadia_MILC_WordType_Entry)) {
    next(thread, self);
    entry = Arcadia_BooleanValue_True;
  }
  Arcadia_String* nativeName = NULL;
  if (is(thread, self, Arcadia_MILC_WordType_Native)) {
    next(thread, self);
    if (!is(thread, self, Arcadia_MILC_WordType_StringLiteral)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    nativeName = getText(thread, self);
    next(thread, self);
  }
  Arcadia_MILC_AST_IdentifierNode* procedureName = onIdentifier(thread, self);
  Arcadia_List* procedureParameters = onParameters(thread, self);
  Arcadia_List* procedureBody = NULL;
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  if (is(thread, self, Arcadia_MILC_WordType_LeftCurlyBracket)) {
    procedureBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    next(thread, self);
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput) && !is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_MILC_AST_StatementNode* statementNode = onStatement(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, procedureBody, (Arcadia_ObjectReferenceValue)statementNode);
    }
    if (!is(thread, self, Arcadia_MILC_WordType_RightCurlyBracket)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    }
    next(thread, self);
  }
  while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
    next(thread, self);
  }
  Arcadia_MILC_AST_ProcedureDefinitionNode* procedureDefinitionNode = Arcadia_MILC_AST_ProcedureDefinitionNode_create(thread, entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionNode;
}

/// compilationUnit : (classDefinition|enumerationDefinition|moduleDefinition|proceduredefinition)*
static Arcadia_MILC_AST_CompilationUnitNode*
onCompilationUnit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = Arcadia_MILC_AST_CompilationUnitNode_create(thread);
  if (!is(thread, self, Arcadia_MILC_WordType_StartOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  next(thread, self);
  while (!is(thread, self, Arcadia_MILC_WordType_EndOfInput)) {
    while (is(thread, self, Arcadia_MILC_WordType_LineTerminator)) {
      next(thread, self);
    }
    Arcadia_MILC_AST_DefinitionNode* definitionNode = NULL;
    switch (getType(thread, self)) {
      case Arcadia_MILC_WordType_Class: {
        definitionNode = (Arcadia_MILC_AST_DefinitionNode*)onClassDefinition(thread, self);
        Arcadia_MILC_AST_CompilationUnitNode_appendDefinition(thread, compilationUnitNode, definitionNode);
        definitionNode->compilationUnitNode = compilationUnitNode;
        assert(NULL != definitionNode->compilationUnitNode);
      } break;
      case Arcadia_MILC_WordType_Enumeration: {
        definitionNode = (Arcadia_MILC_AST_DefinitionNode*)onEnumerationDefinition(thread, self);
        Arcadia_MILC_AST_CompilationUnitNode_appendDefinition(thread, compilationUnitNode, definitionNode);
        definitionNode->compilationUnitNode = compilationUnitNode;
        assert(NULL != definitionNode->compilationUnitNode);
      } break;
      case Arcadia_MILC_WordType_Module: {
        definitionNode = (Arcadia_MILC_AST_DefinitionNode*)onModuleDefinition(thread, self);
        Arcadia_MILC_AST_CompilationUnitNode_appendDefinition(thread, compilationUnitNode, definitionNode);
        definitionNode->compilationUnitNode = compilationUnitNode;
        assert(NULL != definitionNode->compilationUnitNode);
      } break;
      case Arcadia_MILC_WordType_Procedure: {
        definitionNode = (Arcadia_MILC_AST_DefinitionNode*)onProcedureDefinition(thread, self);
        Arcadia_MILC_AST_CompilationUnitNode_appendDefinition(thread, compilationUnitNode, definitionNode);
        definitionNode->compilationUnitNode = compilationUnitNode;
        assert(NULL != definitionNode->compilationUnitNode);
      } break;
      default: {
        Arcadia_Languages_Diagnostics_add(thread,
                                          self->diagnostics,
                                          (Arcadia_Languages_Diagnostic*)
                                          Arcadia_MILC_Diagnostics_UnexpectedWordDiagnostic_create(thread,
                                                                                                   Arcadia_Languages_DiagnosticType_Error,
                                                                                                   getType(thread, self)));
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
  if (!is(thread, self, Arcadia_MILC_WordType_EndOfInput)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return compilationUnitNode;
}

static Arcadia_Value
Arcadia_MILC_Parser_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self,
    Arcadia_RuntimeByteArray* input
  )
{
  Arcadia_Languages_Scanner_setInput(thread, (Arcadia_Languages_Scanner*)self->scanner, input);
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = onCompilationUnit(thread, self);
  return Arcadia_Value_makeObjectReferenceValue(compilationUnitNode);
}

static Arcadia_Languages_StringTable*
Arcadia_MILC_Parser_getStringTableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{ return self->stringTable; }

static Arcadia_Languages_Diagnostics*
Arcadia_MILC_Parser_getDiagnosticsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Parser* self
  )
{ return self->diagnostics; }
