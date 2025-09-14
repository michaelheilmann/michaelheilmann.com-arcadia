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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/StatementAst.h"
typedef struct Arcadia_MIL_ExpressionAst Arcadia_MIL_ExpressionAst;

/// @code
/// class Arcadia.MIL.ExpressionStatementAst extends Arcadia.MIL.Statement
/// @endcode
/// represents
/// @code
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.ExpressionStatementAst", Arcadia_MIL_ExpressionStatementAst,
                          u8"Arcadia.MIL.StatementAst");

struct Arcadia_MIL_ExpressionStatementAst {
  Arcadia_MIL_StatementAst parent;
  Arcadia_String* targetVariableName;
  Arcadia_MIL_ExpressionAst* expression;
};

/// @brief Create a MIL expression statement AST.
/// @return A pointer to this MIL expression statement ASt.
Arcadia_MIL_ExpressionStatementAst*
Arcadia_MIL_ExpressionStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* targetVariableName,
    Arcadia_MIL_ExpressionAst* expression
  );

/// @brief Get the name of the target variable.
/// @param self This expression statement AST.
/// @return The name of the target variable.
Arcadia_String*
Arcadia_MIL_ExpressionStatementAst_getTargetVariableName
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  );

/// @brief Get the expression AST of the expression statement AST.
/// @param self This expression statement AST.
/// @return The expression AST.
Arcadia_MIL_ExpressionAst*
Arcadia_MIL_ExpressionStatementAst_getExpression
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ExpressionStatementAst* self
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_EXPRESSIONSTATEMENTAST_H_INCLUDED
