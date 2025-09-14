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

#define ARCADIA_DATADEFINITIONLANGUAGE_PRIVATE (1)
#include "Arcadia/DataDefinitionLanguage/Tree/MapNode.h"

static void
Arcadia_DataDefinitionLanguage_Tree_MapNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Tree_MapNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_MapNode_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Tree_MapNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_MapNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_MapNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_MapNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.MapNode", Arcadia_DataDefinitionLanguage_Tree_MapNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_MapNode_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Tree_MapNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Tree_MapNode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_MapNode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_Tree_NodeType_Map),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->entries = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_DataDefinitionLanguage_Tree_MapNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* self
  )
{
  if (self->entries) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->entries);
  }
}

Arcadia_DataDefinitionLanguage_Tree_MapNode*
Arcadia_DataDefinitionLanguage_Tree_MapNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_MapNode);
}
