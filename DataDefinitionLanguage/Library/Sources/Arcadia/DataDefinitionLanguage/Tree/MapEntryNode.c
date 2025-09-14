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
#include "Arcadia/DataDefinitionLanguage/Tree/MapEntryNode.h"

#include "Arcadia/DataDefinitionLanguage/Tree/Include.h"

static void
Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.MapEntryNode", Arcadia_DataDefinitionLanguage_Tree_MapEntryNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_Tree_NodeType_MapEntry),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->key = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_DataDefinitionLanguage_Tree_NameNode_getType(thread));
  _self->value = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_DataDefinitionLanguage_Tree_Node_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* self
  )
{
  if (self->key) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->key);
  }
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}


Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*
Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NameNode* key,
    Arcadia_DataDefinitionLanguage_Tree_Node* value
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
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_MapEntryNode);
}
