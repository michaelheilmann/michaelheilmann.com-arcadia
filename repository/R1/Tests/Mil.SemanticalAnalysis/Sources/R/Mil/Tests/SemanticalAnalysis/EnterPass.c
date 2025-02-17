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

// Last modified: 2024-10-18

#include "R/Mil/Tests/SemanticalAnalysis/EnterPass.h"

#include "R/Include.h"
#include "R/Mil/Tests/SemanticalAnalysis/StatementsContext.h"
#include "R/Interpreter/Constructor.h"
#include "R/Interpreter/Method.h"
#include "R/Mil/Include.h"
#include "R/ArgumentsValidation.h"

static Arcadia_Natural32Value
getRegisterOfVariable
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name
  );

static void
onOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_OperandAst* operand
  );

static R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  );

static void
onConstructorDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_Mil_ConstructorDefinitionAst* definitionAst
  );

static R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  );

static void
onMethodDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_Mil_MethodDefinitionAst* definitionAst
  );

static R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  );

static void
onProcedureDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ProcedureDefinitionAst* definitionAst
  );

static void
onVariableDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_Mil_VariableDefinitionAst* definitionAst
  );

static void
onClassBodyDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_List* classBodyAst
  );

static void
onClassDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ClassDefinitionAst* definitionAst
  );

static Arcadia_Natural32Value
getRegisterOfVariable
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, context->variables); i < n; ++i) {
    Arcadia_Value args[2] = { { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name }, 
                              Arcadia_List_getAt(process, context->variables, i) };
    if (Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      return i;
    }
  }
  Arcadia_List_appendObjectReferenceValue(process, context->variables, name);
  return Arcadia_List_getSize(process, context->variables) - 1;
}

static void
onOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_OperandAst* operandAst
  )
{
  if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_VariableOperandAst_getType(process))) {
    Arcadia_Mil_VariableOperandAst* variableOperandAst = (Arcadia_Mil_VariableOperandAst*)operandAst;
    R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(process, context, variableOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_BooleanLiteralOperandAst_getType(process))) {
    Arcadia_Mil_BooleanLiteralOperandAst* booleanLiteralOperandAst = (Arcadia_Mil_BooleanLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateBoolean(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toBoolean(process, booleanLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_IntegerLiteralOperandAst_getType(process))) {
    Arcadia_Mil_IntegerLiteralOperandAst* integerLiteralOperandAst = (Arcadia_Mil_IntegerLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateInteger64(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toInteger64(process, integerLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_RealLiteralOperandAst_getType(process))) {
    Arcadia_Mil_RealLiteralOperandAst* realLiteralOperandAst = (Arcadia_Mil_RealLiteralOperandAst*)operandAst;
    Arcadia_String_toReal64(process, realLiteralOperandAst->value);
    /*@todo Support Real64 constants.*/
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_StringLiteralOperandAst_getType(process))) {
    Arcadia_Mil_StringLiteralOperandAst* stringLiteralOperandAst = (Arcadia_Mil_StringLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateString(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), stringLiteralOperandAst->value);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _Arcadia_Mil_VoidLiteralOperandAst_getType(process))) {
    Arcadia_Mil_VoidLiteralOperandAst* voidLiteralOperandAst = (Arcadia_Mil_VoidLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateVoid(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toVoid(process, voidLiteralOperandAst->value));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
onLabelStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_LabelStatementAst* labelStatementAst
  )
{
  Arcadia_Mil_CallableContext_onDefineLabel(process, context, labelStatementAst->labelName, labelStatementAst, context->statementIndex);
  context->statementIndex++;
}

static void
onRaiseStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_RaiseStatementAst* raiseStatementAst
  )
{
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Raise;
  R_Interpreter_Code_append(process, code, &opcode, 1);
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
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Return;
  R_Interpreter_Code_append(process, code, &opcode, 1);
  onOperand(process, interpreterProcessState, code, context, returnStatementAst->operand);
  context->statementIndex++;
}

static void
onExpressionStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    Arcadia_Mil_CallableContext* context,
    Arcadia_Mil_ExpressionStatementAst* expressionStatementAst
  )
{
  Arcadia_Mil_ExpressionAst* expressionAst = Arcadia_Mil_ExpressionStatementAst_getExpression(expressionStatementAst);
  if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _Arcadia_Mil_LoadExpressionAst_getType(process))) {
    Arcadia_Mil_LoadExpressionAst* loadExpressionAst = (Arcadia_Mil_LoadExpressionAst*)expressionAst;
    Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Load;
    R_Interpreter_Code_append(process, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
    onOperand(process, interpreterProcessState, code, context, loadExpressionAst->operand);
    context->statementIndex++;
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _Arcadia_Mil_BinaryExpressionAst_getType(process))) {
    Arcadia_Mil_BinaryExpressionAst* binaryExpressionAst = (Arcadia_Mil_BinaryExpressionAst*)expressionAst;
    switch (binaryExpressionAst->type) {
      case Arcadia_Mil_BinaryExpressionAstType_Add: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Add;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Subtract: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Subtract;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Multiply: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Multiply;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Divide: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Divide;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_Concatenate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Concatenate;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsEqualTo;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsNotEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsNotEqualTo;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsLowerThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThan;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsLowerThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsLowerThanOrEqualTo;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsGreaterThan: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThan;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      case Arcadia_Mil_BinaryExpressionAstType_IsGreaterThanOrEqualTo: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_IsGreaterThanOrEqualTo;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, context, binaryExpressionAst->operand2);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Process_jump(process);
      } break;
    };
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _Arcadia_Mil_UnaryExpressionAst_getType(process))) {
    Arcadia_Mil_UnaryExpressionAst* unaryExpressionAst = (Arcadia_Mil_UnaryExpressionAst*)expressionAst;
    switch (unaryExpressionAst->type) {
      case Arcadia_Mil_UnaryExpressionAstType_Negate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Negate;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, unaryExpressionAst->operand1);
      } break;
      case Arcadia_Mil_UnaryExpressionAstType_Not: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Not;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, context, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, context, unaryExpressionAst->operand1);
        context->statementIndex++;
      } break;
      default: {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Process_jump(process);
      } break;
    };
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
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
  Arcadia_Mil_CallableContext_onLocalVariableDefinition(process,
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
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, statements); i < n; ++i) {
    Arcadia_Value elementValue = Arcadia_List_getAt(process, statements, i);
    Arcadia_ObjectReferenceValue objectElementValue = Arcadia_Value_getObjectReferenceValue(&elementValue);
    Arcadia_Mil_StatementAst* statement = (Arcadia_Mil_StatementAst*)objectElementValue;
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _Arcadia_Mil_LabelStatementAst_getType(process))) {
      onLabelStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_LabelStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _Arcadia_Mil_RaiseStatementAst_getType(process))) {
      onRaiseStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_RaiseStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _Arcadia_Mil_ReturnStatementAst_getType(process))) {
      onReturnStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_ReturnStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _Arcadia_Mil_ExpressionStatementAst_getType(process))) {
      onExpressionStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_ExpressionStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _Arcadia_Mil_VariableDefinitionStatementAst_getType(process))) {
      onVariableDefinitionStatement(process, interpreterProcessState, code, context, (Arcadia_Mil_VariableDefinitionStatementAst*)statement);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
  }
}

static R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Mil_CallableContext* context,
    Arcadia_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, context, statements);
  return code;
}

static void
onProcedureDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ProcedureDefinitionAst* definitionAst
  )
{
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->procedureName };
  Arcadia_Value v = Arcadia_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, definitionAst->procedureParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(process, definitionAst->procedureParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(process, context,
                                                              variableNameString,
                                                              (Arcadia_Mil_Ast*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->procedureBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = Arcadia_Map_get(process, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_createForeign(process, definitionAst->procedureName, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, interpreterProcessState, procedure);
  } else {
    if (!definitionAst->procedureBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_create(process, definitionAst->procedureName, onProcedureBody(process, interpreterProcessState, context, definitionAst->procedureBody));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, interpreterProcessState, procedure);
  }
}

static void
onConstructorDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_Mil_ConstructorDefinitionAst* definitionAst
  )
{
  Arcadia_String* name = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"<constructor>", sizeof(u8"<constructor>") - 1));
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name };
  Arcadia_Value v = Arcadia_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, definitionAst->constructorParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(process, definitionAst->constructorParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(process, context,
                                                              variableNameString,
                                                              (Arcadia_Mil_Ast*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->constructorBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = Arcadia_Map_get(process, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Constructor* construcor = R_Interpreter_Constructor_createForeign(process, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addConstructor(process, enclosing, construcor);
  } else {
    if (!definitionAst->constructorBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Constructor* constructor = R_Interpreter_Constructor_create(process, onConstructorBody(process, interpreterProcessState, context, definitionAst->constructorBody));
    R_Interpreter_Class_addConstructor(process, enclosing, constructor);
  }
}

static void
onMethodDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_Mil_MethodDefinitionAst* definitionAst
  )
{
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->methodName };
  Arcadia_Value v = Arcadia_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Mil_CallableContext* context = Arcadia_Mil_CallableContext_create(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, definitionAst->methodParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = Arcadia_List_getAt(process, definitionAst->methodParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    Arcadia_Mil_CallableContext_onParameterVariableDefinition(process, context,
                                                              variableNameString, 
                                                              (Arcadia_Mil_Ast*)definitionAst);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->methodBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = Arcadia_Map_get(process, foreignProcedures, k);
    if (Arcadia_Value_isVoidValue(&v)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Method* method = R_Interpreter_Method_createForeign(process, definitionAst->methodName, Arcadia_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addMethod(process, enclosing, method);
  } else {
    if (!definitionAst->methodBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    R_Interpreter_Method* method = R_Interpreter_Method_create(process, definitionAst->methodName, onMethodBody(process, interpreterProcessState, context, definitionAst->methodBody));
    R_Interpreter_Class_addMethod(process, enclosing, method);
  }
}

static void
onVariableDefinition
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    Arcadia_List* classBodyAst
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, classBodyAst); i < n; ++i) {
    Arcadia_ObjectReferenceValue element = Arcadia_List_getObjectReferenceValueAt(process, classBodyAst, i);
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _Arcadia_Mil_ConstructorDefinitionAst_getType(process))) {
      onConstructorDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _Arcadia_Mil_MethodDefinitionAst_getType(process))) {
      onMethodDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _Arcadia_Mil_VariableDefinitionAst_getType(process))) {
      onVariableDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
}

static void
onClassDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ClassDefinitionAst* definitionAst
  )
{
  R_Interpreter_Class* class = R_Interpreter_Class_create(process, definitionAst->className, definitionAst->extendedClassName);
  if (!definitionAst->classBody) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  onClassBodyDefinition(process, interpreterProcess, symbolTable, foreignProcedures, class, definitionAst->classBody);
  R_Interpreter_ProcessState_defineGlobalClass(process, interpreterProcess, class);
}

void
Arcadia_Mil_EnterPass_onModule
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ModuleAst* moduleAst
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Mil_ModuleAst_getNumberOfDefinitions(process, moduleAst); i < n; ++i) {
    Arcadia_Mil_DefinitionAst* definitionAst = Arcadia_Mil_ModuleAst_getDefinitionAt(process, moduleAst, i);
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(definitionAst), _Arcadia_Mil_ClassDefinitionAst_getType(process))) {
      onClassDefinition(process, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_Mil_ClassDefinitionAst*)definitionAst);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(definitionAst), _Arcadia_Mil_ProcedureDefinitionAst_getType(process))) {
      onProcedureDefinition(process, interpreterProcess, symbolTable, foreignProcedures, (Arcadia_Mil_ProcedureDefinitionAst*)definitionAst);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
  }
}

static void
Arcadia_Mil_EnterPass_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_EnterPass_visit
  (
    Arcadia_Process* process,
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
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Arcadia.Mil.EnterPass", Arcadia_Mil_EnterPass, u8"Arcadia.Mil.Pass", Arcadia_Mil_Pass, &_typeOperations);

static void
Arcadia_Mil_EnterPass_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Pass* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_EnterPass_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_EnterPass_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_EnterPass* self
  )
{ }

Arcadia_Mil_EnterPass*
Arcadia_Mil_EnterPass_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  Arcadia_Mil_EnterPass* self = R_allocateObject(process, _Arcadia_Mil_EnterPass_getType(process), 0, &argumentValues[0]);
  return self;
}
