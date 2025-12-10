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
#include "Arcadia/ADL/Context.h"

#include "Arcadia/ADL/Definitions.h"

#include "Arcadia/ADL/Definitions/ColorReader.h"
#include "Arcadia/ADL/Definitions/CheckerboardFillOperationReader.h"
#include "Arcadia/ADL/Definitions/FillOperationReader.h"
#include "Arcadia/ADL/Definitions/PixelBufferReader.h"

static void
Arcadia_ADL_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self
  );

static void
Arcadia_ADL_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ContextDispatch* self
  );

static void
Arcadia_ADL_Context_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self
  );

static Arcadia_ADL_Context*
Arcadia_ADL_Context_create
  (
    Arcadia_Thread* thread
  );

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  );

static Arcadia_ADL_Definition*
readFromString
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* input
  );

static Arcadia_ADL_Definition*
readFromNode
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_MapNode* input
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_Context_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ADL_Context_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.Context", Arcadia_ADL_Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ADL_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_Context_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->readers = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  //
  {
    Arcadia_ADL_Reader* reader = (Arcadia_ADL_Reader*)Arcadia_ADL_PixelBufferOperations_FillOperationReader_create(thread);
    Arcadia_Map_set(thread, self->readers, Arcadia_Value_makeObjectReferenceValue(Arcadia_ADL_Reader_getTypeName(thread, reader)), Arcadia_Value_makeObjectReferenceValue(reader), NULL, NULL);
  }
  {
    Arcadia_ADL_Reader* reader = (Arcadia_ADL_Reader*)Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationReader_create(thread);
    Arcadia_Map_set(thread, self->readers, Arcadia_Value_makeObjectReferenceValue(Arcadia_ADL_Reader_getTypeName(thread, reader)), Arcadia_Value_makeObjectReferenceValue(reader), NULL, NULL);
  }
  {
    Arcadia_ADL_Reader* reader = (Arcadia_ADL_Reader*)Arcadia_ADL_ColorReader_create(thread);
    Arcadia_Map_set(thread, self->readers, Arcadia_Value_makeObjectReferenceValue(Arcadia_ADL_Reader_getTypeName(thread, reader)), Arcadia_Value_makeObjectReferenceValue(reader), NULL, NULL);
  }
  {
    Arcadia_ADL_Reader* reader = (Arcadia_ADL_Reader*)Arcadia_ADL_PixelBufferReader_create(thread);
    Arcadia_Map_set(thread, self->readers, Arcadia_Value_makeObjectReferenceValue(Arcadia_ADL_Reader_getTypeName(thread, reader)), Arcadia_Value_makeObjectReferenceValue(reader), NULL, NULL);
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_ADL_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ContextDispatch* self
  )
{ }

static void
Arcadia_ADL_Context_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self
  )
{
  if (self->readers) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->readers);
  }
}

static Arcadia_ADL_Context*
Arcadia_ADL_Context_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_Context);
}

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  Arcadia_String* value = NULL;
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
        Arcadia_logf(Arcadia_LogFlags_Error, u8"map entry with name `type` has no `string` value\n");
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      if (value) {
        Arcadia_logf(Arcadia_LogFlags_Error, u8"map entry with name `type` already specified\n");
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      value = ((Arcadia_DDL_StringNode*)valueNode)->value;
    }
  }
  if (!value) {
    Arcadia_logf(Arcadia_LogFlags_Error, u8"map entry with name `type` not specified\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  return value;
}

static Arcadia_ADL_Definition*
readFromString
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* input
  )
{
  Arcadia_DDL_DefaultReader* reader = (Arcadia_DDL_DefaultReader*)Arcadia_DDL_DefaultReader_create(thread);
  Arcadia_DDL_Node* node = Arcadia_DDL_DefaultReader_run(thread, reader, input);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)node, _Arcadia_DDL_MapNode_getType(thread))) {
    Arcadia_logf(Arcadia_LogFlags_Error, u8"argument input is not a of type Arcadia.DDL.MapNode\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  return readFromNode(thread, self, definitions, (Arcadia_DDL_MapNode*)node);
}


static Arcadia_ADL_Definition*
readFromNode
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_MapNode* input
  )
{
  // (1) Retrieve reader.
  Arcadia_String* entryName = Arcadia_String_createFromCxxString(thread, "type");
  Arcadia_String* entryValue = getStringValue(thread, self, input, entryName);
  Arcadia_Value readerValue = Arcadia_Map_get(thread, self->readers, Arcadia_Value_makeObjectReferenceValue(entryValue));
  if (Arcadia_Value_isVoidValue(&readerValue)) {
    Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, "no reader registered for type `")));
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(entryValue));
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, "`")));
    Arcadia_Languages_Diagnostics_emit(thread, stringBuffer);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ADL_Reader* reader = (Arcadia_ADL_Reader*)Arcadia_Value_getObjectReferenceValue(&readerValue);
  // (2) Read the definition.
  Arcadia_ADL_Definition* definition = Arcadia_ADL_Reader_read(thread, reader, self, definitions, (Arcadia_DDL_Node*)input);
  // (3) Assert there is no definition of the same name in the definitions already.
  Arcadia_Value temporary = Arcadia_Map_get(thread, definitions->definitions, Arcadia_Value_makeObjectReferenceValue(definition->name));
  if (!Arcadia_Value_isVoidValue(&temporary)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Exists);
    Arcadia_Thread_jump(thread);
  }
  // (4) Register the definition.
  Arcadia_Map_set(thread, definitions->definitions, Arcadia_Value_makeObjectReferenceValue(definition->name), Arcadia_Value_makeObjectReferenceValue(definition), NULL, NULL);
  // (5) Return the definition.
  return definition;
}

static Arcadia_ADL_Context* g_instance = NULL;

static void
Arcadia_ADL_Context_destroyCallback
  (
    void* observer,
    void* observed
  )
{ g_instance = NULL; }

Arcadia_ADL_Context*
Arcadia_ADL_Context_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_ADL_Context* instance = Arcadia_ADL_Context_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &Arcadia_ADL_Context_destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}

Arcadia_ADL_Definition*
Arcadia_ADL_Context_readFromNode
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  )
{
  if (!input) {
    Arcadia_logf(Arcadia_LogFlags_Error, u8"argument input is a null pointer\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)input, _Arcadia_DDL_MapNode_getType(thread))) {
    Arcadia_logf(Arcadia_LogFlags_Error, u8"argument input is not a of type Arcadia.DDL.MapNode\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  return readFromNode(thread, self, definitions, (Arcadia_DDL_MapNode*)input);
}

Arcadia_ADL_Definition*
Arcadia_ADL_Context_readFromString
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* input
  )
{
  if (!input) {
    Arcadia_logf(Arcadia_LogFlags_Error, u8"argument input is a null pointer\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return readFromString(thread, self, definitions, input);
}
