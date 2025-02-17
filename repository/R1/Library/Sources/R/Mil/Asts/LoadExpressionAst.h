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

#if !defined(ARCADIA_MIL_ASTS_LOADEXPRESSIONAST_H_INCLUDED)
#define ARCADIA_MIL_ASTS_LOADEXPRESSIONAST_H_INCLUDED

#include "R/Mil/Asts/ExpressionAst.h"
typedef struct Arcadia_Mil_OperandAst Arcadia_Mil_OperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Arcadia.Mil.LoadExpressionAst extends Arcadia.Mil.ExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// BooleanLiteral | NumberLiteral | StringLiteral | VariableName
/// @endcode
Rex_declareObjectType(u8"Arcadia.Mil.LoadExpressionAst", Arcadia_Mil_LoadExpressionAst, u8"Arcadia.Mil.ExpressionAst");

struct Arcadia_Mil_LoadExpressionAst {
  Arcadia_Mil_ExpressionAst parent;
  Arcadia_Mil_OperandAst* operand;
};

Arcadia_Mil_LoadExpressionAst*
Arcadia_Mil_LoadExpressionAst_create
  (
    Arcadia_Process* process,
    Arcadia_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_MIL_ASTS_LOADEXPRESSIONAST_H_INCLUDED
