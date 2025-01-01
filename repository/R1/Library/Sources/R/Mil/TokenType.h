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

#if !defined(R_MIL_TOKENTYPE_H_INCLUDED)
#define R_MIL_TOKENTYPE_H_INCLUDED

#include "R.h"

typedef enum R_Mil_TokenType {

  // Start of input.
  R_Mil_TokenType_StartOfInput,
  // End of input.
  R_Mil_TokenType_EndOfInput,

  // LF, CR or CR LF
  R_Mil_TokenType_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  R_Mil_TokenType_WhiteSpaces,

  // The `Equals Sign` / `=`  / U+003D.
  R_Mil_TokenType_EqualsSign,
  // The `Colon` / `:` / U+003A.
  R_Mil_TokenType_Colon,
  // The `Comma` / `,` / U+002C.
  R_Mil_TokenType_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  R_Mil_TokenType_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  R_Mil_TokenType_RightCurlyBracket,
  // The `Left Parenthesis` / `(` / U+0028.
  R_Mil_TokenType_LeftParenthesis,
  // The `Right Parenthesis`/ `)` / U+0029.
  R_Mil_TokenType_RightParenthesis,


  // A name.
  R_Mil_TokenType_Name,

  // A boolean literal.
  // `true` or `false`.
  R_Mil_TokenType_BooleanLiteral,
  // A real number literal.
  R_Mil_TokenType_RealLiteral,
  // An integer literal.
  R_Mil_TokenType_IntegerLiteral,
  // A string literal.
  R_Mil_TokenType_StringLiteral,
  // A void literal.
  // `void`.
  R_Mil_TokenType_VoidLiteral,

  // "class"
  R_Mil_TokenType_Class,
  // "constructor"
  R_Mil_TokenType_Constructor,
  // "extends"
  R_Mil_TokenType_Extends,
  // "implements"
  R_Mil_TokenType_Implements,
  // "procedure"
  R_Mil_TokenType_Procedure,
  // "method"
  R_Mil_TokenType_Method,

  // "invoke"
  R_Mil_TokenType_Invoke,

  // "native"
  R_Mil_TokenType_Native,
  // "entry"
  R_Mil_TokenType_Entry,
  // "return"
  R_Mil_TokenType_Return,
  // "variable"
  R_Mil_TokenType_Variable,

  // "add" (arithmetic operations)
  R_Mil_TokenType_Add,
  // "subtract" (arithmetic operations)
  R_Mil_TokenType_Subtract,
  // "multiply" (arithmetic operations)
  R_Mil_TokenType_Multiply,
  // "divide" (arithmetic operations)
  R_Mil_TokenType_Divide,

  // "negate" (arithmetic operations/logical operations)
  R_Mil_TokenType_Negate,

  // "not" (boolean operations)
  R_Mil_TokenType_Not,
  // "and" (boolean operations)
  R_Mil_TokenType_And,
  // "or" (boolean operations)
  R_Mil_TokenType_Or,

  // "concatenate" (list operations)
  R_Mil_TokenType_Concatenate,

  /// A single line comment.
  R_Mil_TokenType_SingleLineComment,
  /// A multi line comment.
  R_Mil_TokenType_MultiLineComment,

} R_Mil_TokenType;

#endif // R_MIL_TOKENTYPE_H_INCLUDED
