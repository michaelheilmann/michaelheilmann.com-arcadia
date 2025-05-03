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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_UNARYEXPRESSIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_UNARYEXPRESSIONAST_H_INCLUDED

#include "Arcadia/Mil/Frontend/Asts/ExpressionAst.h"
typedef struct Arcadia_Mil_OperandAst Arcadia_Mil_OperandAst;

/// @todo Use Arcadia_(declare/defined)EnumerationType.
typedef enum Arcadia_Mil_UnaryExpressionAstType Arcadia_Mil_UnaryExpressionAstType;

enum Arcadia_Mil_UnaryExpressionAstType {
  Arcadia_Mil_UnaryExpressionAstType_Negate = 1,
  Arcadia_Mil_UnaryExpressionAstType_Not = 2,
};

/// @code
/// class Arcadia.Mil.UnaryExpressionAst extends Arcadia.Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// (negate|not) <operand1>
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.UnaryExpressionAst", Arcadia_Mil_UnaryExpressionAst, u8"Arcadia.Mil.ExpressionAst");

struct Arcadia_Mil_UnaryExpressionAst {
  Arcadia_Mil_ExpressionAst parent;
  Arcadia_Mil_UnaryExpressionAstType type;
  Arcadia_Mil_OperandAst* operand1;
};

Arcadia_Mil_UnaryExpressionAst*
Arcadia_Mil_UnaryExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_UnaryExpressionAstType type,
    Arcadia_Mil_OperandAst* operand1
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_UNARYEXPRESSIONAST_H_INCLUDED
