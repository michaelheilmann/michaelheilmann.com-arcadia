// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_MILC_AST_OPERANDS_LITERALOPERANDNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_OPERANDS_LITERALOPERANDNODE_H_INCLUDED

#include "Arcadia/MILC/AST/OperandNode.h"

/// @code
/// class Arcadia.MILC.AST.LiteralOperandNode extends Arcadia.MILC.AST.OperandNode {
///   ...
/// }
/// @endcode
/// represents
/// @code
/// lexical.literal
/// @endcode
/// in the @a operand context.
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.LiteralOperandNode", Arcadia_MILC_AST_LiteralOperandNode,
                          u8"Arcadia.MIL.OperandAst");

struct Arcadia_MILC_AST_LiteralOperandNodeDispatch {
  Arcadia_MILC_AST_OperandNodeDispatch parent;
};

struct Arcadia_MILC_AST_LiteralOperandNode {
  Arcadia_MILC_AST_OperandNode parent;
  Arcadia_MILC_AST_Node* literal;
};

Arcadia_MILC_AST_LiteralOperandNode*
Arcadia_MILC_AST_LiteralOperandNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Node* literal
  );

#endif // ARCADIA_MILC_AST_OPERANDS_LITERALOPERANDNODE_H_INCLUDED
