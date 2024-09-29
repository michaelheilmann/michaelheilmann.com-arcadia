// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Tools/Cilc/Scanner.h"

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
// The scanner can write to an output buffer an arbitrary UTF8 string, and UTF8 symbol, or the range of Bytes of (i,n,s) if s is not START, END, or ERROR.
#include <string.h>
#include "R.h"

#define CodePoint_Start (R_Utf8CodePoint_Last + 1)
#define CodePoint_End (R_Utf8CodePoint_Last + 2)
#define CodePoint_Error (R_Utf8CodePoint_Last + 3)

struct Cil_Scanner {
  // The index of the Byte in the input stream at which the current symbol starts.
  R_SizeValue i;
  // The length, in Bytes, of the current symbol "s".
  R_SizeValue n;
  // The current symbol "s".
  R_Natural32Value symbol;
  // The input stream.
  R_Utf8Reader* input;
  struct {
    /// The text of the token.
    R_StringBuffer* text;
    /// The type of the token.
    R_Natural32Value type;
  } token;
};

static void
Cil_Scanner_destruct
  (
    Cil_Scanner* self
  );

static void
Cil_Scanner_visit
  (
    Cil_Scanner* self
  );

static void
write
  (
    Cil_Scanner* self,
    R_Natural32Value codePoint
  );

static void
save
  (
    Cil_Scanner* self
  );

static void
next
  (
    Cil_Scanner* self
  );

static void
saveAndNext
  (
    Cil_Scanner* self
  );

static void
onEndToken
  (
    Cil_Scanner* self,
    Cil_TokenType type
  );

static R_BooleanValue
isAlphabetic
  (
    Cil_Scanner* self
  );

static R_BooleanValue
isDigit
  (
    Cil_Scanner* self
  );

static void
Cil_Scanner_destruct
  (
    Cil_Scanner* self
  )
{/*Intentionally empty.*/}

static void
Cil_Scanner_visit
  (
    Cil_Scanner* self
  )
{
  R_Object_visit(self->input);
  R_Object_visit(self->token.text);
}

static void
write
  (
    Cil_Scanner* self,
    R_Natural32Value codePoint
  )
{
  R_StringBuffer_appendCodePoints(self->token.text, &codePoint, R_SizeValue_Literal(1));
}

static void
save
  (
    Cil_Scanner* self
  )
{ write(self, self->symbol); }

static void
next
  (
    Cil_Scanner* self
  )
{
  if (R_Utf8Reader_hasCodePoint(self->input)) {
    self->symbol = R_Utf8Reader_getCodePoint(self->input);
    R_Utf8Reader_next(self->input);
  } else {
    self->symbol = CodePoint_End;
  }
}

static void
saveAndNext
  (
    Cil_Scanner* self
  )
{
  save(self);
  next(self);
}

static void
onEndToken
  (
    Cil_Scanner* self,
    Cil_TokenType type
  )
{
  self->token.type = type;
}

static R_BooleanValue
isAlphabetic
  (
    Cil_Scanner* self
  )
{
  return ('A' <= self->symbol && self->symbol <= 'Z')
      || ('a' <= self->symbol && self->symbol <= 'z');
}

static R_BooleanValue
isDigit
  (
    Cil_Scanner* self
  )
{
  return ('0' <= self->symbol && self->symbol <= '9');
}

void
_Cil_Scanner_registerType
  (
  )
{
  R_registerObjectType("Cil.Scanner", sizeof("Cil.Scanner") - 1, sizeof(Cil_Scanner), NULL, &Cil_Scanner_visit, &Cil_Scanner_destruct);
}

Cil_Scanner*
Cil_Scanner_create
  (
  )
{
  Cil_Scanner* self = R_allocateObject(R_getObjectType("Cil.Scanner", sizeof("Cil.Scanner") - 1));
  self->input = (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn("", sizeof("") - 1));
  self->symbol = CodePoint_Start;
  self->token.type = Cil_TokenType_StartOfInput;
  self->token.text = R_StringBuffer_create();
  return self;
}

R_Natural32Value
Cil_Scanner_getType
  (
    Cil_Scanner* self
  )
{ return self->token.type; }

void
Cil_Scanner_step
  (
    Cil_Scanner* self
  )
{
  R_StringBuffer_clear(self->token.text);
  if (CodePoint_End == self->symbol) {
    onEndToken(self, Cil_TokenType_EndOfInput);
    R_StringBuffer_append_pn(self->token.text, u8"<end of input>", sizeof(u8"<end of input>") - 1);
    return;
  }
  if (CodePoint_Start == self->symbol) {
    next(self);
  }
 
  // Whitespace :  <Whitespace> | <Tabulator>
  if (' ' == self->symbol || '\t' == self->symbol) {
    do {
      next(self);
    } while (' ' == self->symbol || '\t' == self->symbol);
    onEndToken(self, Cil_TokenType_WhiteSpaces);
    R_StringBuffer_append_pn(self->token.text, u8"<whitespaces>", sizeof(u8"<whitespaces>") - 1);
    return;
  }
  // LineTerminator : <LineFeed>
  //                  <CarriageReturn>
  //                  <CarriageReturn> <LineFeed>
  if ('\r' == self->symbol) {
    next(self);
    if ('\n' == self->symbol) {
      next(self);
    }
    onEndToken(self, Cil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  } else if ('\n' == self->symbol) {
    next(self);
    onEndToken(self, Cil_TokenType_LineTerminator);
    R_StringBuffer_append_pn(self->token.text, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
    return;
  }
  if ('=' == self->symbol) {
    // <assign>
    next(self);
    onEndToken(self, Cil_TokenType_Assign);
    R_StringBuffer_append_pn(self->token.text, u8"<assign>", sizeof(u8"<assign>") - 1);
    return;
  } else if ('"' == self->symbol) {
    // <string>    
    next(self);
    R_BooleanValue lastWasSlash = R_BooleanValue_False;
    while (R_BooleanValue_True) {
      if (lastWasSlash) {
        switch (self->symbol) {
          case '"': {
            write(self, '"');
            next(self);
          } break;
          case '\\': {
            write(self, '\\');
            next(self);
          } break;
          case 'n': {
            write(self, '\n');
            next(self);
          } break;
          case 'r': {
            write(self, '\r');
            next(self);
          } break;
          default: {
            R_setStatus(R_Status_LexicalError);
            R_jump();
          } break;
        }
      } else {
        if ('\\' == self->symbol) {
          lastWasSlash = R_BooleanValue_True;
          next(self);
        } else if ('"' == self->symbol) {
          next(self);
          break;
        } else if (CodePoint_End == self->symbol) {
          R_setStatus(R_Status_LexicalError);
          R_jump();
        } else {
          saveAndNext(self);
        }
      }
    }
    onEndToken(self, Cil_TokenType_StringLiteral);
    return;
  } else if ('_' == self->symbol || isAlphabetic(self)) {
    // <name>
    saveAndNext(self);
    while ('_' == self->symbol || isAlphabetic(self) || isDigit(self)) {
      saveAndNext(self);
    }
    onEndToken(self, Cil_TokenType_Name);
    return;
  } else if (isDigit(self)) {
    do {
      saveAndNext(self);
    } while (isDigit(self));
    if ('.' == self->symbol) {
      saveAndNext(self);
      while (isDigit(self)) {
        saveAndNext(self);
      }
      if ('e' == self->symbol || 'E' == self->symbol) {
        saveAndNext(self);
        if ('+' == self->symbol || '-' == self->symbol) {
          saveAndNext(self);
        }
        if (!isDigit(self)) {
          R_setStatus(R_Status_LexicalError);
          R_jump();
        }
        do {
          saveAndNext(self);
        } while (isDigit(self));
      }
    }
    onEndToken(self, Cil_TokenType_NumberLiteral);
  } else {
    R_setStatus(R_Status_LexicalError);
    R_jump();
  }
}

void
Cil_Scanner_setInput
  (
    Cil_Scanner* self,
    R_Utf8Reader* input
  )
{
  self->input = input;
  self->symbol = CodePoint_Start;
  self->token.type = Cil_TokenType_StartOfInput;
}
