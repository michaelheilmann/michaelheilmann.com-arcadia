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

#if !defined(R_MIL_ENTER_H_INCLUDED)
#define R_MIL_ENTER_H_INCLUDED

#include "R.h"
#include "R/Mil/Include.h"

void
onOperand
  (
    R_Interpreter_ProcessState* process,
    R_Interpreter_Code* code,
    R_Mil_OperandAst* operand
  );

R_Interpreter_Code*
onConstructorBody
  (
    R_List* statements
  );

void
onConstructorDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_ConstructorDefinitionAst* definitionAst
  );

R_Interpreter_Code*
onMethodBody
  (
    R_List* statements
  );

void
onMethodDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_MethodDefinitionAst* definitionAst
  );

R_Interpreter_Code*
onProcedureBody
  (
    R_List* statements
  );

void
onProcedureDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ProcedureDefinitionAst* definitionAst
  );

void
onVariableDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_Mil_VariableDefinitionAst* definitionAst
  );

void
onClassBodyDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Interpreter_Class* enclosing,
    R_List* classBodyAst
  );

void
onClassDefinition
  (
    R_Interpreter_ProcessState* process,
    R_Map* symbolTable,
    R_Map* foreignProcedures,
    R_Mil_ClassDefinitionAst* definitionAst
  );

#endif // R_MIL_ENTER_H_INCLUDED
