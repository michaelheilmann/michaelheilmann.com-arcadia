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

#if !defined(CIL_TOKENTYPE_H_INCLUDED)
#define CIL_TOKENTYPE_H_INCLUDED

#include "R.h"

typedef enum Cil_TokenType {

  // Start of input.
  Cil_TokenType_StartOfInput,
  // End of input.
  Cil_TokenType_EndOfInput,

  // LF, CR or CR LF
  Cil_TokenType_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  Cil_TokenType_WhiteSpaces,

  // The `Equals Sign` / `=`  / U+003D.
  Cil_TokenType_EqualsSign,
  // The `Colon` / `:` / U+003A.
  Cil_TokenType_Colon,
  // The `Comma` / `,` / U+002C.
  Cil_TokenType_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  Cil_TokenType_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  Cil_TokenType_RightCurlyBracket,
  // The `Left Parenthesis` / `(` / U+0028.
  Cil_TokenType_LeftParenthesis,
  // The `Right Parenthesis`/ `)` / U+0029.
  Cil_TokenType_RightParenthesis,


  // A name.
  Cil_TokenType_Name,

  // A boolean literal.
  // `true` or `false`.
  Cil_TokenType_BooleanLiteral,
  // A number literal.
  Cil_TokenType_NumberLiteral,
  // A string literal.
  Cil_TokenType_StringLiteral,
  // A void literal.
  // `void`.
  Cil_TokenType_VoidLiteral,

  // "class"
  Cil_TokenType_Class,
  // "constructor"
  Cil_TokenType_Constructor,
  // "extends"
  Cil_TokenType_Extends,
  // "implements"
  Cil_TokenType_Implements,
  // "procedure"
  Cil_TokenType_Procedure,
  // "method"
  Cil_TokenType_Method,

  // "native"
  Cil_TokenType_Native,
  // "return"
  Cil_TokenType_Return,
  // "variable"
  Cil_TokenType_Variable,

  // "add" (arithmetic operations)
  Cil_TokenType_Add,
  // "subtract" (arithmetic operations)
  Cil_TokenType_Subtract,
  // "multiply" (arithmetic operations)
  Cil_TokenType_Multiply,
  // "divide" (arithmetic operations)
  Cil_TokenType_Divide,

  // "negate" (arithmetic operations/logical operations)
  Cil_TokenType_Negate,

  // "not" (boolean operations)
  Cil_TokenType_Not,
  // "and" (boolean operations)
  Cil_TokenType_And,
  // "or" (boolean operations)
  Cil_TokenType_Or,

  // "concatenate" (list operations)
  Cil_TokenType_Concatenate,

  /// A single line comment.
  Cil_TokenType_SingleLineComment,
  /// A multi line comment.
  Cil_TokenType_MultiLineComment,

} Cil_TokenType;

#endif // CIL_TOKENTYPE_H_INCLUDED
