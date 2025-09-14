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

#include "Arcadia/DataDefinitionLanguage/Writer/Unparser.h"

#include "Arcadia/DataDefinitionLanguage/Include.h"

struct Arcadia_DataDefinitionLanguage_Unparser {
  Arcadia_Object _parent;
};

static void
whitespace
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* target,
    Arcadia_SizeValue count
  )
{
  for (Arcadia_SizeValue i = 0; i < count; ++i) {
    Arcadia_Utf8Writer_writeBytes(thread, target, u8" ", sizeof(u8" ") - 1);
  }
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_writeVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Unparser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Unparser_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Unparser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Unparser", Arcadia_DataDefinitionLanguage_Unparser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Unparser_writeBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_BooleanNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_Utf8Writer_writeString(thread, target, node->value);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_ListNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"[\n", sizeof(u8"[\n") - 1);
  indent += 2;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->elements); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_Node* elementNode = (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_List_getObjectReferenceValueAt(thread, node->elements, i);
    whitespace(thread, target, indent);
    Arcadia_DataDefinitionLanguage_Unparser_writeValue(thread, self, elementNode, indent, target);
    Arcadia_Utf8Writer_writeBytes(thread, target, u8",\n", sizeof(u8",\n") - 1);
  }
  indent -= 2;
  whitespace(thread, target, indent);
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"]", sizeof(u8"]") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"{\n", sizeof(u8"{\n") - 1);
  indent += 2; 
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* entryNode =
      (Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    Arcadia_DataDefinitionLanguage_Tree_NameNode* keyNode = entryNode->key;
    whitespace(thread, target, indent);
    Arcadia_Utf8Writer_writeString(thread, target, keyNode->value);
    Arcadia_Utf8Writer_writeBytes(thread, target, u8" : ", sizeof(u8" : ") - 1);
    Arcadia_DataDefinitionLanguage_Tree_Node* valueNode = entryNode->value;
    Arcadia_DataDefinitionLanguage_Unparser_writeValue(thread, self, valueNode, indent, target);
    Arcadia_Utf8Writer_writeBytes(thread, target, u8",\n", sizeof(u8",\n") - 1);
  }
  indent -= 2;
  whitespace(thread, target, indent);
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"}", sizeof(u8"}") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeNumberValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_Utf8Writer_writeString(thread, target, node->value);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{ 
  Arcadia_String* string = node->value;
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"\"", sizeof(u8"\"") - 1);
  Arcadia_Utf8Reader* reader = (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, string);
  while (Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, reader);
    // Escape all control characters [0,1f].
    if (codePoint <= 0x1f) {
      static const Arcadia_Natural32Value codePoints[] = { '\\', 'u', '0', '0' };
      Arcadia_Utf8Writer_writeCodePoints(thread, target, codePoints, 4);
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
      Arcadia_Utf8Writer_writeCodePoints(thread, target, &hexDigit[y], 1);
      Arcadia_Utf8Writer_writeCodePoints(thread, target, &hexDigit[x], 1);
    } else {
      switch (codePoint) {
        case '"': {
          static const uint32_t codePoints[] = { '\\', '"' };
          Arcadia_Utf8Writer_writeCodePoints(thread, target, codePoints, 2);
        } break;
        case '\\': {
          static const uint32_t codePoints[] = { '\\', '\\' };
          Arcadia_Utf8Writer_writeCodePoints(thread, target, codePoints, 2);
        } break;
        default: {
          Arcadia_Utf8Writer_writeCodePoints(thread, target, &codePoint, 1);
        } break;
      };
    }
    Arcadia_Utf8Reader_next(thread, reader);
  }
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"\"", sizeof(u8"\"") - 1);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  switch (node->type) {
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Boolean: {
      Arcadia_DataDefinitionLanguage_Unparser_writeBooleanValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_BooleanNode*)node, indent, target);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_List: {
      Arcadia_DataDefinitionLanguage_Unparser_writeListValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_ListNode*)node, indent, target);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Map: {
      Arcadia_DataDefinitionLanguage_Unparser_writeMapValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_MapNode*)node, indent, target);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Number: {
      Arcadia_DataDefinitionLanguage_Unparser_writeNumberValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_NumberNode*)node, indent, target);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_String: {
      Arcadia_DataDefinitionLanguage_Unparser_writeStringValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_StringNode*)node, indent, target);
    } break;
    case Arcadia_DataDefinitionLanguage_Tree_NodeType_Void: {
      Arcadia_DataDefinitionLanguage_Unparser_writeVoidValue(thread, self, (Arcadia_DataDefinitionLanguage_Tree_VoidNode*)node, indent, target);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static void
Arcadia_DataDefinitionLanguage_Unparser_writeVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* node,
    Arcadia_SizeValue indent,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_Utf8Writer_writeString(thread, target, node->value);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Unparser* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Unparser_getType(thread);
  //
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_DataDefinitionLanguage_Unparser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self
  )
{/*Intentionally empty.*/}

Arcadia_DataDefinitionLanguage_Unparser*
Arcadia_DataDefinitionLanguage_Unparser_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Unparser);
}

void
Arcadia_DataDefinitionLanguage_Unparser_run
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_Utf8Writer* target
  )
{
  Arcadia_DataDefinitionLanguage_Unparser_writeValue(thread, self, node, Arcadia_SizeValue_Literal(0), target);
  Arcadia_Utf8Writer_writeBytes(thread, target, u8"\n", sizeof(u8"\n") - 1);
}
