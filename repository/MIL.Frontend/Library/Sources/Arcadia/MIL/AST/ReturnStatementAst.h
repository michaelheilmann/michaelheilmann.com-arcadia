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

#if !defined(ARCADIA_MIL_AST_RETURNSTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_AST_RETURNSTATEMENTAST_H_INCLUDED

#include "Arcadia/MIL/AST/StatementNode.h"
typedef struct Arcadia_MIL_AST_OperandNode Arcadia_MIL_AST_OperandNode;

/// @code
/// class Arcadia.MIL.ReturnStatementAst extends Arcadia.MIL.AST.StatementNode
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.ReturnStatementAst", Arcadia_MIL_ReturnStatementAst,
                          u8"Arcadia.MIL.AST.StatementNode");

struct Arcadia_MIL_ReturnStatementAst {
  Arcadia_MIL_AST_StatementNode parent;
  Arcadia_MIL_AST_OperandNode* operand;
};

/// @brief Create a MIL return statement AST.
/// @return A pointer to this MIL return statement AST.
Arcadia_MIL_ReturnStatementAst*
Arcadia_MIL_ReturnStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_OperandNode* operand
  );

#endif // ARCADIA_MIL_AST_RETURNSTATEMENTAST_H_INCLUDED
