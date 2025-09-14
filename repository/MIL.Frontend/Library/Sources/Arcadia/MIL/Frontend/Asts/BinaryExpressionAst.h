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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_BINARYEXPRESSIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_BINARYEXPRESSIONAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/ExpressionAst.h"
typedef struct Arcadia_MIL_OperandAst Arcadia_MIL_OperandAst;

/// @todo Use Arcadia_(declare/defined)EnumerationType.
typedef enum Arcadia_MIL_BinaryExpressionAstType Arcadia_MIL_BinaryExpressionAstType;

enum Arcadia_MIL_BinaryExpressionAstType {
  Arcadia_MIL_BinaryExpressionAstType_Add = 1,
  Arcadia_MIL_BinaryExpressionAstType_And = 2,
  Arcadia_MIL_BinaryExpressionAstType_Concatenate = 3,
  Arcadia_MIL_BinaryExpressionAstType_Divide = 4,
  Arcadia_MIL_BinaryExpressionAstType_Multiply = 5,
  Arcadia_MIL_BinaryExpressionAstType_Or = 6,
  Arcadia_MIL_BinaryExpressionAstType_Subtract = 7,
  Arcadia_MIL_BinaryExpressionAstType_IsEqualTo = 8,
  Arcadia_MIL_BinaryExpressionAstType_IsNotEqualTo = 9,
  Arcadia_MIL_BinaryExpressionAstType_IsLowerThan = 10,
  Arcadia_MIL_BinaryExpressionAstType_IsLowerThanOrEqualTo = 11,
  Arcadia_MIL_BinaryExpressionAstType_IsGreaterThan = 12,
  Arcadia_MIL_BinaryExpressionAstType_IsGreaterThanOrEqualTo = 13,
};

/// @code
/// class Arcadia.MIL.BinaryOperationExpressionAst extends Arcadia.MIL.ExpressionAst
/// @endcode
/// Represents a binary operations like
/// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.BinaryExpressionAst", Arcadia_MIL_BinaryExpressionAst,
                          u8"Arcadia.MIL.ExpressionAst");

struct Arcadia_MIL_BinaryExpressionAst {
  Arcadia_MIL_ExpressionAst parent;
  Arcadia_MIL_BinaryExpressionAstType type;
  Arcadia_MIL_OperandAst* operand1;
  Arcadia_MIL_OperandAst* operand2;
};

Arcadia_MIL_BinaryExpressionAst*
Arcadia_MIL_BinaryExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_BinaryExpressionAstType type,
    Arcadia_MIL_OperandAst* operand1,
    Arcadia_MIL_OperandAst* operand2
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_BINARYEXPRESSIONAST_H_INCLUDED
