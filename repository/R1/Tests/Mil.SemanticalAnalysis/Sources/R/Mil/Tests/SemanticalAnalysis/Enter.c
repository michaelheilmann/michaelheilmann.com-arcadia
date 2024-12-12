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

void
onOperand
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_Mil_OperandAst* operand
  )
{
  if (R_Type_isSubType(R_Object_getType(operand), _R_Mil_BooleanLiteralOperandAst_getType())) {
  } else if (R_Type_isSubType(R_Object_getType(operand), _R_Mil_NumberLiteralOperandAst_getType())) {
  } else if (R_Type_isSubType(R_Object_getType(operand), _R_Mil_VoidLiteralOperandAst_getType())) {
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

R_Interpreter_Code*
onConstructorBody
  (
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  for (R_SizeValue i = 0, n = R_List_getSize(statements); i < n; ++i) {
    R_Value elementValue = R_List_getAt(statements, i);
    R_ObjectReferenceValue objectElementValue = R_Value_getObjectReferenceValue(&elementValue);
    R_Mil_StatementAst* statement = (R_Mil_StatementAst*)objectElementValue;
    if (R_Type_isSubType(R_Object_getType(statement), _R_Mil_ExpressionStatementAst_getType())) {
      R_Mil_ExpressionStatementAst* expressionStatement = (R_Mil_ExpressionStatementAst*)statement;
      R_Mil_ExpressionAst* expression = R_Mil_ExpressionStatementAst_getExpression(expressionStatement);
      if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_BinaryExpressionAst_getType())) {
        R_Mil_BinaryExpressionAst* binaryExpression = (R_Mil_BinaryExpressionAst*)expression;
        switch (binaryExpression->type) {
          case R_Mil_BinaryExpressionAstType_Add: {
          } break;
          case R_Mil_BinaryExpressionAstType_Subtract: {
          } break;
          case R_Mil_BinaryExpressionAstType_Multiply: {
          } break;
          case R_Mil_BinaryExpressionAstType_Divide: {
          } break;
          case R_Mil_BinaryExpressionAstType_Concatenate: {
          } break;
          default: {
            R_setStatus(R_Status_ArgumentTypeInvalid);
            R_jump();
          } break;
        };
      } else if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_UnaryExpressionAst_getType())) {
        R_Mil_UnaryExpressionAst* unaryExpression = (R_Mil_UnaryExpressionAst*)expression;
        switch (unaryExpression->type) {
          case R_Mil_UnaryExpressionAstType_Negate: {
          } break;
          case R_Mil_UnaryExpressionAstType_Not: {
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
  }
  return code;
}

R_Interpreter_Code*
onMethodBody
  (
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  for (R_SizeValue i = 0, n = R_List_getSize(statements); i < n; ++i) {
    R_Value elementValue = R_List_getAt(statements, i);
    R_ObjectReferenceValue objectElementValue = R_Value_getObjectReferenceValue(&elementValue);
    R_Mil_StatementAst* statement = (R_Mil_StatementAst*)objectElementValue;
    if (R_Type_isSubType(R_Object_getType(statement), _R_Mil_ExpressionStatementAst_getType())) {
      R_Mil_ExpressionStatementAst* expressionStatement = (R_Mil_ExpressionStatementAst*)statement;
      R_Mil_ExpressionAst* expression = R_Mil_ExpressionStatementAst_getExpression(expressionStatement);
      if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_BinaryExpressionAst_getType())) {
        R_Mil_BinaryExpressionAst* binaryExpression = (R_Mil_BinaryExpressionAst*)expression;
        switch (binaryExpression->type) {
          case R_Mil_BinaryExpressionAstType_Add: {
          } break;
          case R_Mil_BinaryExpressionAstType_Subtract: {
          } break;
          case R_Mil_BinaryExpressionAstType_Multiply: {
          } break;
          case R_Mil_BinaryExpressionAstType_Divide: {
          } break;
          case R_Mil_BinaryExpressionAstType_Concatenate: {
          } break;
          default: {
            R_setStatus(R_Status_ArgumentTypeInvalid);
            R_jump();
          } break;
        };
      } else if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_UnaryExpressionAst_getType())) {
        R_Mil_UnaryExpressionAst* unaryExpression = (R_Mil_UnaryExpressionAst*)expression;
        switch (unaryExpression->type) {
          case R_Mil_UnaryExpressionAstType_Negate: {
          } break;
          case R_Mil_UnaryExpressionAstType_Not: {
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
  }
  return code;
}

R_Interpreter_Code*
onProcedureBody
  (
    R_List* statements
  )
{
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  for (R_SizeValue i = 0, n = R_List_getSize(statements); i < n; ++i) {
    R_Value elementValue = R_List_getAt(statements, i);
    R_ObjectReferenceValue objectElementValue = R_Value_getObjectReferenceValue(&elementValue);
    R_Mil_StatementAst* statement = (R_Mil_StatementAst*)objectElementValue;
    if (R_Type_isSubType(R_Object_getType(statement), _R_Mil_ExpressionStatementAst_getType())) {
      R_Mil_ExpressionStatementAst* expressionStatement = (R_Mil_ExpressionStatementAst*)statement;
      R_Mil_ExpressionAst* expression = R_Mil_ExpressionStatementAst_getExpression(expressionStatement);
      if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_BinaryExpressionAst_getType())) {
        R_Mil_BinaryExpressionAst* binaryExpression = (R_Mil_BinaryExpressionAst*)expression;
        switch (binaryExpression->type) {
          case R_Mil_BinaryExpressionAstType_Add: {
          } break;
          case R_Mil_BinaryExpressionAstType_Subtract: {
          } break;
          case R_Mil_BinaryExpressionAstType_Multiply: {
          } break;
          case R_Mil_BinaryExpressionAstType_Divide: {
          } break;
          case R_Mil_BinaryExpressionAstType_Concatenate: {
          } break;
          default: {
            R_setStatus(R_Status_ArgumentTypeInvalid);
            R_jump();
          } break;
        };
      } else if (R_Type_isSubType(R_Object_getType(expression), _R_Mil_UnaryExpressionAst_getType())) {
        R_Mil_UnaryExpressionAst* unaryExpression = (R_Mil_UnaryExpressionAst*)expression;
        switch (unaryExpression->type) {
          case R_Mil_UnaryExpressionAstType_Negate: {
          } break;
          case R_Mil_UnaryExpressionAstType_Not: {
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
  }
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
    R_Interpreter_Procedure* procedure = R_Interpreter_Procedure_create(definitionAst->procedureName, onProcedureBody(definitionAst->procedureBody));
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
    R_Interpreter_Constructor* constructor = R_Interpreter_Constructor_create(onConstructorBody(definitionAst->constructorBody));
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
    R_Interpreter_Method* method = R_Interpreter_Method_create(definitionAst->methodName, onMethodBody(definitionAst->methodBody));
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
