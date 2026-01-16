#if !defined(ARCADIA_VISUALS_VPL_TREE_BINARYEXPRNODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_BINARYEXPRNODE_H_INCLUDED

#include "Arcadia/Visuals/VPL/Tree/Node.h"

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
Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Tree.BinaryExprNode", Arcadia_Visuals_VPL_Tree_BinaryExprNode,
                          u8"Arcadia.Visuals.VPL.TreeNode");

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
