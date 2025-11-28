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

#define ARCADIA_DDL_PRIVATE (1)
#include "Arcadia/DDL/Reader/Parser.h"

#include "Arcadia/DDL/Include.h"

#include "Arcadia/DDL/Nodes/Include.h"

/// @brief Get the text of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language parser.
/// @return The text of the word.
static Arcadia_String*
Arcadia_DDL_Parser_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

/// @brief Get the type of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language parser.
/// @return The type of the word.
static Arcadia_Natural32Value
Arcadia_DDL_Parser_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static void
Arcadia_DDL_Parser_next
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static Arcadia_DDL_ListNode*
Arcadia_DDL_Parser_onListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static Arcadia_DDL_MapEntryNode*
Arcadia_DDL_Parser_onMapEntry
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static Arcadia_DDL_MapNode*
Arcadia_DDL_Parser_onMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static Arcadia_DDL_NameNode*
Arcadia_DDL_Parser_onName
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static Arcadia_DDL_Node*
Arcadia_DDL_Parser_onValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

struct Arcadia_DDL_Parser {
  Arcadia_Object _parent;
  Arcadia_DDL_Scanner* scanner;
};

static void
Arcadia_DDL_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static void
Arcadia_DDL_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDL_Parser_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_Parser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.Parser", Arcadia_DDL_Parser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DDL_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_Parser_getType(thread);
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
  self->scanner = Arcadia_DDL_Scanner_create(thread);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DDL_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  if (self->scanner) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner);
  }
}

Arcadia_DDL_Parser*
Arcadia_DDL_Parser_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDL_Parser);
}

static Arcadia_String*
Arcadia_DDL_Parser_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{ return Arcadia_DDL_Scanner_getWordText(thread, self->scanner); }

static Arcadia_Natural32Value
Arcadia_DDL_Parser_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{ return Arcadia_DDL_Scanner_getWordType(thread, self->scanner); }

static void
Arcadia_DDL_Parser_next
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  do {
    Arcadia_DDL_Scanner_step(thread, self->scanner);
  } while (Arcadia_DDL_WordType_WhiteSpace == Arcadia_DDL_Parser_getWordType(thread, self) ||
           Arcadia_DDL_WordType_LineTerminator == Arcadia_DDL_Parser_getWordType(thread, self));
}

static Arcadia_DDL_ListNode*
Arcadia_DDL_Parser_onListValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  Arcadia_DDL_ListNode* listNode = Arcadia_DDL_ListNode_create(thread);
  Arcadia_DDL_Parser_next(thread, self);
  // As long as we do nor hit a right square bracket or the end of the input, stay in loop.
  while (Arcadia_DDL_WordType_RightSquareBracket != Arcadia_DDL_Parser_getWordType(thread, self) &&
         Arcadia_DDL_WordType_EndOfInput != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_DDL_Node* listElementNode = Arcadia_DDL_Parser_onValue(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, listNode->elements, (Arcadia_Object*)listElementNode);
    // If no comma follows, break the loop.
    if (Arcadia_DDL_WordType_Comma != Arcadia_DDL_Parser_getWordType(thread, self)) {
      break;
    } else {
      Arcadia_DDL_Parser_next(thread, self);
    }
  }
  if (Arcadia_DDL_WordType_RightSquareBracket != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_Parser_next(thread, self);
  return listNode;
}

static Arcadia_DDL_MapEntryNode*
Arcadia_DDL_Parser_onMapEntry
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  Arcadia_DDL_NameNode* keyNode = Arcadia_DDL_Parser_onName(thread, self);
  if (Arcadia_DDL_WordType_Colon != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_Parser_next(thread, self);
  Arcadia_DDL_Node* valueNode = Arcadia_DDL_Parser_onValue(thread, self);
  Arcadia_DDL_MapEntryNode* mapEntryNode =
    Arcadia_DDL_MapEntryNode_create(thread, keyNode, valueNode);
  return mapEntryNode;
}

static Arcadia_DDL_MapNode*
Arcadia_DDL_Parser_onMapValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  Arcadia_DDL_MapNode* mapNode = Arcadia_DDL_MapNode_create(thread);
  Arcadia_DDL_Parser_next(thread, self);
  // As long as we do nor hit a right curly bracket or the end of the input, stay in loop.
  while (Arcadia_DDL_WordType_RightCurlyBracket != Arcadia_DDL_Parser_getWordType(thread, self) &&
         Arcadia_DDL_WordType_EndOfInput != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      Arcadia_DDL_Parser_onMapEntry(thread, self);
    Arcadia_List_insertBackObjectReferenceValue(thread, mapNode->entries, (Arcadia_Object*)mapEntryNode);
    // If no comma follows, break the loop.
    if (Arcadia_DDL_WordType_Comma != Arcadia_DDL_Parser_getWordType(thread, self)) {
      break;
    } else {
      Arcadia_DDL_Parser_next(thread, self);
    }
  }
  if (Arcadia_DDL_WordType_RightCurlyBracket != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_Parser_next(thread, self);
  return mapNode;
}

static Arcadia_DDL_NameNode*
Arcadia_DDL_Parser_onName
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  if (Arcadia_DDL_WordType_Name != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_NameNode* nameNode =
      Arcadia_DDL_NameNode_create(thread, Arcadia_DDL_Parser_getWordText(thread, self));
  Arcadia_DDL_Parser_next(thread, self);
  return nameNode;
}

static Arcadia_DDL_Node*
Arcadia_DDL_Parser_onValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  switch (Arcadia_DDL_Parser_getWordType(thread, self)) {
    case Arcadia_DDL_WordType_BooleanLiteral: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_BooleanNode_createString(thread, Arcadia_DDL_Parser_getWordText(thread, self));
      Arcadia_DDL_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_IntegerLiteral: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_NumberNode_createString(thread, Arcadia_DDL_Parser_getWordText(thread, self));
      Arcadia_DDL_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_LeftCurlyBracket: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_Parser_onMapValue(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_LeftSquareBracket: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_Parser_onListValue(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_RealLiteral: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_NumberNode_createString(thread, Arcadia_DDL_Parser_getWordText(thread, self));
      Arcadia_DDL_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_StringLiteral: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_StringNode_createString(thread, Arcadia_DDL_Parser_getWordText(thread, self));
      Arcadia_DDL_Parser_next(thread, self);
      return node;
    } break;
    case Arcadia_DDL_WordType_VoidLiteral: {
      Arcadia_DDL_Node* node = NULL;
      node = (Arcadia_DDL_Node*)
        Arcadia_DDL_VoidNode_createString(thread, Arcadia_DDL_Parser_getWordText(thread, self));
      Arcadia_DDL_Parser_next(thread, self);
      return node;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

Arcadia_DDL_Node*
Arcadia_DDL_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{
  if (Arcadia_DDL_WordType_StartOfInput != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_Parser_next(thread, self);
  Arcadia_DDL_Node* valueNode = Arcadia_DDL_Parser_onValue(thread, self);
  if (Arcadia_DDL_WordType_Comma == Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_DDL_Parser_next(thread, self);
  }
  if (Arcadia_DDL_WordType_EndOfInput != Arcadia_DDL_Parser_getWordType(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SyntacticalError);
    Arcadia_Thread_jump(thread);
  }
  return valueNode;
}

void
Arcadia_DDL_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self,
    Arcadia_UTF8Reader* input
  )
{
  Arcadia_DDL_Scanner_setInput(thread, self->scanner, input);
}

Arcadia_Languages_StringTable*
Arcadia_DDL_Parser_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  )
{ return Arcadia_DDL_Scanner_getStringTable(thread, self->scanner); }
