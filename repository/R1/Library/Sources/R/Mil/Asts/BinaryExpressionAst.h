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

#if !defined(R_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED)
#define R_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED

#include "R/Mil/Asts/ExpressionAst.h"
typedef struct R_Mil_OperandAst R_Mil_OperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum R_Mil_BinaryExpressionAstType R_Mil_BinaryExpressionAstType;

enum R_Mil_BinaryExpressionAstType {
  R_Mil_BinaryExpressionAstType_Add = 1,
  R_Mil_BinaryExpressionAstType_And = 2,
  R_Mil_BinaryExpressionAstType_Concatenate = 3,
  R_Mil_BinaryExpressionAstType_Divide = 4,
  R_Mil_BinaryExpressionAstType_Multiply = 5,
  R_Mil_BinaryExpressionAstType_Or = 6,
  R_Mil_BinaryExpressionAstType_Subtract = 7,
};

/// @code
/// class R.Mil.BinaryOperationExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents a binary operations like
/// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType(u8"R.Mil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, u8"R.Mil.ExpressionAst");

struct R_Mil_BinaryExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_BinaryExpressionAstType type;
  R_Mil_OperandAst* operand1;
  R_Mil_OperandAst* operand2;
};

R_Mil_BinaryExpressionAst*
R_Mil_BinaryExpressionAst_create
  (
    Arcadia_Process* process,
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED
