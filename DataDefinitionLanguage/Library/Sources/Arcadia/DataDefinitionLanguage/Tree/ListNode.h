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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_TREE_LISTNODE_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_TREE_LISTNODE_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Tree/Node.h"
#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.ListNode", Arcadia_DataDefinitionLanguage_Tree_ListNode, u8"Arcadia.DataDefinitionLanguage.Tree.Node");

struct Arcadia_DataDefinitionLanguage_Tree_ListNode {
  Arcadia_DataDefinitionLanguage_Tree_Node parent;
  Arcadia_List* elements;
};

Arcadia_DataDefinitionLanguage_Tree_ListNode*
Arcadia_DataDefinitionLanguage_Tree_ListNode_create
  (
    Arcadia_Thread* thread
  );

Arcadia_SizeValue
Arcadia_DataDefinitionLanguage_Tree_ListNode_getNumberOfElements
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* self
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_TREE_LISTNODE_H_INCLUDED
