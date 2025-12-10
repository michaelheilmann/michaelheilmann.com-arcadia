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
#include "Arcadia/DDL/Nodes/MapEntryNode.h"

#include "Arcadia/DDL/Nodes/Include.h"

static void
Arcadia_DDL_MapEntryNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNode* self
  );

static void
Arcadia_DDL_MapEntryNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNodeDispatch* self
  );

static void
Arcadia_DDL_MapEntryNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDL_MapEntryNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDL_MapEntryNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_MapEntryNode_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDL_MapEntryNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDL_MapEntryNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.MapEntryNode", Arcadia_DDL_MapEntryNode,
                         u8"Arcadia.DDL.Node", Arcadia_DDL_Node,
                         &_Arcadia_DDL_MapEntryNode_typeOperations);

static void
Arcadia_DDL_MapEntryNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_MapEntryNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDL_NodeType_MapEntry);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->key = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_DDL_NameNode_getType(thread));
  self->value = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_DDL_Node_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_DDL_MapEntryNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNodeDispatch* self
  )
{ }

static void
Arcadia_DDL_MapEntryNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapEntryNode* self
  )
{
  if (self->key) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->key);
  }
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}


Arcadia_DDL_MapEntryNode*
Arcadia_DDL_MapEntryNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* key,
    Arcadia_DDL_Node* value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (key) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, key);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (value) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, value);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_DDL_MapEntryNode);
}
