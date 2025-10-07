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

#include "Arcadia/DataDefinitionLanguage/Reader/Parser.h"

#include "Arcadia/DataDefinitionLanguage/Include.h"

#include "Arcadia/DataDefinitionLanguage/Tree/Include.h"

static void
Arcadia_DataDefinitionLanguage_Parser_next
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static Arcadia_DataDefinitionLanguage_Tree_ListNode*
Arcadia_DataDefinitionLanguage_Parser_onListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*
Arcadia_DataDefinitionLanguage_Parser_onMapEntry
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static Arcadia_DataDefinitionLanguage_Tree_MapNode*
Arcadia_DataDefinitionLanguage_Parser_onMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static Arcadia_DataDefinitionLanguage_Tree_NameNode*
Arcadia_DataDefinitionLanguage_Parser_onName
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static Arcadia_DataDefinitionLanguage_Tree_Node*
Arcadia_DataDefinitionLanguage_Parser_onValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

struct Arcadia_DataDefinitionLanguage_Parser {
  Arcadia_Object _parent;
  Arcadia_DataDefinitionLanguage_Scanner* scanner;
};

static void
Arcadia_DataDefinitionLanguage_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static void
Arcadia_DataDefinitionLanguage_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DataDefinitionLanguage_Parser_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Parser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Parser", Arcadia_DataDefinitionLanguage_Parser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Parser_getType(thread);
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
  self->scanner = Arcadia_DataDefinitionLanguage_Scanner_create(thread);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DataDefinitionLanguage_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  if (self->scanner) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner);
  }
}

Arcadia_DataDefinitionLanguage_Parser*
Arcadia_DataDefinitionLanguage_Parser_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Parser);
}

Arcadia_String*
Arcadia_DataDefinitionLanguage_Parser_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{ return Arcadia_DataDefinitionLanguage_Scanner_getWordText(thread, self->scanner); }

Arcadia_Natural32Value
Arcadia_DataDefinitionLanguage_Parser_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{ return Arcadia_DataDefinitionLanguage_Scanner_getWordType(thread, self->scanner); }

static void
Arcadia_DataDefinitionLanguage_Parser_next
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  do {
    Arcadia_DataDefinitionLanguage_Scanner_step(thread, self->scanner);
  } while (Arcadia_DataDefinitionLanguage_WordType_WhiteSpace == Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self) ||
           Arcadia_DataDefinitionLanguage_WordType_LineTerminator == Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self));
}

static Arcadia_DataDefinitionLanguage_Tree_ListNode*
Arcadia_DataDefinitionLanguage_Parser_onListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  Arcadia_DataDefinitionLanguage_Tree_ListNode* listNode = Arcadia_DataDefinitionLanguage_Tree_ListNode_create(thread);
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  // As long as we do nor hit a right square bracket or the end of the input, stay in loop.
  while (Arcadia_DataDefinitionLanguage_WordType_RightSquareBracket != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self) &&
         Arcadia_DataDefinitionLanguage_WordType_EndOfInput != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_DataDefinitionLanguage_Tree_Node* listElementNode = Arcadia_DataDefinitionLanguage_Parser_onValue(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, listNode->elements, (Arcadia_Object*)listElementNode);
    // If no comma follows, break the loop.
    if (Arcadia_DataDefinitionLanguage_WordType_Comma != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
      break;
    } else {
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
    }
  }
  if (Arcadia_DataDefinitionLanguage_WordType_RightSquareBracket != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  return listNode;
}

static Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*
Arcadia_DataDefinitionLanguage_Parser_onMapEntry
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  ) 
{
  Arcadia_DataDefinitionLanguage_Tree_NameNode* keyNode = Arcadia_DataDefinitionLanguage_Parser_onName(thread, self);
  if (Arcadia_DataDefinitionLanguage_WordType_Colon != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  Arcadia_DataDefinitionLanguage_Tree_Node* valueNode = Arcadia_DataDefinitionLanguage_Parser_onValue(thread, self);
  Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* mapEntryNode =
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create(thread, keyNode, valueNode);
  return mapEntryNode;
}

static Arcadia_DataDefinitionLanguage_Tree_MapNode*
Arcadia_DataDefinitionLanguage_Parser_onMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  Arcadia_DataDefinitionLanguage_Tree_MapNode* mapNode = Arcadia_DataDefinitionLanguage_Tree_MapNode_create(thread);
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  // As long as we do nor hit a right curly bracket or the end of the input, stay in loop.
  while (Arcadia_DataDefinitionLanguage_WordType_RightCurlyBracket != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self) && 
         Arcadia_DataDefinitionLanguage_WordType_EndOfInput != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* mapEntryNode =
      Arcadia_DataDefinitionLanguage_Parser_onMapEntry(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, mapNode->entries, (Arcadia_Object*)mapEntryNode);
    // If no comma follows, break the loop.
    if (Arcadia_DataDefinitionLanguage_WordType_Comma != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
      break;
    } else {
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
    }
  }
  if (Arcadia_DataDefinitionLanguage_WordType_RightCurlyBracket != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  return mapNode;
}

static Arcadia_DataDefinitionLanguage_Tree_NameNode*
Arcadia_DataDefinitionLanguage_Parser_onName
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  if (Arcadia_DataDefinitionLanguage_WordType_Name != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Tree_NameNode* nameNode = 
      Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  return nameNode;
}

static Arcadia_DataDefinitionLanguage_Tree_Node*
Arcadia_DataDefinitionLanguage_Parser_onValue
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  switch (Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    case Arcadia_DataDefinitionLanguage_WordType_BooleanLiteral: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Tree_BooleanNode_createString(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_IntegerLiteral: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Tree_NumberNode_createString(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_LeftCurlyBracket: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Parser_onMapValue(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_LeftSquareBracket: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Parser_onListValue(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_RealLiteral: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Tree_NumberNode_createString(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_StringLiteral: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Tree_StringNode_createString(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DataDefinitionLanguage_WordType_VoidLiteral: {
      Arcadia_DataDefinitionLanguage_Tree_Node* node = NULL;
      node = (Arcadia_DataDefinitionLanguage_Tree_Node*)
        Arcadia_DataDefinitionLanguage_Tree_VoidNode_createString(thread, Arcadia_DataDefinitionLanguage_Parser_getWordText(thread, self));
      Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
      return node;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

Arcadia_DataDefinitionLanguage_Tree_Node*
Arcadia_DataDefinitionLanguage_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self
  )
{
  if (Arcadia_DataDefinitionLanguage_WordType_StartOfInput != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DataDefinitionLanguage_Parser_next(thread, self);
  Arcadia_DataDefinitionLanguage_Tree_Node* valueNode = Arcadia_DataDefinitionLanguage_Parser_onValue(thread, self);
  if (Arcadia_DataDefinitionLanguage_WordType_EndOfInput != Arcadia_DataDefinitionLanguage_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return valueNode;
}

void
Arcadia_DataDefinitionLanguage_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Parser* self,
    Arcadia_Utf8Reader* input
  )
{
  Arcadia_DataDefinitionLanguage_Scanner_setInput(thread, self->scanner, input);
}
