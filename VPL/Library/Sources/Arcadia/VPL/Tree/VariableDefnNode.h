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

#if !defined(ARCADIA_VISUALS_VPL_TREE_VARIABLEDEFNNODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_VARIABLEDEFNNODE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Tree/Node.h"
#include "Arcadia/VPL/Tree/NameExprNode.h"


// <variable definition> : <name> ':' <type name> <modifiers>
// <modifier>            : <modifier>*
// <modifier>            : 'constant'
//                       / 'variable'
Arcadia_declareObjectType(u8"Arcadia.VPL.Tree.VariableDefnNode", Arcadia_VPL_Tree_VariableDefnNode,
                          u8"Arcadia.VPL.Tree.Node");

struct Arcadia_VPL_Tree_VariableDefnNodeDispatch {
  Arcadia_VPL_Tree_NodeDispatch _parent;
};

struct Arcadia_VPL_Tree_VariableDefnNode {
  Arcadia_VPL_Tree_Node _parent;
  // The name of the variable.
  Arcadia_String* name;
  // List of modifiers of the variable.
  Arcadia_List* modifiers;
  // The type of the variable.
  Arcadia_String* type;
  // The symbol of the type.
  Arcadia_VPL_Symbols_Symbol* typeSymbol;
};

Arcadia_VPL_Tree_VariableDefnNode*
Arcadia_VPL_Tree_VariableDefnNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_VariableDefnNode_isVertex
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_VariableDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_VariableDefnNode_isFragment
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_VariableDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_VariableDefnNode_isPixel
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_VariableDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_VariableDefnNode_isConstant
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_VariableDefnNode* self
  );

Arcadia_BooleanValue
Arcadia_VPL_Tree_VariableDefnNode_isVariable
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_VariableDefnNode* self
  );

#endif // ARCADIA_VISUALS_VPL_TREE_VARIABLEDEFNNODE_H_INCLUDED
