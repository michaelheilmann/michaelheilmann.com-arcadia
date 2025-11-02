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

#include "Arcadia/MIL/Frontend/Tests/SemanticalAnalysis/EnterPass.h"

#include "Arcadia/Include.h"
#include "Arcadia/MIL/Frontend/Tests/SemanticalAnalysis/StatementsContext.h"
#include "Arcadia/Interpreter/Constructor.h"
#include "Arcadia/Interpreter/Method.h"
#include "Arcadia/MIL/AST/Include.h"
#include "Arcadia/MIL/Frontend/Include.h"
#include <limits.h>

static Arcadia_Natural32Value
getRegisterOfVariable2
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_OperandNode* operand
  );

static void
onOperand
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_OperandNode* operand
  );

static R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  );

static void
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_AST_ConstructorDefinitionNode* definitionAst
  );

static R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  );

static void
onMethodDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_MethodDefinitionNode* definitionAst
  );

static R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  );

static void
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ProcedureDefinitionNode* definitionAst
  );

static void
onParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing
  );

static void
onLocalVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing
  );

static void
onObjectVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_AST_FieldDefinitionNode* definitionAst
  );

static void
onClassBodyDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_List* classBodyAst
  );

static void
onClassDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ClassDefinitionNode* definitionAst
  );

// get the register index for a variable operand or a register operand
static Arcadia_Natural32Value
getRegisterOfVariable2
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_OperandNode* operand
  )
{
  Arcadia_String* name = NULL;
  if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)operand, _Arcadia_MIL_AST_VariableOperandNode_getType(thread))) {
    name = ((Arcadia_MIL_AST_VariableOperandNode*)operand)->value;
  } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)operand, _Arcadia_MIL_AST_RegisterOperandNode_getType(thread))) {
    name = ((Arcadia_MIL_AST_VariableOperandNode*)operand)->value;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)context->variables); i < n; ++i) {
    Arcadia_Value args[2] = {
        Arcadia_Value_makeObjectReferenceValue(name),
        Arcadia_List_getAt(thread, context->variables, i),
    };
    if (Arcadia_Value_isEqualTo(thread, &args[0], &args[1])) {
      return i;
    }
  }
  Arcadia_List_insertBackObjectReferenceValue(thread, context->variables, name);
  return Arcadia_Collection_getSize(thread, (Arcadia_Collection*)context->variables) - 1;
}

static void
onOperand
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_OperandNode* operandAst
  )
{
  if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_MIL_AST_VariableOperandNode_getType(thread))) {
    Arcadia_MIL_AST_VariableOperandNode* variableOperandAst = (Arcadia_MIL_AST_VariableOperandNode*)operandAst;
    R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable2(thread, context, (Arcadia_MIL_AST_OperandNode*)variableOperandAst));
  } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)operandAst, _Arcadia_MIL_AST_LiteralOperandNode_getType(thread))) {
    Arcadia_MIL_AST_Node* literalNode = ((Arcadia_MIL_AST_LiteralOperandNode*)operandAst)->literal;
    if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)literalNode, _Arcadia_MIL_AST_BooleanLiteralNode_getType(thread))) {
      Arcadia_MIL_AST_BooleanLiteralNode* booleanLiteralOperandAst = (Arcadia_MIL_AST_BooleanLiteralNode*)literalNode;
      R_Interpreter_Code_Constants_getOrCreateBoolean(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toBoolean(thread, booleanLiteralOperandAst->value));
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)literalNode, _Arcadia_MIL_AST_IntegerLiteralNode_getType(thread))) {
      Arcadia_MIL_AST_IntegerLiteralNode* integerLiteralOperandAst = (Arcadia_MIL_AST_IntegerLiteralNode*)literalNode;
      R_Interpreter_Code_Constants_getOrCreateInteger64(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toInteger64(thread, integerLiteralOperandAst->value));
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)literalNode, _Arcadia_MIL_AST_RealLiteralNode_getType(thread))) {
      Arcadia_MIL_AST_RealLiteralNode* realLiteralOperandAst = (Arcadia_MIL_AST_RealLiteralNode*)literalNode;
      Arcadia_String_toReal64(thread, realLiteralOperandAst->value);
      /*@todo Support Real64 constants.*/
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)literalNode, _Arcadia_MIL_AST_StringLiteralNode_getType(thread))) {
      Arcadia_MIL_AST_StringLiteralNode* stringLiteralOperandAst = (Arcadia_MIL_AST_StringLiteralNode*)literalNode;
      R_Interpreter_Code_Constants_getOrCreateString(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), stringLiteralOperandAst->value);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)literalNode, _Arcadia_MIL_AST_VoidLiteralNode_getType(thread))) {
      Arcadia_MIL_AST_VoidLiteralNode* voidLiteralOperandAst = (Arcadia_MIL_AST_VoidLiteralNode*)literalNode;
      R_Interpreter_Code_Constants_getOrCreateVoid(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toVoid(thread, voidLiteralOperandAst->value));
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
onLabelDefinitionStatement
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_LabelDefinitionStatementNode* labelDefinitionStatement
  )
{
  Arcadia_MIL_CallableContext_onDefineLabel(thread, context, labelDefinitionStatement->labelName, labelDefinitionStatement, context->statementIndex);
  context->statementIndex++;
}

static void
onRaiseInstruction
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_RaiseInstructionNode* raiseInstructionNode
  )
{
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Raise;
  R_Interpreter_Code_append(thread, code, &opcode, 1);
  context->statementIndex++;
}

static void
onReturnInstruction
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_ReturnInstructionNode* returnInstructionNode
  )
{
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Return;
  R_Interpreter_Code_append(thread, code, &opcode, 1);
  onOperand(thread, interpreterProcessState, code, context, returnInstructionNode->operand);
  context->statementIndex++;
}

static void
onExpressionStatement
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_AST_InstructionStatementNode* instructionStatementNode
  )
{
  if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)instructionStatementNode), _Arcadia_MIL_AST_BinaryInstructionNode_getType(thread))) {
    Arcadia_MIL_AST_BinaryInstructionNode* binaryExpressionAst = (Arcadia_MIL_AST_BinaryInstructionNode*)instructionStatementNode;
    switch (binaryExpressionAst->kind) {
      case Arcadia_MIL_AST_BinaryInstructionKind_Add: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Add;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_Subtract: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Subtract;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_Multiply: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Multiply;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_Divide: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Divide;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_Concatenate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Concatenate;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsNotEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsNotEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThan;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThanOrEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThan;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThanOrEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, binaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)instructionStatementNode), _Arcadia_MIL_AST_UnaryInstructionNode_getType(thread))) {
    Arcadia_MIL_AST_UnaryInstructionNode* unaryExpressionAst = (Arcadia_MIL_AST_UnaryInstructionNode*)instructionStatementNode;
    switch (unaryExpressionAst->kind) {
      case Arcadia_MIL_AST_UnaryInstructionKind_Negate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Negate;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, unaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, unaryExpressionAst->operand1);
      } break;
      case Arcadia_MIL_AST_UnaryInstructionKind_Not: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Not;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, unaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, unaryExpressionAst->operand1);
        context->statementIndex++;
      } break;
      case Arcadia_MIL_AST_UnaryInstructionKind_Set: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Load;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable2(thread, context, unaryExpressionAst->target));
        onOperand(thread, interpreterProcessState, code, context, unaryExpressionAst->operand1);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)instructionStatementNode), _Arcadia_MIL_AST_RaiseInstructionNode_getType(thread))) {
    onRaiseInstruction(thread, interpreterProcessState, code, context, (Arcadia_MIL_AST_RaiseInstructionNode*)instructionStatementNode);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)instructionStatementNode), _Arcadia_MIL_AST_ReturnInstructionNode_getType(thread))) {
    onReturnInstruction(thread, interpreterProcessState, code, context, (Arcadia_MIL_AST_ReturnInstructionNode*)instructionStatementNode);
  } else {
    Arcadia_Type* type = Arcadia_Object_getType(thread, (Arcadia_Object*)instructionStatementNode);
    Arcadia_AtomValue typeNameAtom = Arcadia_Type_getName(type);
    Arcadia_logf(Arcadia_LogFlags_Error, u8"AST node of type `%.*s` was not handled\n",
                                         Arcadia_clampSizeValue(thread, Arcadia_Atom_getNumberOfBytes(thread, typeNameAtom), 0, INT_MAX),
                                         Arcadia_Atom_getBytes(thread, typeNameAtom));
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
onVariableDefinitionStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_MIL_VariableDefinitionStatementNode* variableDefinitionStatement
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_MIL_CallableContext_onLocalVariableDefinition(thread,
                                                        context,
                                                        variableDefinitionStatement->variableName,
                                                        variableDefinitionStatement);
  context->statementIndex++;
}

static void
onStatements
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)statements); i < n; ++i) {
    Arcadia_Value elementValue = Arcadia_List_getAt(thread, statements, i);
    Arcadia_ObjectReferenceValue objectElementValue = Arcadia_Value_getObjectReferenceValue(&elementValue);
    Arcadia_MIL_AST_StatementNode* statement = (Arcadia_MIL_AST_StatementNode*)objectElementValue;
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_MIL_AST_InstructionStatementNode_getType(thread))) {
      onExpressionStatement(thread, interpreterProcessState, code, context, (Arcadia_MIL_AST_InstructionStatementNode*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_MIL_VariableDefinitionStatementNode_getType(thread))) {
      onVariableDefinitionStatement(process, interpreterProcessState, code, context, (Arcadia_MIL_VariableDefinitionStatementNode*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_MIL_AST_LabelDefinitionStatementNode_getType(thread))) {
      onLabelDefinitionStatement(thread, interpreterProcessState, code, context, (Arcadia_MIL_AST_LabelDefinitionStatementNode*)statement);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
}

static R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_MIL_CallableContext* context,
    Arcadia_List* statements
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static void
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ProcedureDefinitionNode* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->procedureName);
  Arcadia_Value v = Arcadia_Map_get(thread, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_CallableContext* context = Arcadia_MIL_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)definitionAst->procedureParameters); i < n; ++i) {
    Arcadia_MIL_AST_FieldDefinitionNode* variable = (Arcadia_MIL_AST_FieldDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, definitionAst->procedureParameters, i, _Arcadia_MIL_AST_FieldDefinitionNode_getType(thread));
    Arcadia_MIL_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variable->name,
                                                              (Arcadia_MIL_AST_Node*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->procedureBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->nativeName);
    Arcadia_Value v = Arcadia_Map_get(thread, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_createForeign(thread, definitionAst->procedureName, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, interpreterProcessState, procedure);
  } else {
    if (!definitionAst->procedureBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_create(thread, definitionAst->procedureName, onProcedureBody(thread, interpreterProcessState, context, definitionAst->procedureBody));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, interpreterProcessState, procedure);
  }
}

static void
onConstructorDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_AST_ConstructorDefinitionNode* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_String* name = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"<constructor>", sizeof(u8"<constructor>") - 1));
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(name);
  Arcadia_Value v = Arcadia_Map_get(thread, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_CallableContext* context = Arcadia_MIL_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)definitionAst->constructorParameters); i < n; ++i) {
    Arcadia_MIL_AST_FieldDefinitionNode* variable = (Arcadia_MIL_AST_FieldDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, definitionAst->constructorParameters, i, _Arcadia_MIL_AST_FieldDefinitionNode_getType(thread));
    Arcadia_MIL_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variable->name,
                                                              (Arcadia_MIL_AST_Node*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->constructorBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->nativeName);
    Arcadia_Value v = Arcadia_Map_get(thread, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Constructor* construcor = R_Interpreter_Constructor_createForeign(thread, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addConstructor(process, enclosing, construcor);
  } else {
    if (!definitionAst->constructorBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Constructor* constructor = R_Interpreter_Constructor_create(thread, onConstructorBody(thread, interpreterProcessState, context, definitionAst->constructorBody));
    R_Interpreter_Class_addConstructor(process, enclosing, constructor);
  }
}

static void
onMethodDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_MethodDefinitionNode* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->methodName);
  Arcadia_Value v = Arcadia_Map_get(thread, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_CallableContext* context = Arcadia_MIL_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)definitionAst->methodParameters); i < n; ++i) {
    Arcadia_MIL_AST_FieldDefinitionNode* variable = (Arcadia_MIL_AST_FieldDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, definitionAst->methodParameters, i, _Arcadia_MIL_AST_FieldDefinitionNode_getType(thread));
    Arcadia_MIL_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variable->name,
                                                              (Arcadia_MIL_AST_Node*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->methodBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->nativeName);
    Arcadia_Value v = Arcadia_Map_get(thread, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Method* method = R_Interpreter_Method_createForeign(thread, definitionAst->methodName, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addMethod(process, enclosing, method);
  } else {
    if (!definitionAst->methodBody) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    R_Interpreter_Method* method = R_Interpreter_Method_create(thread, definitionAst->methodName, onMethodBody(thread, interpreterProcessState, context, definitionAst->methodBody));
    R_Interpreter_Class_addMethod(process, enclosing, method);
  }
}

/* parameter variable of a constructor, method, or procedure */
static void
onParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing
  )
{ }

/* local variable of a constructor, method, or procedure */
static void
onLocalVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing
  )
{ }

// definition of a variable in a class body
static void
onObjectVariableDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_MIL_AST_FieldDefinitionNode* definitionAst
  )
{ }

static void
onClassBodyDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_List* classBodyAst
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)classBodyAst); i < n; ++i) {
    Arcadia_ObjectReferenceValue element = Arcadia_List_getObjectReferenceValueAt(thread, classBodyAst, i);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_MIL_AST_ConstructorDefinitionNode_getType(thread))) {
      onConstructorDefinition(thread, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_MIL_MethodDefinitionNode_getType(thread))) {
      onMethodDefinition(thread, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_MIL_AST_FieldDefinitionNode_getType(thread))) {
      onObjectVariableDefinition(thread, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
onClassDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ClassDefinitionNode* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  R_Interpreter_Class* class = R_Interpreter_Class_create(thread, definitionAst->className, definitionAst->extendedClassName);
  if (!definitionAst->classBody) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  onClassBodyDefinition(thread, interpreterProcess, symbolTable, foreignProcedures, class, definitionAst->classBody);
  R_Interpreter_ProcessState_defineGlobalClass(process, interpreterProcess, class);
}

void
Arcadia_MIL_SemanticalAnalysis_EnterPass_onModule
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ModuleNode* moduleAst
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_MIL_AST_ModuleNode_getNumberOfDefinitions(thread, moduleAst); i < n; ++i) {
    Arcadia_MIL_DefinitionAst* definitionAst = Arcadia_MIL_AST_ModuleNode_getDefinitionAt(thread, moduleAst, i);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)definitionAst), _Arcadia_MIL_AST_ClassDefinitionNode_getType(thread))) {
      onClassDefinition(thread, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_MIL_AST_ClassDefinitionNode*)definitionAst);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)definitionAst), _Arcadia_MIL_AST_ProcedureDefinitionNode_getType(thread))) {
      onProcedureDefinition(thread, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_MIL_AST_ProcedureDefinitionNode*)definitionAst);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
Arcadia_MIL_SemanticalAnalysis_EnterPass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SemanticalAnalysis_EnterPass* self
  );

static void
Arcadia_MIL_SemanticalAnalysis_EnterPass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SemanticalAnalysis_EnterPass* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_SemanticalAnalysis_EnterPass_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_SemanticalAnalysis_EnterPass_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.SemanticalAnalysis.EnterPass", Arcadia_MIL_SemanticalAnalysis_EnterPass,
                         u8"Arcadia.MIL.Pass", Arcadia_MIL_Pass,
                         &_typeOperations);

static void
Arcadia_MIL_SemanticalAnalysis_EnterPass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SemanticalAnalysis_EnterPass* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_SemanticalAnalysis_EnterPass_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_MIL_SemanticalAnalysis_EnterPass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SemanticalAnalysis_EnterPass* self
  )
{ }

Arcadia_MIL_SemanticalAnalysis_EnterPass*
Arcadia_MIL_SemanticalAnalysis_EnterPass_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_SemanticalAnalysis_EnterPass);
}
