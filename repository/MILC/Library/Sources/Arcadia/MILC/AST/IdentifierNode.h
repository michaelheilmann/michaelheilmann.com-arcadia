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

#if !defined(ARCADIA_MILC_AST_IDENTIFIERNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_IDENTIFIERNODE_H_INCLUDED

#include "Arcadia/MILC/AST/Node.h"
#include "Arcadia/Collections/Include.h"

/// @code
/// class Arcadia.MILC.AST.ExpressionNode extends Arcadia.MILC.AST.Node {
///   ...
/// }
/// @endcode
/// represents
/// @code
/// identifier : lexical.name (`.` lexical.name)*
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.IdentifierNode", Arcadia_MILC_AST_IdentifierNode,
                          u8"Arcadia.MILC.AST.Node");

struct Arcadia_MILC_AST_IdentifierNodeDispatch {
  Arcadia_MILC_AST_NodeDispatch _parent;
};

struct Arcadia_MILC_AST_IdentifierNode {
  Arcadia_MILC_AST_Node _parent;
  Arcadia_ImmutableList* names;
};

Arcadia_MILC_AST_IdentifierNode*
Arcadia_MILC_AST_IdentifierNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* names
  );

#endif // ARCADIA_MILC_AST_IDENTIFIERNODE_H_INCLUDED
