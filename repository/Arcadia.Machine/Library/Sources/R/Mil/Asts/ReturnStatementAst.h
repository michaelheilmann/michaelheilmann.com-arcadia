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

// Last modified: 2025-01-01

#if !defined(ARCADIA_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED

#include "R/Mil/Asts/StatementAst.h"
typedef struct Arcadia_Mil_OperandAst Arcadia_Mil_OperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Arcadia.Mil.ReturnStatementAst extends Arcadia.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.ReturnStatementAst", Arcadia_Mil_ReturnStatementAst, u8"Arcadia.Mil.StatementAst");

struct Arcadia_Mil_ReturnStatementAst {
  Arcadia_Mil_StatementAst parent;
  Arcadia_Mil_OperandAst* operand;
};

/// @brief Create a Mil return statement AST.
/// @return A pointer to this Mil return statement AST.
Arcadia_Mil_ReturnStatementAst*
Arcadia_Mil_ReturnStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_MIL_ASTS_RETURNSTATEMENTAST_H_INCLUDED
