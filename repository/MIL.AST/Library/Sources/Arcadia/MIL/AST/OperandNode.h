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

#if !defined(ARCADIA_MIL_AST_OPERANDS_OPERANDNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_OPERANDS_OPERANDNODE_H_INCLUDED

#include "Arcadia/MIL/AST/Node.h"

/// @code
/// class Arcadia.MIL.AST.OperandNode extends Arcadia.MIL.AST.Node {
///   ...
/// }
/// @endcode
/// represents
/// @code
/// operand : booleanLiteralOperand
///         | numberLiteralOperand
///         | stringLiteralOperand
///         | variableOperand
///         | registerOperand
/// variableOperand : lexical.string | lexical.name
/// registerOperand : lexical.register
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.OperandNode", Arcadia_MIL_AST_OperandNode,
                          u8"Arcadia.MIL.AST.Node");

struct Arcadia_MIL_AST_OperandNode {
  Arcadia_MIL_AST_Node _parent;
};

#endif // ARCADIA_MIL_AST_OPERANDS_OPERANDNODE_H_INCLUDED
