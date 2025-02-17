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

#if !defined(ARCADIA_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED)
#define ARCADIA_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED

#include "R/Mil/Asts/ExpressionAst.h"
typedef struct Arcadia_Mil_OperandAst Arcadia_Mil_OperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum Arcadia_Mil_BinaryExpressionAstType Arcadia_Mil_BinaryExpressionAstType;

enum Arcadia_Mil_BinaryExpressionAstType {
  Arcadia_Mil_BinaryExpressionAstType_Add = 1,
  Arcadia_Mil_BinaryExpressionAstType_And = 2,
  Arcadia_Mil_BinaryExpressionAstType_Concatenate = 3,
  Arcadia_Mil_BinaryExpressionAstType_Divide = 4,
  Arcadia_Mil_BinaryExpressionAstType_Multiply = 5,
  Arcadia_Mil_BinaryExpressionAstType_Or = 6,
  Arcadia_Mil_BinaryExpressionAstType_Subtract = 7,
  Arcadia_Mil_BinaryExpressionAstType_IsEqualTo = 8,
  Arcadia_Mil_BinaryExpressionAstType_IsNotEqualTo = 9,
  Arcadia_Mil_BinaryExpressionAstType_IsLowerThan = 10,
  Arcadia_Mil_BinaryExpressionAstType_IsLowerThanOrEqualTo = 11,
  Arcadia_Mil_BinaryExpressionAstType_IsGreaterThan = 12,
  Arcadia_Mil_BinaryExpressionAstType_IsGreaterThanOrEqualTo = 13,
};

/// @code
/// class Arcadia.Mil.BinaryOperationExpressionAst extends Arcadia.Mil.ExpressionAst
/// @endcode
/// Represents a binary operations like
/// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType(u8"Arcadia.Mil.BinaryExpressionAst", Arcadia_Mil_BinaryExpressionAst, u8"Arcadia.Mil.ExpressionAst");

struct Arcadia_Mil_BinaryExpressionAst {
  Arcadia_Mil_ExpressionAst parent;
  Arcadia_Mil_BinaryExpressionAstType type;
  Arcadia_Mil_OperandAst* operand1;
  Arcadia_Mil_OperandAst* operand2;
};

Arcadia_Mil_BinaryExpressionAst*
Arcadia_Mil_BinaryExpressionAst_create
  (
    Arcadia_Process* process,
    Arcadia_Mil_BinaryExpressionAstType type,
    Arcadia_Mil_OperandAst* operand1,
    Arcadia_Mil_OperandAst* operand2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_MIL_ASTS_BINARYEXPRESSIONAST_H_INCLUDED
