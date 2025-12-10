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

#define ARCADIA_DDL_NODES_PRIVATE (1)
#include "Arcadia/DDL/Nodes/ListNode.h"

static void
Arcadia_DDL_ListNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  );

static void
Arcadia_DDL_ListNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNodeDispatch* self
  );

static void
Arcadia_DDL_ListNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDL_ListNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDL_ListNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_ListNode_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDL_ListNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDL_ListNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.ListNode", Arcadia_DDL_ListNode,
                         u8"Arcadia.DDL.Node", Arcadia_DDL_Node,
                         &_Arcadia_DDL_ListNode_typeOperations);

static void
Arcadia_DDL_ListNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_ListNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDL_NodeType_List);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->elements = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_DDL_ListNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNodeDispatch* self
  )
{ }

static void
Arcadia_DDL_ListNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  )
{
  if (self->elements) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->elements);
  }
}

Arcadia_DDL_ListNode*
Arcadia_DDL_ListNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDL_ListNode);
}

Arcadia_SizeValue
Arcadia_DDL_ListNode_getNumberOfElements
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_ListNode* self
  )
{ return Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->elements); }
