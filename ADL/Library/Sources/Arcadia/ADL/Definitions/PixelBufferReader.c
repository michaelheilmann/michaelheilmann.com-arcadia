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

#define ARCADIA_ADL_PRIVATE (1)
#include "Arcadia/ADL/Definitions/PixelBufferReader.h"

#include "Arcadia/ADL/Context.h"
#include "Arcadia/ADL/Definitions/PixelBufferDefinition.h"
#include "Arcadia/ADL/Reference.h"

static const char* SCHEMA =
"{\n"
"  kind : \"Schema\",\n"
"  name : \"PixelBuffer\",\n"
"  definition : {\n"
"    kind : \"Map\",\n"
"    entries : [\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"type\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"name\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"width\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"height\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"operations\",\n"
"        type : {\n"
"          kind : \"List\",\n"
"          entry : {\n"
"            kind :  \"String\",\n"
"          },\n"
"        },\n"
"      },\n"
"    ],\n"
"  },\n"
"}\n"
;

static Arcadia_String*
Arcadia_ADL_PixelBufferReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  );

static Arcadia_ADL_PixelBufferDefinition*
Arcadia_ADL_PixelBufferReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  );

static Arcadia_Natural32Value
getNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static Arcadia_List*
getListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static void
Arcadia_ADL_PixelBufferReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  );

static void
Arcadia_ADL_PixelBufferReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReaderDispatch* self
  );

static void
Arcadia_ADL_PixelBufferReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) &Arcadia_ADL_PixelBufferReader_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) &Arcadia_ADL_PixelBufferReader_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.PixelBufferReaderr", Arcadia_ADL_PixelBufferReader,
                         u8"Arcadia.ADL.Reader", Arcadia_ADL_Reader,
                         &_typeOperations);

static Arcadia_String*
Arcadia_ADL_PixelBufferReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  )
{ return self->TYPENAME; }

static Arcadia_ADL_PixelBufferDefinition*
Arcadia_ADL_PixelBufferReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  )
{
  Arcadia_DDLS_ValidationContext_run(thread, self->validationContext, self->SCHEMANAME, input);

  Arcadia_String* type = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->TYPE);
  Arcadia_String* name = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->NAME);
  Arcadia_Natural32Value width = getNatural32Value(thread, (Arcadia_DDL_MapNode*)input, self->WIDTH);
  Arcadia_Natural32Value height = getNatural32Value(thread, (Arcadia_DDL_MapNode*)input, self->HEIGHT);

  // Assert the definition has the correct type.
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(self->TYPENAME);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)type, &t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }


  Arcadia_ADL_PixelBufferDefinition* definition = Arcadia_ADL_PixelBufferDefinition_create(thread, definitions, name, width, height);

  // Get the list.
  Arcadia_List* operations = getListValue(thread, (Arcadia_DDL_MapNode*)input, self->OPERATIONS);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)operations); i < n; ++i) {
    Arcadia_DDL_StringNode* operation = (Arcadia_DDL_StringNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, operations, i, _Arcadia_DDL_StringNode_getType(thread));
    Arcadia_ADL_Reference* operationReference = Arcadia_ADL_Reference_create(thread, definitions, operation->value);
    Arcadia_List_insertBackObjectReferenceValue(thread, definition->operations, operationReference);
  }

  return definition;
}

static Arcadia_Natural32Value
getNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
      (
        thread,
        (Arcadia_List*)mapNode->entries,
        i,
        _Arcadia_DDL_MapEntryNode_getType(thread)
      );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_NumberNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_NumberNode* numberNode = (Arcadia_DDL_NumberNode*)valueNode;
      return Arcadia_String_toNatural32(thread, numberNode->value);
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
      (
        thread,
        (Arcadia_List*)mapNode->entries,
        i,
        _Arcadia_DDL_MapEntryNode_getType(thread)
      );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_StringNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_StringNode* stringNode = (Arcadia_DDL_StringNode*)valueNode;
      return stringNode->value;
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static Arcadia_List*
getListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
      (
        thread,
        (Arcadia_List*)mapNode->entries,
        i,
        _Arcadia_DDL_MapEntryNode_getType(thread)
      );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_ListNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_ListNode* listNode = (Arcadia_DDL_ListNode*)valueNode;
      return listNode->elements;
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ADL_PixelBufferReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_PixelBufferReader_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_DDLS_DefaultReader* reader = (Arcadia_DDLS_DefaultReader*)Arcadia_DDLS_DefaultReader_create(thread);
    Arcadia_DDLS_Node* node = Arcadia_DDLS_DefaultReader_run(thread, reader, Arcadia_String_createFromCxxString(thread, SCHEMA));
    if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)node, _Arcadia_DDLS_SchemaNode_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_addSchema(thread, validationContext, (Arcadia_DDLS_SchemaNode*)node);
    self->validationContext = validationContext;
  }
  //
  self->TYPE = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"type");
  self->NAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"name");
  self->SCHEMANAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"PixelBuffer");
  self->TYPENAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"PixelBuffer");
  self->OPERATIONS = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"operations");
  self->WIDTH = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"width");
  self->HEIGHT = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"height");
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_ADL_PixelBufferReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReaderDispatch* self
  )
{
  ((Arcadia_ADL_ReaderDispatch*)self)->getTypeName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*)) & Arcadia_ADL_PixelBufferReader_getTypeName;
  ((Arcadia_ADL_ReaderDispatch*)self)->read = (Arcadia_ADL_Definition * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*, Arcadia_ADL_Context*, Arcadia_ADL_Definitions*, Arcadia_DDL_Node*)) & Arcadia_ADL_PixelBufferReader_read;
}

static void
Arcadia_ADL_PixelBufferReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferReader* self
  )
{
  if (self->validationContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->validationContext);
  }
  //
  if (self->TYPE) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->TYPE);
  }
  if (self->NAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->NAME);
  }
  if (self->SCHEMANAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->SCHEMANAME);
  }
  if (self->TYPENAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->TYPENAME);
  }
  if (self->OPERATIONS) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->OPERATIONS);
  }
  if (self->WIDTH) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->WIDTH);
  }
  if (self->HEIGHT) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->HEIGHT);
  }
}

Arcadia_ADL_PixelBufferReader*
Arcadia_ADL_PixelBufferReader_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_PixelBufferReader);
}
