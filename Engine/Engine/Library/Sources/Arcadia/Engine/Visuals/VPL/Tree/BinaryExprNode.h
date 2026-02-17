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

#if !defined(ARCADIA_VISUALS_VPL_TREE_BINARYEXPRNODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_BINARYEXPRNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/VPL/Tree/Node.h"

// <expression> '.' <expression>
#define Arcadia_Visuals_VPL_Tree_BinaryExprNodeFlags_Access (0)

// <expression> '+' <expression>
#define Arcadia_Visuals_VPL_Tree_BinaryExprNodeFlags_Add (1)

// <expression> '-' <expression>
#define Arcadia_Visuals_VPL_Tree_BinaryExprNodeFlags_Subtract (2)

// <expression> '*' <expression>
#define Arcadia_Visuals_VPL_Tree_BinaryExprNodeFlags_Multiply (3)

// <expression> '/' <expression>
#define Arcadia_Visuals_VPL_Tree_BinaryExprNodeFlags_Divide (4)

/// For Arcadia_Visuals_VPL_Tree_NodeFlags_(Add|Subtract|Multiply|Divide|Access).
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.VPL.Tree.BinaryExprNode", Arcadia_Visuals_VPL_Tree_BinaryExprNode,
                          u8"Arcadia.Engine.Visuals.VPL.TreeNode");

struct Arcadia_Visuals_VPL_Tree_BinaryExprNodeDispatch {
  Arcadia_Visuals_VPL_Tree_NodeDispatch _parent;
};

struct Arcadia_Visuals_VPL_Tree_BinaryExprNode {
  Arcadia_Visuals_VPL_Tree_Node _parent;
  Arcadia_Integer32Value kind;
  Arcadia_Visuals_VPL_Tree_Node* lhs, * rhs;
};

Arcadia_Visuals_VPL_Tree_BinaryExprNode*
Arcadia_Visuals_VPL_Tree_BinaryExprNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value kind,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

#endif // ARCADIA_VISUALS_VPL_TREE_BINARYEXPRNODE_H_INCLUDED
