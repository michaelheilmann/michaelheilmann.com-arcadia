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

#if !defined(ARCADIA_VPL_TREE_TREEVISITOR_H_INCLUDED)
#define ARCADIA_VPL_TREE_TREEVISITOR_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Tree/Node.h"
#include "Arcadia/VPL/Tree/BinaryExprNode.h"
#include "Arcadia/VPL/Tree/ConstantRecordDefnNode.h"
#include "Arcadia/VPL/Tree/CallExprNode.h"
#include "Arcadia/VPL/Tree/ProcedureDefnNode.h"
#include "Arcadia/VPL/Tree/ProgramDefnNode.h"
#include "Arcadia/VPL/Tree/VariableDefnNode.h"

Arcadia_declareObjectType(u8"Arcadia.VPL.Tree.TreeVisitor", Arcadia_VPL_Tree_NodeVisitor,
                          u8"Arcadia.Object");

struct Arcadia_VPL_Tree_NodeVisitorDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_Value (*onBinaryExprNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_BinaryExprNode* tree);
  Arcadia_Value (*onCallExprNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_CallExprNode* tree);
  Arcadia_Value (*onConstantRecordDefnNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_ConstantRecordDefnNode* tree);
  Arcadia_Value (*onProcedureDefnNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_ProcedureDefnNode* tree);
  Arcadia_Value (*onProgramDefnNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_ProgramDefnNode* tree);
  Arcadia_Value (*onVariableDefnNode)(Arcadia_Thread* thread, Arcadia_VPL_Tree_NodeVisitor* self, Arcadia_Value context, Arcadia_VPL_Tree_VariableDefnNode* tree);
};

struct Arcadia_VPL_Tree_NodeVisitor {
  Arcadia_Object _parent;
};

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onBinaryExprNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_BinaryExprNode* tree
  );

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onCallExprNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_CallExprNode* tree
  );

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onProcedureDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_ProcedureDefnNode* tree
  );

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onProgramDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_ProgramDefnNode* tree
  );

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onVariableDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_VariableDefnNode* tree
  );

#endif // ARCADIA_VPL_TREE_TREEVISITOR_H_INCLUDED
