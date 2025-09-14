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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/ExpressionAst.h"
typedef struct Arcadia_MIL_VariableOperandAst Arcadia_MIL_VariableOperandAst;

/// @code
/// class Arcadia.MIL.InvokeExpressionAst extends Arcadia.MIL.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// invoke variableOperand '(' (operand (',' operand)*)? ')'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.InvokeExpressionAst", Arcadia_MIL_InvokeExpressionAst,
                          u8"Arcadia.MIL.ExpressionAst");

struct Arcadia_MIL_InvokeExpressionAst {
  Arcadia_MIL_ExpressionAst parent;
  Arcadia_MIL_VariableOperandAst* callee;
  Arcadia_List* operands;
};

Arcadia_MIL_InvokeExpressionAst*
Arcadia_MIL_InvokeExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_VariableOperandAst* callee,
    Arcadia_List* operands
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED
