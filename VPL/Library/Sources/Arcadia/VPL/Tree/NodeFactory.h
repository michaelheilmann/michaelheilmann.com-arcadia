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

#if !defined(ARCADIA_VISUALS_VPL_TREE_NODEFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_NODEFACTORY_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Tree/Node.h"
#include "Arcadia/VPL/Tree/ProcedureDefnNode.h"

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeCallExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* target
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeNumberExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeAccessExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeAddExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeSubtractExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeMultiplyExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeDivideExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeNameExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeAssignmentExpr
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_NodeFactory_makeVariableDefn
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type
  );

Arcadia_VPL_Tree_ProcedureDefnNode*
Arcadia_VPL_Tree_NodeFactory_makeProcedureDefn
  (
    Arcadia_Thread* thread,
    Arcadia_List* modifiers,
    Arcadia_VPL_Tree_NameExprNode* returnValueType,
    Arcadia_String* name,
    Arcadia_List* parameters,
    Arcadia_List* body
  );


#endif // ARCADIA_VISUALS_VPL_TREE_NODEFACTORY_H_INCLUDED
