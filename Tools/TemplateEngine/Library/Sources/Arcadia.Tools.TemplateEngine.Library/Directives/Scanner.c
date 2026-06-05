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

#include "Arcadia.Tools.TemplateEngine.Library/Directives/Scanner.h"

static void
Directives_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static void
Directives_Scanner_visit
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static void
Directives_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static void
Directives_Scanner_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_ScannerDispatch* self
  );

static Arcadia_Languages_StringTable*
Directives_Scanner_getStringTableImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static Arcadia_Languages_Diagnostics*
Directives_Scanner_getDiagnosticsImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self,
    Arcadia_Natural32Value expectedCodePoint
  );

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static void
scanName
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static void
scanString
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Directives_Scanner_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Directives_Scanner_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Directives_Scanner_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Directives_Scanner_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Directives.Scanner", Directives_Scanner,
                         u8"Arcadia.Languages.Scanner", Arcadia_Languages_Scanner,
                         &_typeOperations);

static void
Directives_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{/*Intentionally empty.*/}

static void
Directives_Scanner_visit
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics);
  }
  if (self->stringTable) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->stringTable);
  }
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
Directives_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  Arcadia_EnterConstructor(Directives_Scanner);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->diagnostics = Arcadia_Languages_Diagnostics_create(thread, (Arcadia_Log*)Arcadia_ConsoleLog_create(thread));
  self->stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);

  self->file = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->line = Arcadia_ValueStack_getNatural64Value(thread, 2);
  self->reader = (Arcadia_UnicodeCodePointReader*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_UnicodeCodePointReader_getType(thread));

  self->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  self->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  self->wordType = Arcadia_TemplateEngine_WordType_StartOfInput;

  Arcadia_LeaveConstructor(Directives_Scanner);
}

static void
Directives_Scanner_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_ScannerDispatch* self
  )
{
  ((Arcadia_Languages_ScannerDispatch*)self)->getDiagnostics = (Arcadia_Languages_Diagnostics * (*)(Arcadia_Thread*, Arcadia_Languages_Scanner*)) & Directives_Scanner_getDiagnosticsImpl;
  ((Arcadia_Languages_ScannerDispatch*)self)->getStringTable = (Arcadia_Languages_StringTable * (*)(Arcadia_Thread*, Arcadia_Languages_Scanner*)) & Directives_Scanner_getStringTableImpl;
}

static Arcadia_Languages_StringTable*
Directives_Scanner_getStringTableImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{ return self->stringTable; }

static Arcadia_Languages_Diagnostics*
Directives_Scanner_getDiagnosticsImpl
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{ return self->diagnostics; }

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self,
    Arcadia_Natural32Value expectedCodePoint
  )
{
  if (!Arcadia_UnicodeCodePointReader_hasValue(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
  return expectedCodePoint == currentCodePoint;
}

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  return is(thread, self, '+') || is(thread, self, '-');
}

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  if (!Arcadia_UnicodeCodePointReader_hasValue(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  if (!Arcadia_UnicodeCodePointReader_hasValue(thread, self->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
  return ('0' <= current && current <= '9');
}

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  return is(thread, self, '_');
}

static void
scanName
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  Arcadia_ByteArrayBuilder_clear(thread, self->temporaryBuffer);
  if (!isUnderscore(thread, self) && !isLetter(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  do {
    Arcadia_Natural32Value targetCodePoint = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
    Arcadia_Unicode_Encoder_encodeCodePoints(thread, self->temporary, &targetCodePoint, 1, self->temporaryBuffer);
    Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
  } while (isUnderscore(thread, self) || isLetter(thread, self) || isDigit(thread, self));
  self->wordType = Arcadia_TemplateEngine_WordType_Name;
}

static void
scanString
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  Arcadia_ByteArrayBuilder_clear(thread, self->temporaryBuffer);
  if (!is(thread, self, '"')) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);

  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (true) {
    if (!Arcadia_UnicodeCodePointReader_hasValue(thread, self->reader)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Natural32Value current = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          Arcadia_Natural32Value targetCodePoint = '\\';
          Arcadia_Unicode_Encoder_encodeCodePoints(thread, self->temporary, &targetCodePoint, 1, self->temporaryBuffer);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        case '"': {
          Arcadia_Natural32Value targetCodePoint = '"';
          Arcadia_Unicode_Encoder_encodeCodePoints(thread, self->temporary, &targetCodePoint, 1, self->temporaryBuffer);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
    } else {
      if (current == '"') {
        Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
        self->wordType = Arcadia_TemplateEngine_WordType_StringLiteral;
        return;
      } else if (current == '\\') {
        lastWasSlash = Arcadia_BooleanValue_True;
        Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      } else {
        Arcadia_Unicode_Encoder_encodeCodePoints(thread, self->temporary, &current, 1, self->temporaryBuffer);
        Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      }
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

Directives_Scanner*
Directives_Scanner_create
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
  ARCADIA_CREATEOBJECT(Directives_Scanner);
}

void
Directives_Scanner_setInput
  (
    Arcadia_Thread* thread,
	  Directives_Scanner* self,
	  Arcadia_String* file,
	  Arcadia_Natural64Value line,
    Arcadia_UnicodeCodePointReader* reader
  )
{
  self->file = file;
  self->line = line;
  self->reader = reader;
  self->wordType = Arcadia_TemplateEngine_WordType_StartOfInput;
}

void
Directives_Scanner_step
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  if (self->wordType == Arcadia_TemplateEngine_WordType_Error || self->wordType == Arcadia_TemplateEngine_WordType_EndOfInput) {
    return;
  }
  if (!Arcadia_UnicodeCodePointReader_hasValue(thread, self->reader)) {
    self->wordType = Arcadia_TemplateEngine_WordType_EndOfInput;
    return;
  }
  Arcadia_Natural32Value current = Arcadia_UnicodeCodePointReader_getValue(thread, self->reader);
  switch (current) {
    case '@': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_AtLiteral;
    } break;
    case '(': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_LeftParenthesis;
    } break;
    case ')': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_RightParenthesis;
    } break;
    case '{': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_LeftCurlyBracket;
    } break;
    case '}': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_RightCurlyBracket;
    } break;
    case '"': {
      scanString(thread, self);
    } break;
    case ',': {
      Arcadia_UnicodeCodePointReader_nextValue(thread, self->reader);
      self->wordType = Arcadia_TemplateEngine_WordType_Comma;
    } break;
    default: {
      scanName(thread, self);
    } break;
  }
}

Arcadia_String*
Directives_Scanner_getLiteral
  (
    Arcadia_Thread* thread,
    Directives_Scanner* self
  )
{
  return Arcadia_String_create_pn(thread, Arcadia_RuntimeByteArray_create(thread, self->temporaryBuffer->p, self->temporaryBuffer->sz));
}
