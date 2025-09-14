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

#include "Arcadia/MIL/Frontend/Asts/ExpressionAst.h"
typedef struct Arcadia_MIL_OperandAst Arcadia_MIL_OperandAst;

/// @todo Use Arcadia_(declare/defined)EnumerationType.
typedef enum Arcadia_MIL_UnaryExpressionAstType Arcadia_MIL_UnaryExpressionAstType;

enum Arcadia_MIL_UnaryExpressionAstType {
  Arcadia_MIL_UnaryExpressionAstType_Negate = 1,
  Arcadia_MIL_UnaryExpressionAstType_Not = 2,
};

/// @code
/// class Arcadia.MIL.UnaryExpressionAst extends Arcadia.MIL.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// (negate|not) <operand1>
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.UnaryExpressionAst", Arcadia_MIL_UnaryExpressionAst, u8"Arcadia.MIL.ExpressionAst");

struct Arcadia_MIL_UnaryExpressionAst {
  Arcadia_MIL_ExpressionAst parent;
  Arcadia_MIL_UnaryExpressionAstType type;
  Arcadia_MIL_OperandAst* operand1;
};

Arcadia_MIL_UnaryExpressionAst*
Arcadia_MIL_UnaryExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_UnaryExpressionAstType type,
    Arcadia_MIL_OperandAst* operand1
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_UNARYEXPRESSIONAST_H_INCLUDED
