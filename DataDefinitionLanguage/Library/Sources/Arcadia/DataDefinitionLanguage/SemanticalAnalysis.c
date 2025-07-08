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

#include "Arcadia/DataDefinitionLanguage/SemanticalAnalysis.h"

#include "Arcadia/DataDefinitionLanguage/Include.h"

struct Arcadia_DataDefinitionLanguage_SemanticalAnalysis {
  Arcadia_Object _parent;
  Arcadia_Map* map;
};

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_SemanticalAnalysis_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.SemanticalAnalysis", Arcadia_DataDefinitionLanguage_SemanticalAnalysis,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node
  )
{/*Intentionally empty.*/}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, node->elements); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_Node* elementNode = Arcadia_List_getObjectReferenceValueAt(thread, node->elements, i);
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitValue(thread, self, elementNode);
  }
}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_Map_clear(thread, self->map);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, node->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* mapEntryNode = (Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    Arcadia_Value existing = Arcadia_Map_get(thread, self->map, Arcadia_Value_makeImmutableUtf8StringValue(mapEntryNode->key->value));
    if (!Arcadia_Value_isVoidValue(&existing)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Map_set(thread, self->map, Arcadia_Value_makeImmutableUtf8StringValue(mapEntryNode->key->value), Arcadia_Value_makeObjectReferenceValue(mapEntryNode->value));
  }
  Arcadia_Map_clear(thread, self->map);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, node->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* mapEntryNode = (Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitValue(thread, self, mapEntryNode->value);
  }
}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node
  )
{/*Intentionally empty.*/}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node
  )
{/*Intentionally empty.*/}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  )
{
  switch (node->type) {
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Boolean: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitBooleanValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_BooleanNode*)node);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_List: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitListValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_ListNode*)node);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Map: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitMapValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_MapNode*)node);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Number: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitNumberValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_NumberNode*)node);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_String: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitStringValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_StringNode*)node);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Void: {
      Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitVoidValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_VoidNode*)node);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node
  )
{/*Intentionally empty.*/}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_SemanticalAnalysis_getType(thread);
  //
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  //
  _self->map = Arcadia_Map_create(thread);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self
  )
{
  if (self->map) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->map);
  }
}

Arcadia_DataDefinitionLanguage_SemanticalAnalysis*
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_SemanticalAnalysis_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  )
{
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis_visitValue(thread, self, node);
}
