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
#include "Arcadia/ADL/Definitions/CheckerboardFillOperationReader.h"

#include "Arcadia/DDLS/Include.h"
#include "Arcadia/ADL/Definitions/CheckerboardFillOperationDefinition.h"

static const char* SCHEMA =
"{\n"
"  kind : \"Schema\",\n"
"  name : \"PixelBufferOperations.CheckerboardFillOperation\",\n"
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
"        name : \"firstCheckerColor\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"secondCheckerColor\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"checkerWidth\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"checkerHeight\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"    ],\n"
"  },\n"
"}\n"
;

static Arcadia_String*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
  );

static Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  );

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static Arcadia_Integer32Value
getInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReaderDispatch* self
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.PixelBufferOperations.CheckerboardFillOperationReader", Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader,
                         u8"Arcadia.ADL.Reader", Arcadia_ADL_Reader,
                         &_typeOperations);

static Arcadia_String*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
  )
{ return self->TYPENAME; }

static Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  )
{
  Arcadia_DDLS_ValidationContext_run(thread, self->validationContext, self->SCHEMANAME, input);

  Arcadia_String* type = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->TYPE);
  Arcadia_String* name = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->NAME);
  Arcadia_Integer32Value checkerWidth = getInteger32Value(thread, (Arcadia_DDL_MapNode*)input, self->CHECKERWIDTH);
  Arcadia_Integer32Value checkerHeight = getInteger32Value(thread, (Arcadia_DDL_MapNode*)input, self->CHECKERHEIGHT);
  Arcadia_String* firstCheckerColor = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->FIRSTCHECKERCOLOR);
  Arcadia_String* secondCheckerColor = getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->SECONDCHECKERCOLOR);

  // Assert the definition has the correct type.
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(self->TYPENAME);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)type, &t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* definition =
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_create
      (
        thread,
        definitions,
        name,
        checkerWidth,
        checkerHeight,
        firstCheckerColor,
        secondCheckerColor
      );
  return definition;
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

static Arcadia_Integer32Value
getInteger32Value
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
      return Arcadia_String_toInteger32(thread, numberNode->value);
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_getType(thread);
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
  self->SCHEMANAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"PixelBufferOperations.CheckerboardFillOperation");
  self->TYPENAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"PixelBufferOperations.CheckerboardFillOperation");
  //
  self->FIRSTCHECKERCOLOR = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"firstCheckerColor");
  self->SECONDCHECKERCOLOR = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"secondCheckerColor");
  self->CHECKERWIDTH = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"checkerWidth");
  self->CHECKERHEIGHT = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"checkerHeight");
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReaderDispatch* self
  )
{
  ((Arcadia_ADL_ReaderDispatch*)self)->getTypeName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*)) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_getTypeName;
  ((Arcadia_ADL_ReaderDispatch*)self)->read = (Arcadia_ADL_Definition * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*, Arcadia_ADL_Context*, Arcadia_ADL_Definitions*, Arcadia_DDL_Node*)) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_read;
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader* self
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
  //
  if (self->FIRSTCHECKERCOLOR) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->FIRSTCHECKERCOLOR);
  }
  if (self->SECONDCHECKERCOLOR) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->SECONDCHECKERCOLOR);
  }
  if (self->CHECKERWIDTH) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->CHECKERWIDTH);
  }
  if (self->CHECKERHEIGHT) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->CHECKERHEIGHT);
  }
}

Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader);
}
