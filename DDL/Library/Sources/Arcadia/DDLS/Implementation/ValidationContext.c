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

#include "Arcadia/DDLS/Implementation/ValidationContext.h"

static void
Arcadia_DDLS_ValidationContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self
  );

static void
Arcadia_DDLS_ValidationContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self
  );

static void
Arcadia_DDLS_ValidationContext_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_ValidationContext_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDLS_ValidationContext_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_ValidationContext_visitImpl,
};                                                                                  

static const Arcadia_Type_Operations _Arcadia_DDLS_ValidationContext_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_ValidationContext_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.ValidationContext", Arcadia_DDLS_ValidationContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_DDLS_ValidationContext_typeOperations);

static void
Arcadia_DDLS_ValidationContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_ValidationContext_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->temporary1 = Arcadia_StringBuffer_create(thread);
  self->stringTable = Arcadia_Languages_StringTable_create(thread);
  self->diagnostics = Arcadia_DDLS_Diagnostics_create(thread, self->stringTable);
  //
  self->run = &Arcadia_DDLS_ValidationContext_runImpl;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DDLS_ValidationContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self
  )
{
  if (self->temporary1) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporary1);
  }
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics);
  }
  if (self->stringTable) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->stringTable);
  }
}

#include "Arcadia/DDLS/Extensions.h"

#if 0
static Arcadia_String*
expectedToString
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type
  )
{
  if (Arcadia_DDLS_isBoolean(thread, type)) {
    return self->diagnostics->BOOLEAN;
  } else if (Arcadia_DDLS_isList(thread, type)) {
    return self->diagnostics->LIST;
  } else if (Arcadia_DDLS_isMap(thread, type)) {
    return self->diagnostics->MAP;
  } else if (Arcadia_DDLS_isNumber(thread, type)) {
    return self->diagnostics->NUMBER;
  } else if (Arcadia_DDLS_isString(thread, type)) {
    return self->diagnostics->STRING;
  } else if (Arcadia_DDLS_isVoid(thread, type)) {
    return self->diagnostics->VOID;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}
#endif

#if 0
static Arcadia_String*
receivedToString
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDL_Node* node
  )
{
  if (Arcadia_DDL_Node_isBoolean(thread, node)) {
    return self->diagnostics->BOOLEAN;
  } else if (Arcadia_DDL_Node_isList(thread, node)) {
    return self->diagnostics->LIST;
  } else if (Arcadia_DDL_Node_isMap(thread, node)) {
    return self->diagnostics->MAP;
  } else if (Arcadia_DDL_Node_isNumber(thread, node)) {
    return self->diagnostics->NUMBER;
  } else if (Arcadia_DDL_Node_isString(thread, node)) {
    return self->diagnostics->STRING;
  } else if (Arcadia_DDL_Node_isVoid(thread, node)) {
    return self->diagnostics->VOID;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}
#endif

static void
onValidateList
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  );

static void
onValidateMap
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  );

static void
onValidate
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  );

static void
onValidateList
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  )
{
  Arcadia_DDLS_ListType* listType = (Arcadia_DDLS_ListType*)type;
  Arcadia_DDLS_Type* elementType = listType->element;
  Arcadia_DDL_ListNode* listNode = (Arcadia_DDL_ListNode*)node;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)listNode->elements); i < n; ++i) {
    Arcadia_DDL_Node* node = (Arcadia_DDL_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, listNode->elements, i, _Arcadia_DDL_Node_getType(thread));
    onValidate(thread, self, elementType, node);
  }
}

static void
onValidateMap
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  )
{
  /// @todo The implementation shall be non-recursive (same for onValidateList) for example using a stack on which
  ///       validation tasks (a new object type) are pushed.
  Arcadia_Map* symbols = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_DDL_MapNode* mapNode = (Arcadia_DDL_MapNode*)node;
  Arcadia_DDLS_MapType* mapType = (Arcadia_DDLS_MapType*)type;
  // (1) Ensure all map entry names are unique.
  // (2) Ensure all map entry names are permitted by the type.
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* node = (Arcadia_DDL_MapEntryNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, mapNode->entries, i, _Arcadia_DDL_MapEntryNode_getType(thread));
    Arcadia_Value newValue = Arcadia_Value_makeObjectReferenceValue(node->value);
    Arcadia_Value newKey = Arcadia_Value_makeObjectReferenceValue(node->key->value);
    Arcadia_Value oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void), oldKey = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
    Arcadia_Map_set(thread, symbols, newKey, newValue, &oldKey, &oldValue);
    if (!Arcadia_Value_isVoidValue(&oldKey)) {
      Arcadia_DDLS_Diagnostics_mapEntryAlreadyDefined(thread, self->diagnostics, (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&newKey));
      Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value temporary = Arcadia_Map_get(thread, mapType->entries, newKey);
    if (!Arcadia_Value_isObjectReferenceValue(&temporary)) {
      Arcadia_DDLS_Diagnostics_mapEntryNotInTypeError(thread, self->diagnostics, (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&newKey));
      Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
      Arcadia_Thread_jump(thread);

    }
    onValidate(thread, self, (Arcadia_DDLS_Type*)Arcadia_Value_getObjectReferenceValueChecked(thread, temporary, _Arcadia_DDLS_Type_getType(thread)), node->value);
  }
}

static void
onValidate
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  )
{
  if (Arcadia_DDLS_isBoolean(thread, type) && Arcadia_DDL_Node_isBoolean(thread, node)) {
    return;
  } else if (Arcadia_DDLS_isList(thread, type) && Arcadia_DDL_Node_isList(thread, node)) {
    onValidateList(thread, self, type, node);
  } else if (Arcadia_DDLS_isMap(thread, type) && Arcadia_DDL_Node_isMap(thread, node)) {
    onValidateMap(thread, self, type, node);
  } else if (Arcadia_DDLS_isNumber(thread, type) && Arcadia_DDL_Node_isNumber(thread, node)) {
    return;
  } else if (Arcadia_DDLS_isString(thread, type) && Arcadia_DDL_Node_isString(thread, node)) {
    return;
  } else if (Arcadia_DDLS_isVoid(thread, type) && Arcadia_DDL_Node_isVoid(thread, node)) {
    return;
  } else {
    Arcadia_DDLS_Diagnostics_unexpectedTypeError(thread, self->diagnostics, type, node);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_DDLS_ValidationContext_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  )
{
  onValidate(thread, self, type, node);
}

Arcadia_DDLS_ValidationContext*
Arcadia_DDLS_ValidationContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_ValidationContext);
}

void
Arcadia_DDLS_ValidationContext_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  )
{
  self->run(thread, self, type, node);
}
