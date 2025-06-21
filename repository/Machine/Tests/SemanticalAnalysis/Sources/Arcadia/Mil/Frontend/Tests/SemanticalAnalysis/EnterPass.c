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

#include "Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/EnterPass.h"

#include "Arcadia/Include.h"
#include "Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/StatementsContext.h"
#include "Arcadia/Interpreter/Constructor.h"
#include "Arcadia/Interpreter/Method.h"
#include "Arcadia/Mil/Frontend/Include.h"

static Arcadia_Natural32Value
getRegisterOfVariable
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name
  );

static void
onOperand
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_OperandAst* operand
  );

static R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
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
    Arcadia_Mil_ConstructorDefinitionAst* definitionAst
  );

static R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
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
    Arcadia_Mil_MethodDefinitionAst* definitionAst
  );

static R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  );

static void
onProcedureDefinition
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ProcedureDefinitionAst* definitionAst
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
    Arcadia_Mil_VariableDefinitionAst* definitionAst
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
    Arcadia_Mil_ClassDefinitionAst* definitionAst
  );

static Arcadia_Natural32Value
getRegisterOfVariable
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, context->variables); i < n; ++i) {
    Arcadia_Value args[2] = {
        Arcadia_Value_makeObjectReferenceValue(name),
        Arcadia_List_getAt(thread, context->variables, i),
      };
    if (Arcadia_Value_isEqualTo(thread, &args[0], &args[1])) {
      return i;
    }
  }
  Arcadia_List_insertBackObjectReferenceValue(thread, context->variables, name);
  return Arcadia_List_getSize(thread, context->variables) - 1;
}

static void
onOperand
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_OperandAst* operandAst
  )
{
  if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_VariableOperandAst_getType(thread))) {
    Arcadia_Mil_VariableOperandAst* variableOperandAst = (Arcadia_Mil_VariableOperandAst*)operandAst;
    R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(thread, context, variableOperandAst->value));
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_BooleanLiteralOperandAst_getType(thread))) {
    Arcadia_Mil_BooleanLiteralOperandAst* booleanLiteralOperandAst = (Arcadia_Mil_BooleanLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateBoolean(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toBoolean(thread, booleanLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_IntegerLiteralOperandAst_getType(thread))) {
    Arcadia_Mil_IntegerLiteralOperandAst* integerLiteralOperandAst = (Arcadia_Mil_IntegerLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateInteger64(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toInteger64(thread, integerLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_RealLiteralOperandAst_getType(thread))) {
    Arcadia_Mil_RealLiteralOperandAst* realLiteralOperandAst = (Arcadia_Mil_RealLiteralOperandAst*)operandAst;
    Arcadia_String_toReal64(thread, realLiteralOperandAst->value);
    /*@todo Support Real64 constants.*/
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_StringLiteralOperandAst_getType(thread))) {
    Arcadia_Mil_StringLiteralOperandAst* stringLiteralOperandAst = (Arcadia_Mil_StringLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateString(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), stringLiteralOperandAst->value);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)operandAst), _Arcadia_Mil_VoidLiteralOperandAst_getType(thread))) {
    Arcadia_Mil_VoidLiteralOperandAst* voidLiteralOperandAst = (Arcadia_Mil_VoidLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateVoid(thread, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toVoid(thread, voidLiteralOperandAst->value));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
onLabelStatement
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_LabelStatementAst* labelStatementAst
  )
{
  Arcadia_Mil_CallableContext_onDefineLabel(thread, context, labelStatementAst->labelName, labelStatementAst, context->statementIndex);
  context->statementIndex++;
}

static void
onRaiseStatement
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_RaiseStatementAst* raiseStatementAst
  )
{
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Raise;
  R_Interpreter_Code_append(thread, code, &opcode, 1);
  context->statementIndex++;
}

static void
onReturnStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_ReturnStatementAst* returnStatementAst
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Return;
  R_Interpreter_Code_append(thread, code, &opcode, 1);
  onOperand(thread, interpreterProcessState, code, context, returnStatementAst->operand);
  context->statementIndex++;
}

static void
onExpressionStatement
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_ExpressionStatementAst* expressionStatementAst
  )
{
  Arcadia_Mil_ExpressionAst* expressionAst = Arcadia_Mil_ExpressionStatementAst_getExpression(thread, expressionStatementAst);
  if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)expressionAst), _Arcadia_Mil_LoadExpressionAst_getType(thread))) {
    Arcadia_Mil_LoadExpressionAst* loadExpressionAst = (Arcadia_Mil_LoadExpressionAst*)expressionAst;
    Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Load;
    R_Interpreter_Code_append(thread, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
    onOperand(thread, interpreterProcessState, code, context, loadExpressionAst->operand);
    context->statementIndex++;
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)expressionAst), _Arcadia_Mil_BinaryExpressionAst_getType(thread))) {
    Arcadia_Mil_BinaryExpressionAst* binaryExpressionAst = (Arcadia_Mil_BinaryExpressionAst*)expressionAst;
    switch (binaryExpressionAst->type) {
      case Arcadia_Mil_BinaryExpressionAstType_Add: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Add;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Subtract: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Subtract;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Multiply: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Multiply;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Divide: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Divide;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Concatenate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Concatenate;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsNotEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsNotEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsLowerThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThan;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsLowerThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThanOrEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsGreaterThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThan;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsGreaterThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThanOrEqualTo;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(thread, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)expressionAst), _Arcadia_Mil_UnaryExpressionAst_getType(thread))) {
    Arcadia_Mil_UnaryExpressionAst* unaryExpressionAst = (Arcadia_Mil_UnaryExpressionAst*)expressionAst;
    switch (unaryExpressionAst->type) {
      case Arcadia_Mil_UnaryExpressionAstType_Negate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Negate;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, unaryExpressionAst->operand1);
      } break;
      case Arcadia_Mil_UnaryExpressionAstType_Not: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Not;
        R_Interpreter_Code_append(thread, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(thread, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(thread, context, expressionStatementAst->targetVariableName));
        onOperand(thread, interpreterProcessState, code, context, unaryExpressionAst->operand1);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  } else {
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
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_VariableDefinitionStatementAst* variableDefinitionStatement
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Mil_CallableContext_onLocalVariableDefinition(thread,
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
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, statements); i < n; ++i) {
    Arcadia_Value elementValue = Arcadia_List_getAt(thread, statements, i);
    Arcadia_ObjectReferenceValue objectElementValue = Arcadia_Value_getObjectReferenceValue(&elementValue);
    Arcadia_Mil_StatementAst* statement = (Arcadia_Mil_StatementAst*)objectElementValue;
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_Mil_LabelStatementAst_getType(thread))) {
      onLabelStatement(thread, interpreterProcessState, code, context, (Arcadia_Mil_LabelStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_Mil_RaiseStatementAst_getType(thread))) {
      onRaiseStatement(thread, interpreterProcessState, code, context, (Arcadia_Mil_RaiseStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_Mil_ReturnStatementAst_getType(thread))) {
      onReturnStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_ReturnStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_Mil_ExpressionStatementAst_getType(thread))) {
      onExpressionStatement(thread, interpreterProcessState, code, context, (Arcadia_Mil_ExpressionStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)statement), _Arcadia_Mil_VariableDefinitionStatementAst_getType(thread))) {
      onVariableDefinitionStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_VariableDefinitionStatementAst*)statement);
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
    Arcadia_Mil_CallableContext* context,
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
    Arcadia_Mil_CallableContext* context,
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
    Arcadia_Mil_CallableContext* context,
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
    Arcadia_Mil_ProcedureDefinitionAst* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->procedureName);
  Arcadia_Value v = Arcadia_Map_get(thread, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, definitionAst->procedureParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(thread, definitionAst->procedureParameters, i);
    Arcadia_String* variableNameString = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &variableNameValue, _Arcadia_String_getType(thread));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variableNameString,
                                                              (Arcadia_Mil_Ast*)definitionAst);
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
    Arcadia_Mil_ConstructorDefinitionAst* definitionAst
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
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, definitionAst->constructorParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(thread, definitionAst->constructorParameters, i);
    Arcadia_String* variableNameString = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &variableNameValue, _Arcadia_String_getType(thread));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variableNameString,
                                                              (Arcadia_Mil_Ast*)definitionAst);
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
    Arcadia_Mil_MethodDefinitionAst* definitionAst
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(definitionAst->methodName);
  Arcadia_Value v = Arcadia_Map_get(thread, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, definitionAst->methodParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(thread, definitionAst->methodParameters, i);
    Arcadia_String* variableNameString = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &variableNameValue, _Arcadia_String_getType(thread));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(thread, context,
                                                              variableNameString,
                                                              (Arcadia_Mil_Ast*)definitionAst);
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
    Arcadia_Mil_VariableDefinitionAst* definitionAst
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
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, classBodyAst); i < n; ++i) {
    Arcadia_ObjectReferenceValue element = Arcadia_List_getObjectReferenceValueAt(thread, classBodyAst, i);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_Mil_ConstructorDefinitionAst_getType(thread))) {
      onConstructorDefinition(thread, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_Mil_MethodDefinitionAst_getType(thread))) {
      onMethodDefinition(thread, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, element), _Arcadia_Mil_VariableDefinitionAst_getType(thread))) {
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
    Arcadia_Mil_ClassDefinitionAst* definitionAst
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
Arcadia_Mil_EnterPass_onModule
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ModuleAst* moduleAst
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Mil_ModuleAst_getNumberOfDefinitions(thread, moduleAst); i < n; ++i) {
    Arcadia_Mil_DefinitionAst* definitionAst = Arcadia_Mil_ModuleAst_getDefinitionAt(thread, moduleAst, i);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)definitionAst), _Arcadia_Mil_ClassDefinitionAst_getType(thread))) {
      onClassDefinition(thread, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_Mil_ClassDefinitionAst*)definitionAst);
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)definitionAst), _Arcadia_Mil_ProcedureDefinitionAst_getType(thread))) {
      onProcedureDefinition(thread, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_Mil_ProcedureDefinitionAst*)definitionAst);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
Arcadia_Mil_EnterPass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_EnterPass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_EnterPass* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Mil_EnterPass_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_EnterPass_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Mil.EnterPass", Arcadia_Mil_EnterPass, u8"Arcadia.Mil.Pass", Arcadia_Mil_Pass, &_typeOperations);

static void
Arcadia_Mil_EnterPass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Pass* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_EnterPass_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_EnterPass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_EnterPass* self
  )
{ }

Arcadia_Mil_EnterPass*
Arcadia_Mil_EnterPass_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Mil_EnterPass* self = Arcadia_allocateObject(thread, _Arcadia_Mil_EnterPass_getType(thread), 0, &argumentValues[0]);
  return self;
}
