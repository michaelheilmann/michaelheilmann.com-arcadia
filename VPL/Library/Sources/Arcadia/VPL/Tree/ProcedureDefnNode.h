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

#if !defined(ARCADIA_VISUALS_VPL_TREE_PROCEDUREDEFNNODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_PROCEDUREDEFNNODE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Tree/Node.h"
typedef struct Arcadia_VPL_Tree_NameExprNode Arcadia_VPL_Tree_NameExprNode;

// <procedure defn> : <modifiers> 'procedure' <name> '(' ´<parameters> ')' ':' <return value type> <body>?
// <modifiers> : <modifier>*
// <modifier> : 'builtin' / 'fragment' / 'pixel' / 'vertex'
Arcadia_declareObjectType(u8"Arcadia.VPL.Tree.ProcedureDefnNode", Arcadia_VPL_Tree_ProcedureDefnNode,
                          u8"Arcadia.VPL.Tree.Node");

struct Arcadia_VPL_Tree_ProcedureDefnNodeDispatch {
  Arcadia_VPL_Tree_NodeDispatch _parent;
};

struct Arcadia_VPL_Tree_ProcedureDefnNode {
  Arcadia_VPL_Tree_Node _parent;
  Arcadia_List* modifiers;
  Arcadia_VPL_Tree_NameExprNode* returnValueType;
  Arcadia_String* name;
  Arcadia_List* parameters;
  Arcadia_List* body;
};

Arcadia_VPL_Tree_ProcedureDefnNode*
Arcadia_VPL_Tree_ProcedureDefnNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_List* modifiers,
    Arcadia_VPL_Tree_NameExprNode* returnValueType,
    Arcadia_String* name,
    Arcadia_List* parameters,
    Arcadia_List* body
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isVertex
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isFragment
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isPixel
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  );

#endif // ARCADIA_VISUALS_VPL_TREE_PROCEDUREDEFNNODE_H_INCLUDED
