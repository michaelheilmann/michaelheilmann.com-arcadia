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

#if !defined(ARCADIA_MILC_AST_VOIDLITERALNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_VOIDLITERALNODE_H_INCLUDED

#include "Arcadia/MILC/AST/Node.h"

/// @code
/// class Arcadia.MILC.AST.VoidLiteralNode extends Arcadia.MILC.AST.Node
/// @endcode
/// represents
/// @code
/// voidLiteral : lexicalAnalysis.voidLiteral
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.VoidLiteralNode", Arcadia_MILC_AST_VoidLiteralNode,
                          u8"Arcadia.MILC.AST.Node");

struct Arcadia_MILC_AST_VoidLiteralNodeDispatch {
  Arcadia_MILC_AST_NodeDispatch parent;
};

struct Arcadia_MILC_AST_VoidLiteralNode {
  Arcadia_MILC_AST_Node parent;
  Arcadia_String* value;
};

Arcadia_MILC_AST_VoidLiteralNode*
Arcadia_MILC_AST_VoidLiteralNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  );

#endif // ARCADIA_MILC_AST_VOIDLITERALNODE_H_INCLUDED
