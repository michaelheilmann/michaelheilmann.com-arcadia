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

#if !defined(ARCADIA_DDL_TREE_MAPENTRYNODE_H_INCLUDED)
#define ARCADIA_DDL_TREE_MAPENTRYNODE_H_INCLUDED

#if !defined(ARCADIA_DDL_PRIVATE) || 1 != ARCADIA_DDL_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Include.h` instead")
#endif

#include "Arcadia/DDL/Implementation/Node.h"
typedef struct Arcadia_DDL_NameNode Arcadia_DDL_NameNode;

Arcadia_declareObjectType(u8"Arcadia.DDL.MapEntryNode", Arcadia_DDL_MapEntryNode,
                          u8"Arcadia.DDL.Node");

struct Arcadia_DDL_MapEntryNode {
  Arcadia_DDL_Node parent;
  Arcadia_DDL_NameNode* key;
  Arcadia_DDL_Node* value;
};

Arcadia_DDL_MapEntryNode*
Arcadia_DDL_MapEntryNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* key,
    Arcadia_DDL_Node* value
  );

#endif // ARCADIA_DDL_TREE_MAPENTRYNODE_H_INCLUDED
