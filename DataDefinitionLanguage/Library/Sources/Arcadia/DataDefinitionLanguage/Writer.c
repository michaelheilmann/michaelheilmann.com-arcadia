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

#include "Arcadia/DataDefinitionLanguage/Writer.h"

#include "Arcadia/DataDefinitionLanguage/Include.h"

struct Arcadia_DataDefinitionLanguage_Writer {
  Arcadia_Object _parent;
};

static void
writeImmutableUtf8String(Arcadia_Thread* thread, Arcadia_StringBuffer* stringBuffer, Arcadia_ImmutableUtf8String* string) {
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(string));
}

static void
whitespace(Arcadia_Thread* thread, Arcadia_StringBuffer* stringBuffer, Arcadia_SizeValue count) {
  for (Arcadia_SizeValue i = 0; i < count; ++i) {
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8" ", sizeof(u8" ") - 1);
  }
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_writeVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  );

static void
Arcadia_DataDefinitionLanguage_Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Writer_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Writer_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Writer_visit,
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

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Writer", Arcadia_DataDefinitionLanguage_Writer,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Writer_writeBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(node->value));
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8",\n", sizeof(u8",\n") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"[\n", sizeof(u8"[\n") - 1);
  indent += 2;
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, node->elements); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_Node* elementNode = (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_List_getObjectReferenceValueAt(thread, node->elements, i);
    whitespace(thread, stringBuffer, indent);
    Arcadia_DataDefinitionLanguage_Writer_writeValue(thread, self, elementNode, indent, stringBuffer);
  }
  indent -= 2;
  whitespace(thread, stringBuffer, indent);
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"]\n", sizeof(u8"]\n") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"{\n", sizeof(u8"{\n") - 1);
  indent += 2; 
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, node->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* entryNode =
      (Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    Arcadia_DataDefinitionLanguage_Tree_NameNode* keyNode = entryNode->key;
    whitespace(thread, stringBuffer, indent);
    writeImmutableUtf8String(thread, stringBuffer, keyNode->value);
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8" : ", sizeof(u8" : ") - 1);
    Arcadia_DataDefinitionLanguage_Tree_Node* valueNode = entryNode->value;
    Arcadia_DataDefinitionLanguage_Writer_writeValue(thread, self, valueNode, indent, stringBuffer);
  }
  indent -= 2;
  whitespace(thread, stringBuffer, indent);
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"}\n", sizeof(u8"}\n") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(node->value));
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8",\n", sizeof(u8",\n") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{ 
  Arcadia_String* string = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(node->value));
  Arcadia_Utf8Reader* reader = (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, string);
  while (Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, reader);
    // Escape all control characters [0,1f].
    if (codePoint <= 0x1f) {
      static const Arcadia_Natural32Value codePoints[] = { '\\', 'u', '0', '0' };
      Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, codePoints, 4);
      Arcadia_Natural32Value x = codePoint % 16;
      codePoint /= 16;
      Arcadia_Natural32Value y = codePoint % 16;
      codePoint /= 16;
      static const Arcadia_Natural32Value hexDigit[] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',  
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F'
      };
      Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, &hexDigit[y], 1);
      Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, &hexDigit[x], 1);
    } else {
      switch (codePoint) {
        case '"': {
          static const uint32_t codePoints[] = { '\\', '"' };
          Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, codePoints, 2);
        } break;
        case '\\': {
          static const uint32_t codePoints[] = { '\\', '\\' };
          Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, codePoints, 2);
        } break;
        default: {
          Arcadia_StringBuffer_insertCodePointsBack(thread, stringBuffer, &codePoint, 1);
        } break;
      };
    }
    Arcadia_Utf8Reader_next(thread, reader);
  }
}

static void
Arcadia_DataDefinitionLanguage_Writer_writeValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{ }

static void
Arcadia_DataDefinitionLanguage_Writer_writeVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node,
    Arcadia_SizeValue indent,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(node->value));
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8",\n", sizeof(u8",\n") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Writer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Writer_getType(thread);
  //
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  //
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Writer_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self
  )
{/*Intentionally empty.*/}

Arcadia_DataDefinitionLanguage_Writer*
Arcadia_DataDefinitionLanguage_Writer_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_DataDefinitionLanguage_Writer* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Writer_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_DataDefinitionLanguage_Writer_write
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_DataDefinitionLanguage_Writer_writeValue(thread, self, node, Arcadia_SizeValue_Literal(0), stringBuffer);
}
