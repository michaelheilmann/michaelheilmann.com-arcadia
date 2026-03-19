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

#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/Tree/NodeVisitor.h"

static void
Arcadia_VPL_Tree_NodeVisitor_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self
  );

static void
Arcadia_VPL_Tree_NodeVisitor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitorDispatch* self
  );

static void
Arcadia_VPL_Tree_NodeVisitor_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Tree_NodeVisitor_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Tree_NodeVisitor_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.VPL.Tree.TreeVisitor", Arcadia_VPL_Tree_NodeVisitor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_Tree_NodeVisitor_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Tree_NodeVisitor);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_VPL_Tree_NodeVisitor);
}

static void
Arcadia_VPL_Tree_NodeVisitor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitorDispatch* self
  )
{ }

static void
Arcadia_VPL_Tree_NodeVisitor_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self
  )
{/*Intentionally empty.*/}

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onBinaryExprNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_BinaryExprNode* tree
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_VPL_Tree_NodeVisitor, onBinaryExprNode, self, context, tree); }

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onCallExprNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_CallExprNode* tree
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_VPL_Tree_NodeVisitor, onCallExprNode, self, context, tree); }

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onProcedureDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_ProcedureDefnNode* tree
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_VPL_Tree_NodeVisitor, onProcedureDefnNode, self, context, tree); }

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onProgramDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_ProgramDefnNode* tree
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_VPL_Tree_NodeVisitor, onProgramDefnNode, self, context, tree); }

Arcadia_Value
Arcadia_VPL_Tree_NodeVisitor_onVariableDefnNode
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeVisitor* self,
    Arcadia_Value context,
    Arcadia_VPL_Tree_VariableDefnNode* tree
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_VPL_Tree_NodeVisitor, onVariableDefnNode, self, context, tree); }
