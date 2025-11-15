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

#if !defined(ARCADIA_DDL_TREE_MAPNODE_H_INCLUDED)
#define ARCADIA_DDL_TREE_MAPNODE_H_INCLUDED

#if !defined(ARCADIA_DDL_PRIVATE) || 1 != ARCADIA_DDL_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Include.h` instead")
#endif

#include "Arcadia/DDL/Implementation/Node.h"
typedef struct Arcadia_DDL_MapEntryNode Arcadia_DDL_MapEntryNode;

// The map node is a list of map entry nodes.
Arcadia_declareObjectType(u8"Arcadia.DDL.MapNode", Arcadia_DDL_MapNode,
                          u8"Arcadia.DDL.Node");

struct Arcadia_DDL_MapNode {
  Arcadia_DDL_Node parent;
  Arcadia_List* entries;
};

Arcadia_DDL_MapNode*
Arcadia_DDL_MapNode_create
  (
    Arcadia_Thread* thread
  );

/// @brief Get if this map node has different map entries with the same keys.
/// @param thread Pointer to this thread.
/// @param self Pointer to this map node.
/// @return #Arcadia_BooleanValue_True if there are collision, #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_DDL_MapNode_hasCollisions
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self
  );

void
Arcadia_DDL_MapNode_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_DDL_MapEntryNode* entry
  );

void
Arcadia_DDL_MapNode_inserFront
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_DDL_MapEntryNode* entry
  );

void
Arcadia_DDL_MapNode_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_SizeValue index,
    Arcadia_DDL_MapEntryNode* entry
  );

#endif // ARCADIA_DDL_TREE_MAPNODE_H_INCLUDED
