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

// Last modified: 2025-01-01

#if !defined(R_MIL_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED)
#define R_MIL_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED

#include "R/Mil/Asts/StatementAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.VariableDefinitionStatement extends R.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'variable' VariableName
/// @endcode
Rex_declareObjectType(u8"R.Mil.VariableDefinitionStatementAst", R_Mil_VariableDefinitionStatementAst, u8"R.Mil.StatementAst");

struct R_Mil_VariableDefinitionStatementAst {
  R_Mil_StatementAst parent;
  Arcadia_String* name;
};

/// @brief Create a Mil variable definition statement AST.
/// @return A pointer to this Mil variable definition statement AST.
R_Mil_VariableDefinitionStatementAst*
R_Mil_VariableDefinitionStatementAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED
