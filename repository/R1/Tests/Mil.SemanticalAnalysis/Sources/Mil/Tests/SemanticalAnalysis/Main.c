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

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R/Mil/Parser.h"
#include "R/Mil/Ast.h"

static void
R_Library_print
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{/*Intentionally empty.*/}

static void
R_Library_main
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{/*Intentionally empty.*/}

static void
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

static R_Interpreter_Code*
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

static void
testNativePrintProcedure
  (
  )
{
  R_Map* foreignProcedures = R_Map_create();
#define Define(Name,Function) \
  { \
    R_Value v = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = R_String_create_pn(R_ImmutableByteArray_create(Name, sizeof(Name) - 1)) }; \
    R_Value k = { .tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = &Function }; \
    R_Map_set(foreignProcedures, k, v); \
  }
  Define("print", R_Library_print)
  Define("main", R_Library_main)
#undef Define
  static const char* input =
    u8"procedure native \"print\" print (a)\n"
    u8"procedure entry native \"main\" main()\n"
    ;
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(R_ImmutableByteArray_create(input, strlen(input)))));
  R_Mil_ModuleAst* moduleAst = R_Mil_Parser_run(parser);
  
  R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_create();
  for (R_SizeValue i = 0, n = R_Mil_ModuleAst_getNumberOfDefinitions(moduleAst); i < n; ++i) {
    R_Mil_DefinitionAst* definitionAst = R_Mil_ModuleAst_getDefinitionAt(moduleAst, i);
    if (R_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ClassDefinitionAst_getType())) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
      //R_Mil_ClassDefinitionAst* classDefinitionAst = (R_Mil_ClassDefinitionAst*)definitionAst;
    } else if (R_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ProcedureDefinitionAst_getType())) {
      R_Mil_ProcedureDefinitionAst* procedureDefinitionAst = (R_Mil_ProcedureDefinitionAst*)definitionAst;
      if (procedureDefinitionAst->nativeName) {
        R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue =  procedureDefinitionAst->nativeName };
        R_Value v = R_Map_get(foreignProcedures, k);
        if (R_Value_isVoidValue(&k)) {
          R_setStatus(R_Status_NotExists);
          R_jump();
        }
        R_Interpreter_ProcessState_defineGlobalForeignProcedure(process, procedureDefinitionAst->procedureName, R_Value_getForeignProcedureValue(&v));
      } else {
        R_Procedure* procedure = R_Procedure_create(onProcedureBody(procedureDefinitionAst->procedureBody));
        R_Interpreter_ProcessState_defineGlobalProcedure(process, procedureDefinitionAst->procedureName, procedure);
      }
    } else {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
  }
}

void
main1
  (
    int argc,
    char** argv
  )
{
  testNativePrintProcedure();
}

int
main
  (
    int argc,
    char** argv
  )
{
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
