// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_DDL_PRIVATE (1)
#include "Arcadia/DDL/Implementation/MapNode.h"

static void
Arcadia_DDL_MapNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self
  );

static void
Arcadia_DDL_MapNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDL_MapNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDL_MapNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_MapNode_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDL_MapNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDL_MapNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.MapNode", Arcadia_DDL_MapNode,
                         u8"Arcadia.DDL.Node", Arcadia_DDL_Node,
                         &_Arcadia_DDL_MapNode_typeOperations);

static void
Arcadia_DDL_MapNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_MapNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDL_NodeType_Map);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->entries = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_DDL_MapNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self
  )
{
  if (self->entries) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->entries);
  }
}

Arcadia_DDL_MapNode*
Arcadia_DDL_MapNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDL_MapNode);
}

void
Arcadia_DDL_MapNode_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_DDL_MapEntryNode* entry
  )
{ Arcadia_List_insertBackObjectReferenceValue(thread, self->entries, entry); }

void
Arcadia_DDL_MapNode_inserFront
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_DDL_MapEntryNode* entry
  )
{ Arcadia_List_insertFrontObjectReferenceValue(thread, self->entries, entry); }

void
Arcadia_DDL_MapNode_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* self,
    Arcadia_SizeValue index,
    Arcadia_DDL_MapEntryNode* entry
  )
{ Arcadia_List_insertObjectReferenceValueAt(thread, self->entries, index, entry); }
