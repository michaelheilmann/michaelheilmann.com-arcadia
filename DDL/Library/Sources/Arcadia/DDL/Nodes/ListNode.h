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

#if !defined(ARCADIA_DDL_NODES_LISTNODE_H_INCLUDED)
#define ARCADIA_DDL_NODES_LISTNODE_H_INCLUDED

#if !defined(ARCADIA_DDL_NODES_PRIVATE) || 1 != ARCADIA_DDL_NODES_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Nodes/Include.h` instead")
#endif
#include "Arcadia/DDL/Nodes/Node.h"

Arcadia_declareObjectType(u8"Arcadia.DDL.ListNode", Arcadia_DDL_ListNode,
                          u8"Arcadia.DDL.Node");

struct Arcadia_DDL_ListNodeDispatch {
  Arcadia_DDL_NodeDispatch _parent;
};

struct Arcadia_DDL_ListNode {
  Arcadia_DDL_Node _parent;
  Arcadia_List* elements;
};

Arcadia_DDL_ListNode*
Arcadia_DDL_ListNode_create
  (
    Arcadia_Thread* thread
  );

Arcadia_SizeValue
Arcadia_DDL_ListNode_getNumberOfElements
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  );

#endif // ARCADIA_DDL_NODES_LISTNODE_H_INCLUDED
