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

#include "R/Mil/Tests/SemanticalAnalysis/Enter.h"

#include "R.h"
#include "R/Interpreter/Constructor.h"
#include "R/Interpreter/Method.h"
#include "R/Mil/Include.h"
#include "R/cstdlib.h"
#include "R/ArgumentsValidation.h"

void
addVariable
  (
    Arcadia_Process* process,
    R_List* variables,
    Arcadia_String* name
  )
{
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(variables); i < n; ++i) {
    Arcadia_Value args[2] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name },
                              R_List_getAt(process, variables, i) };
    if (Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
}

Arcadia_Natural32Value
getRegisterOfVariable
  (
    Arcadia_Process* process,
    R_List* variables,
    Arcadia_String* name
  )
{
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(variables); i < n; ++i) {
    Arcadia_Value args[2] = { { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name }, 
                              R_List_getAt(process, variables, i) };
    if (Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      return i;
    }
  }
  R_List_appendObjectReferenceValue(process, variables, name);
  return R_List_getSize(variables) - 1;
}

void
onOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_OperandAst* operandAst
  )
{
  if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_VariableOperandAst_getType(process))) {
    R_Mil_VariableOperandAst* variableOperandAst = (R_Mil_VariableOperandAst*)operandAst;
    R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(process, variables, variableOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_BooleanLiteralOperandAst_getType(process))) {
    R_Mil_BooleanLiteralOperandAst* booleanLiteralOperandAst = (R_Mil_BooleanLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateBoolean(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toBoolean(process, booleanLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_IntegerLiteralOperandAst_getType(process))) {
    R_Mil_IntegerLiteralOperandAst* integerLiteralOperandAst = (R_Mil_IntegerLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateInteger64(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toInteger64(process, integerLiteralOperandAst->value));
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_RealLiteralOperandAst_getType(process))) {
    R_Mil_RealLiteralOperandAst* realLiteralOperandAst = (R_Mil_RealLiteralOperandAst*)operandAst;
    Arcadia_String_toReal64(process, realLiteralOperandAst->value);
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_StringLiteralOperandAst_getType(process))) {
    R_Mil_StringLiteralOperandAst* stringLiteralOperandAst = (R_Mil_StringLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateString(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), stringLiteralOperandAst->value);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(operandAst), _R_Mil_VoidLiteralOperandAst_getType(process))) {
    R_Mil_VoidLiteralOperandAst* voidLiteralOperandAst = (R_Mil_VoidLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateVoid(process, R_Interpreter_ProcessState_getConstants(interpreterProcessState), Arcadia_String_toVoid(process, voidLiteralOperandAst->value));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

void
onReturnStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_ReturnStatementAst* returnStatementAst
  )
{
  Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Return;
  R_Interpreter_Code_append(process, code, &opcode, 1);
  onOperand(process, interpreterProcessState, code, variables, returnStatementAst->operand);
}

void
onExpressionStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_ExpressionStatementAst* expressionStatementAst
  )
{
  R_Mil_ExpressionAst* expressionAst = R_Mil_ExpressionStatementAst_getExpression(expressionStatementAst);
  if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _R_Mil_LoadExpressionAst_getType(process))) {
    R_Mil_LoadExpressionAst* loadExpressionAst = (R_Mil_LoadExpressionAst*)expressionAst;
    Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Load;
    R_Interpreter_Code_append(process, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
    onOperand(process, interpreterProcessState, code, variables, loadExpressionAst->operand);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _R_Mil_BinaryExpressionAst_getType(process))) {
    R_Mil_BinaryExpressionAst* binaryExpressionAst = (R_Mil_BinaryExpressionAst*)expressionAst;
    switch (binaryExpressionAst->type) {
      case R_Mil_BinaryExpressionAstType_Add: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Add;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Subtract: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Subtract;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Multiply: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Multiply;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Divide: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Divide;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Concatenate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Concatenate;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand1);
        onOperand(process, interpreterProcessState, code, variables, binaryExpressionAst->operand2);
      } break;
      default: {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Process_jump(process);
      } break;
    };
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(expressionAst), _R_Mil_UnaryExpressionAst_getType(process))) {
    R_Mil_UnaryExpressionAst* unaryExpressionAst = (R_Mil_UnaryExpressionAst*)expressionAst;
    switch (unaryExpressionAst->type) {
      case R_Mil_UnaryExpressionAstType_Negate: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Negate;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, unaryExpressionAst->operand1);
      } break;
      case R_Mil_UnaryExpressionAstType_Not: {
        Arcadia_Natural8Value opcode = R_Machine_Code_Opcode_Not;
        R_Interpreter_Code_append(process, code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(process, code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(process, variables, expressionStatementAst->targetVariableName));
        onOperand(process, interpreterProcessState, code, variables, unaryExpressionAst->operand1);
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

void
onVariableDefinitionStatement
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_VariableDefinitionAst* variableDefinitionStatement
  )
{
  addVariable(process, variables, variableDefinitionStatement->variableName);
}

void
onStatements
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Interpreter_Code* code,
    R_List* variables,
    R_List* statements
  )
{
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(statements); i < n; ++i) {
    Arcadia_Value elementValue = R_List_getAt(process, statements, i);
    Arcadia_ObjectReferenceValue objectElementValue = Arcadia_Value_getObjectReferenceValue(&elementValue);
    R_Mil_StatementAst* statement = (R_Mil_StatementAst*)objectElementValue;
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _R_Mil_ReturnStatementAst_getType(process))) {
      onReturnStatement(process, interpreterProcessState, code, variables, (R_Mil_ReturnStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _R_Mil_ExpressionStatementAst_getType(process))) {
      onExpressionStatement(process, interpreterProcessState, code, variables, (R_Mil_ExpressionStatementAst*)statement);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(statement), _R_Mil_VariableDefinitionStatementAst_getType(process))) {
      onVariableDefinitionStatement(process, interpreterProcessState, code, variables, (R_Mil_VariableDefinitionAst*)statement);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
  }
}

R_Interpreter_Code*
onConstructorBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, variables, statements);
  return code;
}

R_Interpreter_Code*
onMethodBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, variables, statements);
  return code;
}

R_Interpreter_Code*
onProcedureBody
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  onStatements(process, interpreterProcessState, code, variables, statements);
  return code;
}

void
onProcedureDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ProcedureDefinitionAst* definitionAst
  )
{
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->procedureName };
  Arcadia_Value v = R_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  R_List* variables = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(definitionAst->procedureParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = R_List_getAt(process, definitionAst->procedureParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    addVariable(process, variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->procedureBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = R_Map_get(process, foreignProcedures, k);
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
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_create(process, definitionAst->procedureName, onProcedureBody(process, interpreterProcessState, variables, definitionAst->procedureBody));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, interpreterProcessState, procedure);
  }
}

void
onConstructorDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_ConstructorDefinitionAst* definitionAst
  )
{
  Arcadia_String* name = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getBackendNoLock(process), u8"<constructor>", c_strlen(u8"<constructor>")));
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name };
  Arcadia_Value v = R_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  R_List* variables = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(definitionAst->constructorParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = R_List_getAt(process, definitionAst->constructorParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    addVariable(process, variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->constructorBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = R_Map_get(process, foreignProcedures, k);
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
    R_Interpreter_Constructor* constructor = R_Interpreter_Constructor_create(process, onConstructorBody(process, interpreterProcessState, variables, definitionAst->constructorBody));
    R_Interpreter_Class_addConstructor(process, enclosing, constructor);
  }
}

void
onMethodDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_MethodDefinitionAst* definitionAst
  )
{
  Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->methodName };
  Arcadia_Value v = R_Map_get(process, symbolTable, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  R_List* variables = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(definitionAst->methodParameters); i < n; ++i) {
    Arcadia_Value variableNameValue = R_List_getAt(process, definitionAst->methodParameters, i);
    Arcadia_String* variableNameString = R_Argument_getObjectReferenceValue(process, &variableNameValue, _Arcadia_String_getType(process));
    addVariable(process, variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->methodBody) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    Arcadia_Value v = R_Map_get(process, foreignProcedures, k);
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
    R_Interpreter_Method* method = R_Interpreter_Method_create(process, definitionAst->methodName, onMethodBody(process, interpreterProcessState, variables, definitionAst->methodBody));
    R_Interpreter_Class_addMethod(process, enclosing, method);
  }
}

void
onVariableDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_VariableDefinitionAst* definitionAst
  )
{ }

void
onClassBodyDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_List* classBodyAst
  )
{
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(classBodyAst); i < n; ++i) {
    Arcadia_ObjectReferenceValue element = R_List_getObjectReferenceValueAt(process, classBodyAst, i);
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _R_Mil_ConstructorDefinitionAst_getType(process))) {
      onConstructorDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _R_Mil_MethodDefinitionAst_getType(process))) {
      onMethodDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(element), _R_Mil_VariableDefinitionAst_getType(process))) {
      onVariableDefinition(process, interpreterProcessState, symbolTable, foreignProcedures, enclosing, element);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
}

void
onClassDefinition
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ClassDefinitionAst* definitionAst
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
