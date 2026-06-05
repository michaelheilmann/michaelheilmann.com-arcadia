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

static void
DirectivesScannner_step
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
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Directives_Parser_initializeDispatchImpl,
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
  if (self->scanner) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scanner);
  }
}

static void
Directives_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  Arcadia_EnterConstructor(Directives_Parser);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_String* file = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  Arcadia_Natural64Value line = Arcadia_ValueStack_getNatural64Value(thread, 2);
  Arcadia_UnicodeCodePointReader* reader = (Arcadia_UnicodeCodePointReader*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_UnicodeCodePointReader_getType(thread));
  self->scanner = Directives_Scanner_create(thread, file, line, reader);
  Arcadia_LeaveConstructor(Directives_Parser);
}

static void
Directives_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_ParserDispatch* self
  )
{/*Intentionally empty.*/}

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return self->scanner->wordType == Arcadia_TemplateEngine_WordType_LeftParenthesis;
}

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return self->scanner->wordType == Arcadia_TemplateEngine_WordType_RightParenthesis;;
}

static Arcadia_String*
getLiteral
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  return Directives_Scanner_getLiteral(thread, self->scanner);
}

static Directives_Tree*
parseExpression
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  Directives_Tree* ast = NULL;
  if (self->scanner->wordType != Arcadia_TemplateEngine_WordType_Name) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* name = getLiteral(thread, self);
  DirectivesScannner_step(thread, self);
  if (isLeftParenthesis(thread, self)) {
    DirectivesScannner_step(thread, self);
    Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    while (self->scanner->wordType == Arcadia_TemplateEngine_WordType_StringLiteral) {
      Arcadia_String* argument = getLiteral(thread, self);
      Arcadia_List_insertBackObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
      DirectivesScannner_step(thread, self);
      if (self->scanner->wordType == Arcadia_TemplateEngine_WordType_Comma) {
        DirectivesScannner_step(thread, self);
      }
    }
    if (!isRightParenthesis(thread, self)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    DirectivesScannner_step(thread, self);
    ast = Directives_Tree_createInvokeExpr(thread, name, arguments);
  } else {
    ast = Directives_Tree_createNameExpr(thread, name);
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

static void 
DirectivesScannner_step
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  Directives_Scanner_step(thread, self->scanner);
}

static Directives_Tree*
parseDirective
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  )
{
  if (self->scanner->wordType != Arcadia_TemplateEngine_WordType_StartOfInput) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  DirectivesScannner_step(thread, self);
  switch (self->scanner->wordType) {
    case Arcadia_TemplateEngine_WordType_AtLiteral: {
      Directives_Tree* ast = Directives_Tree_createAtLiteralExpr(thread);
      return ast;
    } break;
    case Arcadia_TemplateEngine_WordType_LeftCurlyBracket: {
      DirectivesScannner_step(thread, self);
      Directives_Tree* ast = parseStatement(thread, self);
      if (self->scanner->wordType != Arcadia_TemplateEngine_WordType_RightCurlyBracket) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
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
    Arcadia_UnicodeCodePointReader* reader
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
    Arcadia_UnicodeCodePointReader* reader
  )
{
  Directives_Scanner_setInput(thread, self->scanner, file, line, reader);
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
