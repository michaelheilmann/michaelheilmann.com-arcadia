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

#if !defined(ARCADIA_DDLS_NODES_NODE_H_INCLUDED)
#define ARCADIA_DDLS_NODES_NODE_H_INCLUDED

#if !defined(ARCADIA_DDLS_NODES_PRIVATE) || 1 != ARCADIA_DDLS_NODES_PRIVATE
  #error("do not include directly, include `Arcadia/DDLS/Nodes/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

/// The base of all nodes.
Arcadia_declareObjectType(u8"Arcadia.DDLS.Node", Arcadia_DDLS_Node,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_NodeDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_DDLS_Node {
  Arcadia_Object parent;
};

#endif // ARCADIA_DDLS_NODES_NODE_H_INCLUDED
