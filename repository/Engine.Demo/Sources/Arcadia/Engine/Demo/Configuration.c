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

#include "Arcadia/Engine/Demo/Configuration.h"

#include <string.h>

static Arcadia_BooleanValue
_isNumber
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  )
{ return Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread)); }

static Arcadia_BooleanValue
_isMapEntry
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  )
{ return Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_getType(thread)); }

static Arcadia_BooleanValue
_isMap
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node
  )
{ return Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DataDefinitionLanguage_Tree_MapNode_getType(thread)); }

static Arcadia_SizeValue
_findIndex
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* self,
    Arcadia_SizeValue index,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = index, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* entry = Arcadia_List_getObjectReferenceValueAt(thread, self->entries, i);
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(entry->key->value);
    Arcadia_Value b = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      return i;
    }
  }
  return Arcadia_SizeValue_Maximum;
}

static void
_createInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    char const* name,
    Arcadia_Integer32Value value
  )
{
  Arcadia_String* nameString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, name, strlen(name))));
  Arcadia_SizeValue i = _findIndex(thread, node, 0, nameString);
  Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e = NULL;
  if (i != Arcadia_SizeValue_Maximum) {
    Arcadia_List_removeAt(thread, node->entries, i, 1);
  }
  Arcadia_DataDefinitionLanguage_Tree_NameNode* k = Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, nameString);
  Arcadia_DataDefinitionLanguage_Tree_Node* v = (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger32(thread, value);
  e = Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create(thread, k, v);
  Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, (Arcadia_ObjectReferenceValue)e);
}

/// - if x[name] is a map node, then return x[name]
/// - if x[name] is not a map node or x[name] does not exit, x[name] = {} and return x[name]
static Arcadia_DataDefinitionLanguage_Tree_MapNode*
_getOrCreateMap
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    char const* name
  )
{
  Arcadia_String* nameString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, name, strlen(name))));
  Arcadia_SizeValue i = _findIndex(thread, node, 0, nameString);
  Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e = NULL;
  if (i != Arcadia_SizeValue_Maximum) {
    e = (Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (!_isMap(thread, e->value)) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      e = NULL;
    }
  }
  if (!e) {
    Arcadia_DataDefinitionLanguage_Tree_NameNode* k = Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, nameString);
    Arcadia_DataDefinitionLanguage_Tree_Node* v = (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_MapNode_create(thread);
    e = Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create(thread, k, v);
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, (Arcadia_ObjectReferenceValue)e);
  }
  return (Arcadia_DataDefinitionLanguage_Tree_MapNode*)e->value;
}


// node must be a map node
void
Cfg2_setInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames,
    Arcadia_Integer32Value value
  )
{
  if (!_isMap(thread, node)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Tree_MapNode* current = (Arcadia_DataDefinitionLanguage_Tree_MapNode*)node;
  for (Arcadia_SizeValue i = 0, n = numberOfNames - 1; i < n; ++i) {
    current = _getOrCreateMap(thread, current, names[i]);
  }
  if (!current) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_jump(thread);
  }
  _createInteger32(thread, current, names[numberOfNames - 1], value);
}

// not exists or conversion failed
Arcadia_Integer32Value
Cfg2_getInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  )
{
  Arcadia_DataDefinitionLanguage_Tree_Node* current = node;
  for (Arcadia_SizeValue i = 0, n = numberOfNames; i < n; ++i) {
    if (!_isMap(thread, current)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* nameString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, names[i], strlen(names[i]))));
    Arcadia_SizeValue i = _findIndex(thread, (Arcadia_DataDefinitionLanguage_Tree_MapNode*)current, 0, nameString);
    if (i == Arcadia_SizeValue_Maximum) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
      Arcadia_Thread_jump(thread);
    }
    current = Arcadia_List_getObjectReferenceValueAt(thread, ((Arcadia_DataDefinitionLanguage_Tree_MapNode*)current)->entries, i);
    if (!_isMapEntry(thread, current)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
      Arcadia_Thread_jump(thread);
    }
    current = ((Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)current)->value;
  }
  if (!current) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_jump(thread);
  }
  if (!_isNumber(thread, current)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_String_toInteger32(thread, ((Arcadia_DataDefinitionLanguage_Tree_NumberNode*)(current))->value);
}

void
Cfg2_setSection
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  )
{
  if (!_isMap(thread, node)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Tree_MapNode* current = (Arcadia_DataDefinitionLanguage_Tree_MapNode*)node;
  for (Arcadia_SizeValue i = 0, n = numberOfNames; i < n; ++i) {
    current = _getOrCreateMap(thread, current, names[i]);
  }
}
