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

#if !defined(ARCADIA_MIL_AST_STATEMENTNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_STATEMENTNODE_H_INCLUDED

#include "Arcadia/MIL/AST/Node.h"

/// @code
/// class Arcadia.MIL.AST.StatementNode extends Arcadia.MIL.AST.Node {
///   ...
/// }
/// @endcode
/// represents
/// @code
/// definitionStatement
/// instructionStatement
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.StatementNode", Arcadia_MIL_AST_StatementNode,
                          u8"Arcadia.MIL.AST.Node");

struct Arcadia_MIL_AST_StatementNodeDispatch {
  Arcadia_MIL_AST_NodeDispatch _parent;
};

struct Arcadia_MIL_AST_StatementNode {
  Arcadia_MIL_AST_Node _parent;
};

#endif // ARCADIA_MIL_AST_STATEMENTNODE_H_INCLUDED
