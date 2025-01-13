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

#if !defined(R_MIL_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED)
#define R_MIL_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED

#include "R/Mil/Asts/StatementAst.h"
typedef struct R_Mil_ExpressionAst R_Mil_ExpressionAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ExpressionStatementAst extends R.Mil.Statement
/// @endcode
/// Represents
Rex_declareObjectType(u8"R.Mil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, u8"R.Mil.StatementAst");

struct R_Mil_ExpressionStatementAst {
  R_Mil_StatementAst parent;
  Arcadia_String* targetVariableName;
  R_Mil_ExpressionAst* expression;
};

/// @brief Create a Mil expression statement AST.
/// @return A pointer to this Mil expression statement ASt.
R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  );

/// @brief Get the name of the target variable.
/// @param self This expression statement AST.
/// @return The name of the target variable.
Arcadia_String*
R_Mil_ExpressionStatementAst_getTargetVariableName
  (
    R_Mil_ExpressionStatementAst* self
  );

/// @brief Get the expression AST of the expression statement AST.
/// @param self This expression statement AST.
/// @return The expression AST.
R_Mil_ExpressionAst*
R_Mil_ExpressionStatementAst_getExpression
  (
    R_Mil_ExpressionStatementAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED
