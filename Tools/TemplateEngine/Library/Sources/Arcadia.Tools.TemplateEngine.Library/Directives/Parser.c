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

#include "Arcadia.Tools.TemplateEngine.Library/Directives/Parser.h"

static void
Directives_Parser_destruct
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static void
Directives_Parser_visit
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static void
Directives_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static void
Directives_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_ParserDispatch* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Directives_Parser* self,
    Arcadia_Natural32Value expectedCodePoint
  );

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Arcadia_String*
getLiteral
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static void
parseIdentifier
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static void
parseString
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Directives_Tree*
parseExpression
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );
  
static Directives_Tree*
parseStatement
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static Directives_Tree*
parseDirective
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Directives_Parser_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Directives_Parser_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Directives_Parser_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Directives.Parser", Directives_Parser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Directives_Parser_destruct
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{/*Intentionally empty.*/}

static void
Directives_Parser_visit
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (self->file) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->file);
  }
  if (self->reader) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->reader);
  }
  if (self->temporary) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporary);
  }
  if (self->temporaryBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporaryBuffer);
  }
} 

static void
Directives_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  Arcadia_TypeValue _type = _Directives_Parser_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->file = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->line = Arcadia_ValueStack_getNatural64Value(thread, 2);
  self->reader = (Arcadia_UTF8Reader*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_UTF8Reader_getType(thread)); 

  self->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  self->temporary = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, self->temporaryBuffer);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Directives_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_ParserDispatch* self
  )
{ }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Directives_Parser* self,
    Arcadia_Natural32Value expectedCodePoint
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
  return expectedCodePoint == currentCodePoint;
}

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return is(thread, self, '+') || is(thread, self, '-');
}

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
  return ('0' <= current && current <= '9');
}

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return is(thread, self, '_');
}

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return is(thread, self, '(');
}

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return is(thread, self, ')');
}

static Arcadia_String*
getLiteral
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return Arcadia_String_create_pn(thread, Arcadia_InternalImmutableByteArray_create(thread, self->temporaryBuffer->p, self->temporaryBuffer->sz));
}

static void
parseIdentifier
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (!isUnderscore(thread, self) && !isLetter(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  do {
    Arcadia_Natural32Value targetCodePoint = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
    Arcadia_UTF8Writer_writeCodePoints(thread, self->temporary, &targetCodePoint, 1);
    Arcadia_UTF8Reader_next(thread, self->reader);
  } while (isUnderscore(thread, self) || isLetter(thread, self) || isDigit(thread, self));
}

static void
parseString
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (!is(thread, self, '"')) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_UTF8Reader_next(thread, self->reader);

  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (true) {
    if (!Arcadia_UTF8Reader_hasCodePoint(thread, self->reader)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Natural32Value current = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          Arcadia_Natural32Value targetCodePoint = '\\';
          Arcadia_UTF8Writer_writeCodePoints(thread, self->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        case '"': {
          Arcadia_Natural32Value targetCodePoint = '"';
          Arcadia_UTF8Writer_writeCodePoints(thread, self->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
    } else {
      if (current == '"') {
        Arcadia_UTF8Reader_next(thread, self->reader);
        return;
      } else if (current == '\\') {
        lastWasSlash = Arcadia_BooleanValue_True;
        Arcadia_UTF8Reader_next(thread, self->reader);
      } else {
        Arcadia_UTF8Writer_writeCodePoints(thread, self->temporary, &current, 1);
        Arcadia_UTF8Reader_next(thread, self->reader);
      }
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

static Directives_Tree*
parseExpression
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  Directives_Tree* ast = NULL;
  Arcadia_ByteBuffer_clear(thread, self->temporaryBuffer);
  parseIdentifier(thread, self);
  Arcadia_String* name = getLiteral(thread, self);
  Arcadia_String* argument = NULL;
  if (isLeftParenthesis(thread, self)) {
    Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    Arcadia_UTF8Reader_next(thread, self->reader);
    if (is(thread, self, '"')) {
      Arcadia_ByteBuffer_clear(thread, self->temporaryBuffer);
      parseString(thread, self);
      argument = getLiteral(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
    }
    if (!isRightParenthesis(thread, self)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_UTF8Reader_next(thread, self->reader);
    ast = Directives_Tree_createInvoke(thread, name, arguments);
  } else {
    ast = Directives_Tree_createGetVariable(thread, name);
  }
  return ast;
}

static Directives_Tree*
parseStatement
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return parseExpression(thread, self);
}

static Directives_Tree*
parseDirective
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, self->reader)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural32Value current = Arcadia_UTF8Reader_getCodePoint(thread, self->reader);
  switch (current) {
    case '@': {
      Directives_Tree* ast = Directives_Tree_createAt(thread);
      Arcadia_UTF8Reader_next(thread, self->reader);
      return ast;
    } break;
    case '{': {
      Arcadia_UTF8Reader_next(thread, self->reader);
      Directives_Tree* ast = parseStatement(thread, self);
      if (!is(thread, self, '}')) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_UTF8Reader_next(thread, self->reader);
      return ast;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

Directives_Parser*
Directives_Parser_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* file,
	  Arcadia_Natural64Value line,
	  Arcadia_UTF8Reader* reader
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)file);
  Arcadia_ValueStack_pushNatural64Value(thread, line);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)reader);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Directives_Parser);
}

void
Directives_Parser_setInput
  (
    Arcadia_Thread* thread,
	  Directives_Parser* self,
	  Arcadia_String* file,
	  Arcadia_Natural64Value line,
	  Arcadia_UTF8Reader* reader
  )
{
  self->file = file;
  self->line = line;
  self->reader = reader;
}

Directives_Tree*
Directives_Parser_run
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return parseDirective(thread, self);
}
