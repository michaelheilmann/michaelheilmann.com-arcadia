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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/VPL/Tree/BinaryExprNode.h"

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNode* self
  );

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNodeDispatch* self
  );

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_VPL_Tree_BinaryExprNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_VPL_Tree_BinaryExprNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.VPL.Tree.BinaryExprNode", Arcadia_Visuals_VPL_Tree_BinaryExprNode,
                         u8"Arcadia.Engine.Visuals.VPL.Tree.Node", Arcadia_Visuals_VPL_Tree_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Tree_BinaryExprNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_Visuals_VPL_Tree_NodeFlags_BinaryExpr);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->kind = Arcadia_ValueStack_getInteger32Value(thread, 3);
  self->lhs = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_VPL_Tree_Node_getType(thread));
  self->rhs = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_VPL_Tree_Node_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 3+ 1);
}

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_VPL_Tree_BinaryExprNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_BinaryExprNode* self
  )
{
  if (self->lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->lhs);
  }
  if (self->rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->rhs);
  }
}

Arcadia_Visuals_VPL_Tree_BinaryExprNode*
Arcadia_Visuals_VPL_Tree_BinaryExprNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value kind,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, kind);
  if (lhs) Arcadia_ValueStack_pushObjectReferenceValue(thread, lhs); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (rhs) Arcadia_ValueStack_pushObjectReferenceValue(thread, rhs); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Tree_BinaryExprNode);
}
