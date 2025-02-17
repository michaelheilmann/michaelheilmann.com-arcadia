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

#if !defined(ARCADIA_MIL_CALLABLECONTEXT_H_INCLUDED)
#define ARCADIA_MIL_CALLABLECONTEXT_H_INCLUDED

#include "R/Include.h"
#include "R/Mil/Include.h"
typedef struct Arcadia_Mil_VariableDefinitionStatementAst Arcadia_Mil_VariableDefinitionStatementAst;

/// @brief Context for compiling a sequence of statements.
Rex_declareObjectType("Arcadia.Mil.CallableContext", Arcadia_Mil_CallableContext, "Arcadia.Object");

struct Arcadia_Mil_CallableContext {
  Arcadia_Object _parent;
  /// The zero-based index of the statement to be emitted.
  Arcadia_Natural32Value statementIndex;
  /// Set of label definitions.
  Arcadia_Map* labels;
  /// Set of variable definitions.
  Arcadia_List* variables;
};

Arcadia_Mil_CallableContext*
Arcadia_Mil_CallableContext_create
  (
    Arcadia_Process* process
  );

/// @brief Reset the statements context to is initial state.
/// @param process A pointer to this process.
/// @param self A pointer to this context.
void
Arcadia_Mil_CallableContext_onReset
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self
  );

/// @brief Add an entry name -> ast.
/// @param process A pointer to this process.
/// @param self A pointer to this context.
/// @error Arcadia_Status_SemanticalError an entry with the specified name already exists
void
Arcadia_Mil_CallableContext_onDefineLabel
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_LabelStatementAst* ast,
    Arcadia_Natural32Value instructionIndex
  );

/// @param process A pointer to this process.
/// @param self A pointer to this context.
void
Arcadia_Mil_CallableContext_onParameterVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_Ast* ast
  );

/// @param process A pointer to this process.
/// @param self A pointer to this context.
void
Arcadia_Mil_CallableContext_onLocalVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_VariableDefinitionStatementAst* ast
  );

#endif // ARCADIA_MIL_CALLABLECONTEXT_H_INCLUDED
