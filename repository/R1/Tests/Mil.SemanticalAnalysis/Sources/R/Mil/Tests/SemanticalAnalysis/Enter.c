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

// Last modified: 2024-10-18

#include "R/Mil/Tests/SemanticalAnalysis/Enter.h"

#include "R.h"
#include "R/Interpreter/Constructor.h"
#include "R/Interpreter/Method.h"
#include "R/Mil/Include.h"
#include "R/cstdlib.h"
#include "R/ArgumentsValidation.h"

void addVariable(R_List* variables, R_String* name) {
  for (R_SizeValue i = 0, n = R_List_getSize(variables); i < n; ++i) {
    R_Value value = R_List_getAt(variables, i);
    if (R_Object_equalTo((R_Object*)name, &value)) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
  }
}

R_Natural32Value getRegisterOfVariable(R_List* variables, R_String* name) {
  for (R_SizeValue i = 0, n = R_List_getSize(variables); i < n; ++i) {
    R_Value value = R_List_getAt(variables, i);
    if (R_Object_equalTo((R_Object*)name, &value)) {
      return i;
    }
  }
  R_List_appendObjectReferenceValue(variables, name);
  return R_List_getSize(variables) - 1;
}

void
onOperand
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_OperandAst* operandAst
  )
{
  if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_VariableOperandAst_getType())) {
    R_Mil_VariableOperandAst* variableOperandAst = (R_Mil_VariableOperandAst*)operandAst;
    R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                            getRegisterOfVariable(variables, variableOperandAst->value));
  } else if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_BooleanLiteralOperandAst_getType())) {
    R_Mil_BooleanLiteralOperandAst* booleanLiteralOperandAst = (R_Mil_BooleanLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateBoolean(R_Interpreter_ProcessState_getConstants(process), R_String_toBoolean(booleanLiteralOperandAst->value));
  } else if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_IntegerLiteralOperandAst_getType())) {
    R_Mil_IntegerLiteralOperandAst* integerLiteralOperandAst = (R_Mil_IntegerLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateInteger64(R_Interpreter_ProcessState_getConstants(process), R_String_toInteger64(integerLiteralOperandAst->value));
  } else if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_RealLiteralOperandAst_getType())) {
    R_Mil_RealLiteralOperandAst* realLiteralOperandAst = (R_Mil_RealLiteralOperandAst*)operandAst;
    R_String_toReal64(realLiteralOperandAst->value);
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  } else if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_StringLiteralOperandAst_getType())) {
    R_Mil_StringLiteralOperandAst* stringLiteralOperandAst = (R_Mil_StringLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateString(R_Interpreter_ProcessState_getConstants(process), stringLiteralOperandAst->value);
  } else if (R_Type_isSubType(R_Object_getType(operandAst), _R_Mil_VoidLiteralOperandAst_getType())) {
    R_Mil_VoidLiteralOperandAst* voidLiteralOperandAst = (R_Mil_VoidLiteralOperandAst*)operandAst;
    R_Interpreter_Code_Constants_getOrCreateVoid(R_Interpreter_ProcessState_getConstants(process), R_String_toVoid(voidLiteralOperandAst->value));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

void
onExpressionStatement
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_ExpressionStatementAst* expressionStatementAst
  )
{
  R_Mil_ExpressionAst* expressionAst = R_Mil_ExpressionStatementAst_getExpression(expressionStatementAst);
  if (R_Type_isSubType(R_Object_getType(expressionAst), _R_Mil_BinaryExpressionAst_getType())) {
    R_Mil_BinaryExpressionAst* binaryExpressionAst = (R_Mil_BinaryExpressionAst*)expressionAst;
    switch (binaryExpressionAst->type) {
      case R_Mil_BinaryExpressionAstType_Add: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Add;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, binaryExpressionAst->operand1);
        onOperand(process, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Subtract: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Subtract;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, binaryExpressionAst->operand1);
        onOperand(process, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Multiply: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Multiply;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, binaryExpressionAst->operand1);
        onOperand(process, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Divide: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Divide;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, binaryExpressionAst->operand1);
        onOperand(process, code, variables, binaryExpressionAst->operand2);
      } break;
      case R_Mil_BinaryExpressionAstType_Concatenate: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Concatenate;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, binaryExpressionAst->operand1);
        onOperand(process, code, variables, binaryExpressionAst->operand2);
      } break;
      default: {
        R_setStatus(R_Status_ArgumentTypeInvalid);
        R_jump();
      } break;
    };
  } else if (R_Type_isSubType(R_Object_getType(expressionAst), _R_Mil_UnaryExpressionAst_getType())) {
    R_Mil_UnaryExpressionAst* unaryExpressionAst = (R_Mil_UnaryExpressionAst*)expressionAst;
    switch (unaryExpressionAst->type) {
      case R_Mil_UnaryExpressionAstType_Negate: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Negate;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, unaryExpressionAst->operand1);
      } break;
      case R_Mil_UnaryExpressionAstType_Not: {
        R_Natural8Value opcode = R_Machine_Code_Opcode_Not;
        R_Interpreter_Code_append(code, &opcode, 1);
        R_Interpreter_Code_appendIndexNatural32(code, R_Machine_Code_IndexKind_Register,
                                                getRegisterOfVariable(variables, expressionStatementAst->targetVariableName));
        onOperand(process, code, variables, unaryExpressionAst->operand1);
      } break;
      default: {
        R_setStatus(R_Status_ArgumentTypeInvalid);
        R_jump();
      } break;
    };
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

void
onVariableDefinitionStatement
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_List* variables,
    R_Mil_VariableDefinitionAst* variableDefinitionStatement
  )
{
  addVariable(variables, variableDefinitionStatement->variableName);
}

void
onStatements
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_List* variables,
    R_List* statements
  )
{
  for (R_SizeValue i = 0, n = R_List_getSize(statements); i < n; ++i) {
    R_Value elementValue = R_List_getAt(statements, i);
    R_ObjectReferenceValue objectElementValue = R_Value_getObjectReferenceValue(&elementValue);
    R_Mil_StatementAst* statement = (R_Mil_StatementAst*)objectElementValue;
    if (R_Type_isSubType(R_Object_getType(statement), _R_Mil_ExpressionStatementAst_getType())) {
      onExpressionStatement(process, code, variables, (R_Mil_ExpressionStatementAst*)statement);
    } else if (R_Type_isSubType(R_Object_getType(statement), _R_Mil_VariableDefinitionAst_getType())) {
      onVariableDefinitionStatement(process, code, variables, (R_Mil_VariableDefinitionAst*)statement);
    } else {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
  }
}

R_Interpreter_Code*
onConstructorBody
  (
    R_Interpreter_ProcessState* process,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  onStatements(process, code, variables, statements);
  return code;
}

R_Interpreter_Code*
onMethodBody
  (
    R_Interpreter_ProcessState* process,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  onStatements(process, code, variables, statements);
  return code;
}

R_Interpreter_Code*
onProcedureBody
  (
    R_Interpreter_ProcessState* process,
    R_List* variables,
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  onStatements(process, code, variables, statements);
  return code;
}

void
onProcedureDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ProcedureDefinitionAst* definitionAst
  )
{
  R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->procedureName };
  R_Value v = R_Map_get(symbolTable, k);
  if (!R_Value_isVoidValue(&v)) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  R_List* variables = R_List_create();
  for (R_SizeValue i = 0, n = R_List_getSize(definitionAst->procedureParameters); i < n; ++i) {
    R_Value variableNameValue = R_List_getAt(definitionAst->procedureParameters, i);
    R_String* variableNameString = R_Argument_getObjectReferenceValue(&variableNameValue, _R_String_getType());
    addVariable(variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->procedureBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    R_Value v = R_Map_get(foreignProcedures, k);
    if (R_Value_isVoidValue(&v)) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_createForeign(definitionAst->procedureName, R_Value_getForeignProcedureValue(&v));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, procedure);
  } else {
    if (!definitionAst->procedureBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_create(definitionAst->procedureName, onProcedureBody(process, variables, definitionAst->procedureBody));
    R_Interpreter_ProcessState_defineGlobalProcedure(process, procedure);
  }
}

void
onConstructorDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_ConstructorDefinitionAst* definitionAst
  )
{
  R_String* name = R_String_create_pn(R_ImmutableByteArray_create("<constructor>", c_strlen("<constructor>")));
  R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
  R_Value v = R_Map_get(symbolTable, k);
  if (!R_Value_isVoidValue(&v)) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  R_List* variables = R_List_create();
  for (R_SizeValue i = 0, n = R_List_getSize(definitionAst->constructorParameters); i < n; ++i) {
    R_Value variableNameValue = R_List_getAt(definitionAst->constructorParameters, i);
    R_String* variableNameString = R_Argument_getObjectReferenceValue(&variableNameValue, _R_String_getType());
    addVariable(variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->constructorBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    R_Value v = R_Map_get(foreignProcedures, k);
    if (R_Value_isVoidValue(&v)) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Constructor* construcor = R_Interpreter_Constructor_createForeign(R_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addConstructor(enclosing, construcor);
  } else {
    if (!definitionAst->constructorBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Constructor* constructor = R_Interpreter_Constructor_create(onConstructorBody(process, variables, definitionAst->constructorBody));
    R_Interpreter_Class_addConstructor(enclosing, constructor);
  }
}

void
onMethodDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_MethodDefinitionAst* definitionAst
  )
{
  R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->methodName };
  R_Value v = R_Map_get(symbolTable, k);
  if (!R_Value_isVoidValue(&v)) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  R_List* variables = R_List_create();
  for (R_SizeValue i = 0, n = R_List_getSize(definitionAst->methodParameters); i < n; ++i) {
    R_Value variableNameValue = R_List_getAt(definitionAst->methodParameters, i);
    R_String* variableNameString = R_Argument_getObjectReferenceValue(&variableNameValue, _R_String_getType());
    addVariable(variables, variableNameString);
  }
  if (definitionAst->nativeName) {
    if (definitionAst->methodBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = definitionAst->nativeName };
    R_Value v = R_Map_get(foreignProcedures, k);
    if (R_Value_isVoidValue(&v)) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Method* method = R_Interpreter_Method_createForeign(definitionAst->methodName, R_Value_getForeignProcedureValue(&v));
    R_Interpreter_Class_addMethod(enclosing, method);
  } else {
    if (!definitionAst->methodBody) {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
    R_Interpreter_Method* method = R_Interpreter_Method_create(definitionAst->methodName, onMethodBody(process, variables, definitionAst->methodBody));
    R_Interpreter_Class_addMethod(enclosing, method);
  }
}

void
onVariableDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_VariableDefinitionAst* definitionAst
  )
{ }

void
onClassBodyDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_List* classBodyAst
  )
{
  for (R_SizeValue i = 0, n = R_List_getSize(classBodyAst); i < n; ++i) {
    R_ObjectReferenceValue element = R_List_getObjectReferenceValueAt(classBodyAst, i);
    if (R_Type_isSubType(R_Object_getType(element), _R_Mil_ConstructorDefinitionAst_getType())) {
      onConstructorDefinition(process, symbolTable, foreignProcedures, enclosing, element);
    } else if (R_Type_isSubType(R_Object_getType(element), _R_Mil_MethodDefinitionAst_getType())) {
      onMethodDefinition(process, symbolTable, foreignProcedures, enclosing, element);
    } else if (R_Type_isSubType(R_Object_getType(element), _R_Mil_VariableDefinitionAst_getType())) {
      onVariableDefinition(process, symbolTable, foreignProcedures, enclosing, element);
    } else {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
  }
}

void
onClassDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ClassDefinitionAst* definitionAst
  )
{
  R_Interpreter_Class* class = R_Interpreter_Class_create(definitionAst->className, definitionAst->extendedClassName);
  if (!definitionAst->classBody) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  onClassBodyDefinition(process, symbolTable, foreignProcedures, class, definitionAst->classBody);
  R_Interpreter_ProcessState_defineGlobalClass(process, class);
}
