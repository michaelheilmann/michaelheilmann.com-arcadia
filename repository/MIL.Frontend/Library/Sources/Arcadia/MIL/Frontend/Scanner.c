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

#include "Arcadia/MIL/Frontend/Scanner.h"

#include "Arcadia/MIL/Frontend/Include.h"
#include "Arcadia/MIL/Frontend/Keywords.h"
#include "Arcadia/MIL/Frontend/StringTable.h"

// This scanner maintains a tuple (i,n,s):
// i is the zero-based index of the Byte at which the current UTF8 symbol starts in the input stream.
// n is the length, in Bytes, of the current UTF8 symbol in the input stream.
// s denotes the current symbol.
//
// There are three symbols different from all UTF8 symbols. These are START, END, and ERROR each of a size, in Bytes, of 0.
//
// The initial values of a scanner is (0,0,START).
//
// When the scanner is in some state (i,n,s) and is advanced to the next symbol,
// then there are two possible outcomes:
// - if the next 1-4 Bytes form a valid next symbol:
//   i is incremented by the number of Bytes of the old symbol, n is assigned the size, in Bytes, of the next symbol, and s is assigned the next symbol.
// - the next 1-4 Bytes do not form a valid next symbol:
//   i is not incremented, n is assigned the size, in Bytes, of the ERROR symbol, and s is assigned the ERROR symbol.
// - there is no next symbol (that is, the end of the input was reached)
//   i is not incremented, n is assigned the size, in Bytes, of the EDN symbol, and s is assigned the END symbol.
//
// The scanner writes the lexeme to a string buffer.
// This allows for efficient creation of strings (see Arcadia_String_create).
// Furthermore, it avoids to create a string twice by using a string table (see Arcadia_MIL_StringTable).

#define CodePoint_Start (Arcadia_Unicode_CodePoint_Last + 1)
#define CodePoint_End (Arcadia_Unicode_CodePoint_Last + 2)
#define CodePoint_Error (Arcadia_Unicode_CodePoint_Last + 3)

struct Arcadia_MIL_Scanner {
  Arcadia_Object _parent;
  // The current symbol "s".
  Arcadia_Natural32Value symbol;
  // The input stream.
  Arcadia_Utf8Reader* input;
  // The string table.
  Arcadia_MIL_StringTable* stringTable;
  // The keywords.
  Arcadia_MIL_Keywords* keywords;
  struct {
    /// The text of the token.
    Arcadia_StringBuffer* text;
    /// The type of the token.
    Arcadia_Natural32Value type;
  } token;
};

static void
Arcadia_MIL_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
Arcadia_MIL_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
Arcadia_MIL_Scanner_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
write
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self,
    Arcadia_Natural32Value codePoint
  );

static void
save
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
saveAndNext
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static void
onEndToken
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self,
    Arcadia_MIL_TokenType type
  );

static Arcadia_BooleanValue
isAlphabetic
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_MIL_Scanner_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_MIL_Scanner_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Scanner_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Scanner", Arcadia_MIL_Scanner,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Scanner_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->token.type = Arcadia_MIL_TokenType_StartOfInput;
  self->token.text = NULL;
  self->stringTable = NULL;
  self->keywords = NULL;
  self->input = NULL;
  self->symbol = CodePoint_Start;
  //
  self->keywords = Arcadia_MIL_Keywords_create(thread);
  //
  self->token.type = Arcadia_MIL_TokenType_StartOfInput;
  self->stringTable = Arcadia_MIL_StringTable_create(thread);
  self->input = (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"", sizeof(u8"") - 1)));
  self->token.text = Arcadia_StringBuffer_create(thread);
  //
  Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<start of input>");
  //
  Arcadia_StringBuffer* temporary = Arcadia_StringBuffer_create(thread);
#define On(text, type) \
  { \
    Arcadia_StringBuffer_clear(thread, temporary); \
    Arcadia_StringBuffer_insertBackCxxString(thread, temporary, text); \
    Arcadia_MIL_Keywords_add(thread, self->keywords, Arcadia_MIL_StringTable_getOrCreateString(thread, self->stringTable, temporary), Arcadia_MIL_TokenType_##type); \
  }
  //
  On(u8"class", Class);
  On(u8"constructor", Constructor);
  On(u8"entry", Entry)
  On(u8"extends", Extends);
  On(u8"implements", Implements);
  On(u8"method", Method);
  On(u8"procedure", Procedure);
  //
  On(u8"native", Native);
  //
  On(u8"return", Return);
  //
  On(u8"variable", Variable);
  //
  On(u8"jump", Jump);
  On(u8"jumpIfTrue", JumpIfTrue);
  On(u8"jumpIfFalse", JumpIfFalse);
  //
  On(u8"raise", Raise);
  // arithmetic operations
  On(u8"add", Add);
  On(u8"subtract", Subtract);
  On(u8"multiply", Multiply);
  On(u8"divide", Divide);
  // arithmetic operations/logical operations
  On(u8"negate", Negate);
  // logcial operations
  On(u8"not", Not);
  On(u8"and", And);
  On(u8"or", Or);
  // relational operations
  On(u8"isEqualTo", IsEqualTo);
  On(u8"isNotEqualTo", IsNotEqualTo);
  On(u8"isLowerThan", IsLowerThan);
  On(u8"isLowerThanOrEqualTo", IsLowerThanOrEqualTo);
  On(u8"isGreaterThan", IsGreaterThan);
  On(u8"isGreaterThanOrEqualTo", IsGreaterThanOrEqualTo);
  // list operations
  On(u8"concatenate", Concatenate);
  // set operations
  On(u8"set", Set);
  // literals
  On(u8"void", VoidLiteral);
  On(u8"true", BooleanLiteral);
  On(u8"false", BooleanLiteral);
#undef On
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_Scanner_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->input);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->token.text);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->stringTable);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->keywords);
}

static void
write
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self,
    Arcadia_Natural32Value codePoint
  )
{
  Arcadia_StringBuffer_insertCodePointsBack(thread, self->token.text, &codePoint, Arcadia_SizeValue_Literal(1));
}

static void
save
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{ write(thread, self, self->symbol); }

static void
next
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  if (Arcadia_Utf8Reader_hasCodePoint(thread, self->input)) {
    self->symbol = Arcadia_Utf8Reader_getCodePoint(thread, self->input);
    Arcadia_Utf8Reader_next(thread, self->input);
  } else {
    self->symbol = CodePoint_End;
  }
}

static void
saveAndNext
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  save(thread, self);
  next(thread, self);
}

static void
onEndToken
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self,
    Arcadia_MIL_TokenType type
  )
{
  self->token.type = type;
}

static Arcadia_BooleanValue
isAlphabetic
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  return ('A' <= self->symbol && self->symbol <= 'Z')
      || ('a' <= self->symbol && self->symbol <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  return ('0' <= self->symbol && self->symbol <= '9');
}

Arcadia_MIL_Scanner*
Arcadia_MIL_Scanner_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Scanner);
}

Arcadia_String*
Arcadia_MIL_Scanner_getTokenText
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{ return Arcadia_MIL_StringTable_getOrCreateString(thread, self->stringTable, self->token.text); }

Arcadia_Natural32Value
Arcadia_MIL_Scanner_getTokenType
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{ return self->token.type; }

static void
onEndOfLine
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  if ('\r' == self->symbol) {
    next(thread, self);
    if ('\n' == self->symbol) {
      next(thread, self);
    }
    onEndToken(thread, self, Arcadia_MIL_TokenType_LineTerminator);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<line terminator>");
    return;
  } else if ('\n' == self->symbol) {
    next(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_LineTerminator);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<line terminator>");
    return;
  }
}

void
Arcadia_MIL_Scanner_step
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self
  )
{
  Arcadia_StringBuffer_clear(thread, self->token.text);
  if (CodePoint_Start == self->symbol) {
    next(thread, self);
  }
  if (CodePoint_End == self->symbol) {
    onEndToken(thread, self, Arcadia_MIL_TokenType_EndOfInput);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<end of input>");
    return;
  }
  // Whitespace :  <Whitespace> | <Tabulator>
  if (' ' == self->symbol || '\t' == self->symbol) {
    do {
      next(thread, self);
    } while (' ' == self->symbol || '\t' == self->symbol);
    onEndToken(thread, self, Arcadia_MIL_TokenType_WhiteSpaces);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<whitespaces>");
    return;
  }
  // LineTerminator : <LineFeed>
  //                  <CarriageReturn>
  //                  <CarriageReturn> <LineFeed>
  if ('\r' == self->symbol) {
    next(thread, self);
    if ('\n' == self->symbol) {
      next(thread, self);
    }
    onEndToken(thread, self, Arcadia_MIL_TokenType_LineTerminator);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<line terminator>");
    return;
  } else if ('\n' == self->symbol) {
    next(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_LineTerminator);
    Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<line terminator>");
    return;
  }
  if ('=' == self->symbol) {
    // <equals sign>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_EqualsSign);
    return;
  } else if (':' == self->symbol) {
     // <colon>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_Colon);
    return;
  } else if (',' == self->symbol) {
     // <comma>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_Comma);
    return;
  } else if ('{' == self->symbol) {
     // <left curly bracket>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_LeftCurlyBracket);
    return;
  } else if ('}' == self->symbol) {
     // <right curly bracket>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_RightCurlyBracket);
    return;
  } else if ('(' == self->symbol) {
     // <left parenthesis>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_LeftParenthesis);
    return;
  } else if (')' == self->symbol) {
     // <right parenthesis>
    saveAndNext(thread, self);
    onEndToken(thread, self, Arcadia_MIL_TokenType_RightParenthesis);
    return;
  } else if ('"' == self->symbol) {
    // <string>
    next(thread, self);
    Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
    while (Arcadia_BooleanValue_True) {
      if (lastWasSlash) {
        switch (self->symbol) {
          case '"': {
            write(thread, self, '"');
            next(thread, self);
          } break;
          case '\\': {
            write(thread, self, '\\');
            next(thread, self);
          } break;
          case 'n': {
            write(thread, self, '\n');
            next(thread, self);
          } break;
          case 'r': {
            write(thread, self, '\r');
            next(thread, self);
          } break;
          default: {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
            Arcadia_Thread_jump(thread);
          } break;
        }
        lastWasSlash = Arcadia_BooleanValue_False;
      } else {
        if ('\\' == self->symbol) {
          lastWasSlash = Arcadia_BooleanValue_True;
          next(thread, self);
        } else if ('"' == self->symbol) {
          next(thread, self);
          break;
        } else if (CodePoint_End == self->symbol) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
          Arcadia_Thread_jump(thread);
        } else {
          saveAndNext(thread, self);
        }
      }
    }
    onEndToken(thread, self, Arcadia_MIL_TokenType_StringLiteral);
    return;
  } else if ('$' == self->symbol) {
    // <register>
    saveAndNext(thread, self);
    // a <register> is one of the following:
    // a) a '$' followed by a digit between 0 and 9
    // b) a '$' followed by a digit between 1 and 9 folloed by one or more digits between 0 and 9
    // c) a '$' followed by a <name>
    if ('0' == self->symbol) {
      saveAndNext(thread, self);
    } else if ('1' <= self->symbol && self->symbol <= '9') {
      saveAndNext(thread, self);
      while (isDigit(thread, self)) {
        saveAndNext(thread, self);
      }
    } else if ('_' == self->symbol || isAlphabetic(thread, self)) {
      saveAndNext(thread, self);
      while ('_' == self->symbol || isAlphabetic(thread, self) || isDigit(thread, self)) {
        saveAndNext(thread, self);
      }
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
      Arcadia_Thread_jump(thread);
    }
    onEndToken(thread, self, Arcadia_MIL_TokenType_Register);
    return;
  } else if ('_' == self->symbol || isAlphabetic(thread, self)) {
    // <name>
    saveAndNext(thread, self);
    while ('_' == self->symbol || isAlphabetic(thread, self) || isDigit(thread, self)) {
      saveAndNext(thread, self);
    }
    onEndToken(thread, self, Arcadia_MIL_TokenType_Name);
    Arcadia_MIL_Keywords_scan(thread, self->keywords, Arcadia_MIL_Scanner_getTokenText(thread, self), &self->token.type);
    return;
  } else if (isDigit(thread, self)) {
    do {
      saveAndNext(thread, self);
    } while (isDigit(thread,self));
    if ('.' == self->symbol) {
      saveAndNext(thread, self);
      while (isDigit(thread, self)) {
        saveAndNext(thread, self);
      }
      if ('e' == self->symbol || 'E' == self->symbol) {
        saveAndNext(thread, self);
        if ('+' == self->symbol || '-' == self->symbol) {
          saveAndNext(thread, self);
        }
        if (!isDigit(thread, self)) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
          Arcadia_Thread_jump(thread);
        }
        do {
          saveAndNext(thread, self);
        } while (isDigit(thread, self));
      }
      onEndToken(thread, self, Arcadia_MIL_TokenType_RealLiteral);
    } else {
      onEndToken(thread, self, Arcadia_MIL_TokenType_IntegerLiteral);
    }
  } else if ('/' == self->symbol) {
    next(thread, self);
    if ('*' == self->symbol) {
      // multi line comment
      next(thread, self);
      while (true) {
        if (CodePoint_End == self->symbol) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
          Arcadia_Thread_jump(thread);
        } else if ('\n' == self->symbol) {
          next(thread, self);
        } else if ('\r' == self->symbol) {
          next(thread, self);
          if ('\n' == self->symbol) {
            next(thread, self);
          }
        } else if ('*' == self->symbol) {
          next(thread, self);
          if ('/' == self->symbol) {
            next(thread, self);
            break;
          } else {
            write(thread, self, '*');
          }
        }
      }
      onEndToken(thread, self, Arcadia_MIL_TokenType_MultiLineComment);
    } else if ('/' == self->symbol) {
      // single line comment
      next(thread, self);
      while (CodePoint_End != self->symbol && '\n' != self->symbol && '\r' != self->symbol) {
        saveAndNext(thread, self);
      }
      onEndToken(thread, self, Arcadia_MIL_TokenType_SingleLineComment);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
      Arcadia_Thread_jump(thread);
    }
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_LexicalError);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_MIL_Scanner_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* self,
    Arcadia_Utf8Reader* input
  )
{
  self->input = input;
  self->symbol = CodePoint_Start;
  self->token.type = Arcadia_MIL_TokenType_StartOfInput;
  Arcadia_StringBuffer_clear(thread, self->token.text);
  Arcadia_StringBuffer_insertBackCxxString(thread, self->token.text, u8"<start of input>");
}
