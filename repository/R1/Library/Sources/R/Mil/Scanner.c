// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-22

#include "R/Mil/Scanner.h"

#include "R/Mil/Keywords.h"
#include "R/Mil/StringTable.h"

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
// This allows for efficient creation of strings (see R_String_create).
// Furthermore, it avoids to create a string twice by using a string table (see R_Mil_StringTable).
#include "R/cstdlib.h"
#include "R.h"

#define CodePoint_Start (R_Utf8CodePoint_Last + 1)
#define CodePoint_End (R_Utf8CodePoint_Last + 2)
#define CodePoint_Error (R_Utf8CodePoint_Last + 3)

struct R_Mil_Scanner {
  R_Object _parent;
  // The current symbol "s".
  Arcadia_Natural32Value symbol;
  // The input stream.
  R_Utf8Reader* input;
  // The string table.
  R_Mil_StringTable* stringTable;
  // The keywords.
  R_Mil_Keywords* keywords;
  struct {
    /// The text of the token.
    R_StringBuffer* text;
    /// The type of the token.
    Arcadia_Natural32Value type;
  } token;
};

static void
R_Mil_Scanner_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_Scanner_destruct
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static void
R_Mil_Scanner_visit
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static void
write
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self,
    Arcadia_Natural32Value codePoint
  );

static void
save
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static void
next
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static void
saveAndNext
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static void
onEndToken
  (
    R_Mil_Scanner* self,
    R_Mil_TokenType type
  );

static Arcadia_BooleanValue
isAlphabetic
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_Scanner_constructImpl,
  .destruct = &R_Mil_Scanner_destruct,
  .visit = &R_Mil_Scanner_visit,
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

Rex_defineObjectType(u8"Cil.Scanner", R_Mil_Scanner, u8"R.Object", R_Object, &_typeOperations);

static void
R_Mil_Scanner_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_Scanner* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_Scanner_getType(process);
  //
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  //
  _self->token.type = R_Mil_TokenType_StartOfInput;
  _self->token.text = NULL;
  _self->stringTable = NULL;
  _self->keywords = NULL;
  _self->input = NULL;
  _self->symbol = CodePoint_Start;
  //
  _self->keywords = R_Mil_Keywords_create(process);
  //
  _self->token.type = R_Mil_TokenType_StartOfInput;
  _self->stringTable = R_Mil_StringTable_create(process);
  _self->input = (R_Utf8Reader*)R_Utf8StringReader_create(process, R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"", sizeof(u8"") - 1)));
  _self->token.text = R_StringBuffer_create(process);
  //
  R_StringBuffer_append_pn(process, _self->token.text, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  //
  R_StringBuffer* temporary = R_StringBuffer_create(process);
#define On(text, type) \
  { \
    R_StringBuffer_clear(temporary); \
    R_StringBuffer_append_pn(process, temporary, text, sizeof(text) - 1); \
    R_Mil_Keywords_add(process, _self->keywords, R_Mil_StringTable_getOrCreateString(process, _self->stringTable, temporary), R_Mil_TokenType_##type); \
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
  // list operations
  On(u8"concatenate", Concatenate);
  // literals
  On(u8"void", VoidLiteral);
  On(u8"true", BooleanLiteral);
  On(u8"false", BooleanLiteral);
#undef On
  //
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Mil_Scanner_destruct
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{/*Intentionally empty.*/}

static void
R_Mil_Scanner_visit
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  R_Object_visit(self->input);
  R_Object_visit(self->token.text);
  R_Object_visit(self->stringTable);
  R_Object_visit(self->keywords);
}

static void
write
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self,
    Arcadia_Natural32Value codePoint
  )
{
  R_StringBuffer_appendCodePoints(process, self->token.text, &codePoint, Arcadia_SizeValue_Literal(1));
}

static void
save
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{ write(process, self, self->symbol); }

static void
next
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  if (R_Utf8Reader_hasCodePoint(process, self->input)) {
    self->symbol = R_Utf8Reader_getCodePoint(process, self->input);
    R_Utf8Reader_next(process, self->input);
  } else {
    self->symbol = CodePoint_End;
  }
}

static void
saveAndNext
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  save(process, self);
  next(process, self);
}

static void
onEndToken
  (
    R_Mil_Scanner* self,
    R_Mil_TokenType type
  )
{
  self->token.type = type;
}

static Arcadia_BooleanValue
isAlphabetic
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  return ('A' <= self->symbol && self->symbol <= 'Z')
      || ('a' <= self->symbol && self->symbol <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  return ('0' <= self->symbol && self->symbol <= '9');
}

R_Mil_Scanner*
R_Mil_Scanner_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Mil_Scanner* self = R_allocateObject(process, _R_Mil_Scanner_getType(process), 0, &argumentValues[0]);
  return self;
}

R_String*
R_Mil_Scanner_getTokenText
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{ return R_Mil_StringTable_getOrCreateString(process, self->stringTable, self->token.text); }

Arcadia_Natural32Value
R_Mil_Scanner_getTokenType
  (
    R_Mil_Scanner* self
  )
{ return self->token.type; }

static void
onEndOfLine
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  if ('\r' == self->symbol) {
    next(process, self);
    if ('\n' == self->symbol) {
      next(process, self);
    }
    onEndToken(self, R_Mil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(process, self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  } else if ('\n' == self->symbol) {
    next(process, self);
    onEndToken(self, R_Mil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(process, self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  }
}

void
R_Mil_Scanner_step
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self
  )
{
  R_StringBuffer_clear(self->token.text);
  if (CodePoint_Start == self->symbol) {
    next(process, self);
  }
  if (CodePoint_End == self->symbol) {
    onEndToken(self, R_Mil_TokenType_EndOfInput);
    R_StringBuffer_append_pn(process, self->token.text, u8"<end of input>", sizeof(u8"<end of input>") - 1);
    return;
  } 
  // Whitespace :  <Whitespace> | <Tabulator>
  if (' ' == self->symbol || '\t' == self->symbol) {
    do {
      next(process, self);
    } while (' ' == self->symbol || '\t' == self->symbol);
    onEndToken(self, R_Mil_TokenType_WhiteSpaces);
    R_StringBuffer_append_pn(process, self->token.text, u8"<whitespaces>", sizeof(u8"<whitespaces>") - 1);
    return;
  }
  // LineTerminator : <LineFeed>
  //                  <CarriageReturn>
  //                  <CarriageReturn> <LineFeed>
  if ('\r' == self->symbol) {
    next(process, self);
    if ('\n' == self->symbol) {
      next(process, self);
    }
    onEndToken(self, R_Mil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(process, self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  } else if ('\n' == self->symbol) {
    next(process, self);
    onEndToken(self, R_Mil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(process, self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  }
  if ('=' == self->symbol) {
    // <equals sign>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_EqualsSign);
    return;
  } else if (':' == self->symbol) {
     // <colon>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_Colon);
    return;
  } else if (',' == self->symbol) {
     // <comma>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_Comma);
    return;
  } else if ('{' == self->symbol) {
     // <left curly bracket>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_LeftCurlyBracket);
    return;
  } else if ('}' == self->symbol) {
     // <right curly bracket>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_RightCurlyBracket);
    return;
  } else if ('(' == self->symbol) {
     // <left parenthesis>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_LeftParenthesis);
    return;
  } else if (')' == self->symbol) {
     // <right parenthesis>
    saveAndNext(process, self);
    onEndToken(self, R_Mil_TokenType_RightParenthesis);
    return;
  } else if ('"' == self->symbol) {
    // <string>    
    next(process, self);
    Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
    while (Arcadia_BooleanValue_True) {
      if (lastWasSlash) {
        switch (self->symbol) {
          case '"': {
            write(process, self, '"');
            next(process, self);
          } break;
          case '\\': {
            write(process, self, '\\');
            next(process, self);
          } break;
          case 'n': {
            write(process, self, '\n');
            next(process, self);
          } break;
          case 'r': {
            write(process, self, '\r');
            next(process, self);
          } break;
          default: {
            Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
            Arcadia_Process_jump(process);
          } break;
        }
        lastWasSlash = Arcadia_BooleanValue_False;
      } else {
        if ('\\' == self->symbol) {
          lastWasSlash = Arcadia_BooleanValue_True;
          next(process, self);
        } else if ('"' == self->symbol) {
          next(process, self);
          break;
        } else if (CodePoint_End == self->symbol) {
          Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
          Arcadia_Process_jump(process);
        } else {
          saveAndNext(process, self);
        }
      }
    }
    onEndToken(self, R_Mil_TokenType_StringLiteral);
    return;
  } else if ('_' == self->symbol || isAlphabetic(process, self)) {
    // <name>
    saveAndNext(process, self);
    while ('_' == self->symbol || isAlphabetic(process, self) || isDigit(process, self)) {
      saveAndNext(process, self);
    }
    onEndToken(self, R_Mil_TokenType_Name);
    R_Mil_Keywords_scan(process, self->keywords, R_Mil_Scanner_getTokenText(process, self), &self->token.type);
    return;
  } else if (isDigit(process, self)) {
    do {
      saveAndNext(process, self);
    } while (isDigit(process,self));
    if ('.' == self->symbol) {
      saveAndNext(process, self);
      while (isDigit(process, self)) {
        saveAndNext(process, self);
      }
      if ('e' == self->symbol || 'E' == self->symbol) {
        saveAndNext(process, self);
        if ('+' == self->symbol || '-' == self->symbol) {
          saveAndNext(process, self);
        }
        if (!isDigit(process, self)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
          Arcadia_Process_jump(process);
        }
        do {
          saveAndNext(process, self);
        } while (isDigit(process, self));
      }
      onEndToken(self, R_Mil_TokenType_RealLiteral);
    } else {
      onEndToken(self, R_Mil_TokenType_IntegerLiteral);
    }
  } else if ('/' == self->symbol) {
    next(process, self);
    if ('*' == self->symbol) {
      // multi line comment
      next(process, self);
      while (true) {
        if (CodePoint_End == self->symbol) {
          Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
          Arcadia_Process_jump(process);
        } else if ('\n' == self->symbol) {
          next(process, self);
        } else if ('\r' == self->symbol) {
          next(process, self);
          if ('\n' == self->symbol) {
            next(process, self);
          }
        } else if ('*' == self->symbol) {
          next(process, self);
          if ('/' == self->symbol) {
            next(process, self);
            break;
          } else {
            write(process, self, '*');
          }
        }
      }
      onEndToken(self, R_Mil_TokenType_MultiLineComment);
    } else if ('/' == self->symbol) {
      // single line comment
      next(process, self);
      while (CodePoint_End != self->symbol && '\n' != self->symbol && '\r' != self->symbol) {
        saveAndNext(process, self);
      }
      onEndToken(self, R_Mil_TokenType_SingleLineComment);
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
      Arcadia_Process_jump(process);
    }
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_LexicalError);
    Arcadia_Process_jump(process);
  }
}

void
R_Mil_Scanner_setInput
  (
    Arcadia_Process* process,
    R_Mil_Scanner* self,
    R_Utf8Reader* input
  )
{
  self->input = input;
  self->symbol = CodePoint_Start;
  self->token.type = R_Mil_TokenType_StartOfInput;
  R_StringBuffer_clear(self->token.text);
  R_StringBuffer_append_pn(process, self->token.text, u8"<start of input>", sizeof(u8"<start of input>") - 1);
}
