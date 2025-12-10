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

#if !defined(ARCADIA_DDL_TREE_VOIDNODE_H_INCLUDED)
#define ARCADIA_DDL_TREE_VOIDNODE_H_INCLUDED

#if !defined(ARCADIA_DDL_NODES_PRIVATE) || 1 != ARCADIA_DDL_NODES_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Nodes/Include.h` instead")
#endif
#include "Arcadia/DDL/Nodes/Node.h"

Arcadia_declareObjectType(u8"Arcadia.DDL.VoidNode", Arcadia_DDL_VoidNode,
                          u8"Arcadia.DDL.Node");

struct Arcadia_DDL_VoidNodeDispatch {
  Arcadia_DDL_NodeDispatch _parent;
};

struct Arcadia_DDL_VoidNode {
  Arcadia_DDL_Node parent;
  Arcadia_String* value;
};

Arcadia_DDL_VoidNode*
Arcadia_DDL_VoidNode_createVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  );

// A writer which consumes a boolean node always checks if the string is a valid void literal string.
// If a reader produces a void node, its string is valid void literal string.
Arcadia_DDL_VoidNode*
Arcadia_DDL_VoidNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_String* stringValue
  );

#endif // ARCADIA_DDL_TREE_VOIDNODE_H_INCLUDED
