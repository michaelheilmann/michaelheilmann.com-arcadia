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

#if !defined(R_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED)
#define R_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED

#include "R/Mil/Asts/StatementAst.h"
typedef struct R_Mil_OperandAst R_Mil_OperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ReturnStatementAst extends R.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Rex_declareObjectType(u8"R.Mil.ReturnStatementAst", R_Mil_ReturnStatementAst, u8"R.Mil.StatementAst");

struct R_Mil_ReturnStatementAst {
  R_Mil_StatementAst parent;
  R_Mil_OperandAst* operand;
};

/// @brief Create a Mil return statement AST.
/// @return A pointer to this Mil return statement AST.
R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    Arcadia_Process* process,
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED
