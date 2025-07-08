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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_TREE_MAPNODE_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_TREE_MAPNODE_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Tree/Node.h"
#include "Arcadia/Ring2/Include.h"

// The map node is  alist of map entry nodes.
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.MapNode", Arcadia_DataDefinitionLanguage_Tree_MapNode,
                          u8"Arcadia.DataDefinitionLanguage.Tree.Node");

struct Arcadia_DataDefinitionLanguage_Tree_MapNode {
  Arcadia_DataDefinitionLanguage_Tree_Node parent;
  Arcadia_List* entries;
};

Arcadia_DataDefinitionLanguage_Tree_MapNode*
Arcadia_DataDefinitionLanguage_Tree_MapNode_create
  (
    Arcadia_Thread* thread
  );

/// @brief Get if this map node has different map entries with the same keys.
/// @param thread Pointer to this thread.
/// @param self Pointer to this map node.
/// @return #Arcadia_BooleanValue_True if there are collision, #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_DataDefinitionLanguage_Tree_MapNode_hasCollisions
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* self
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_TREE_MAPNODE_H_INCLUDED
