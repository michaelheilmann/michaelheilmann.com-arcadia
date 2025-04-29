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

// Last modified: 2024-09-22

#if !defined(ARCADIA_MIL_TOKENTYPE_H_INCLUDED)
#define ARCADIA_MIL_TOKENTYPE_H_INCLUDED

#include "R/Include.h"

typedef enum Arcadia_Mil_TokenType {

  // Start of input.
  Arcadia_Mil_TokenType_StartOfInput,
  // End of input.
  Arcadia_Mil_TokenType_EndOfInput,

  // LF, CR or CR LF
  Arcadia_Mil_TokenType_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  Arcadia_Mil_TokenType_WhiteSpaces,

  // The `Equals Sign` / `=`  / U+003D.
  Arcadia_Mil_TokenType_EqualsSign,
  // The `Colon` / `:` / U+003A.
  Arcadia_Mil_TokenType_Colon,
  // The `Comma` / `,` / U+002C.
  Arcadia_Mil_TokenType_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  Arcadia_Mil_TokenType_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  Arcadia_Mil_TokenType_RightCurlyBracket,
  // The `Left Parenthesis` / `(` / U+0028.
  Arcadia_Mil_TokenType_LeftParenthesis,
  // The `Right Parenthesis`/ `)` / U+0029.
  Arcadia_Mil_TokenType_RightParenthesis,


  // A name.
  Arcadia_Mil_TokenType_Name,

  // A boolean literal.
  // "true" or "false".
  Arcadia_Mil_TokenType_BooleanLiteral,
  // A real number literal.
  Arcadia_Mil_TokenType_RealLiteral,
  // An integer literal.
  Arcadia_Mil_TokenType_IntegerLiteral,
  // A string literal.
  Arcadia_Mil_TokenType_StringLiteral,
  // A void literal.
  // "void".
  Arcadia_Mil_TokenType_VoidLiteral,

  // "class"
  Arcadia_Mil_TokenType_Class,
  // "constructor"
  Arcadia_Mil_TokenType_Constructor,
  // "extends"
  Arcadia_Mil_TokenType_Extends,
  // "implements"
  Arcadia_Mil_TokenType_Implements,
  // "procedure"
  Arcadia_Mil_TokenType_Procedure,
  // "method"
  Arcadia_Mil_TokenType_Method,

  // "invoke"
  Arcadia_Mil_TokenType_Invoke,

  // "native"
  Arcadia_Mil_TokenType_Native,
  // "entry"
  Arcadia_Mil_TokenType_Entry,
  // "return"
  Arcadia_Mil_TokenType_Return,
  // "variable"
  Arcadia_Mil_TokenType_Variable,

  // "jump"
  Arcadia_Mil_TokenType_Jump,
  // "jumpIfTrue"
  Arcadia_Mil_TokenType_JumpIfTrue,
  // "jumpIfFalse"
  Arcadia_Mil_TokenType_JumpIfFalse,

  // "raise"
  Arcadia_Mil_TokenType_Raise,

  // "add" (arithmetic operations)
  Arcadia_Mil_TokenType_Add,
  // "subtract" (arithmetic operations)
  Arcadia_Mil_TokenType_Subtract,
  // "multiply" (arithmetic operations)
  Arcadia_Mil_TokenType_Multiply,
  // "divide" (arithmetic operations)
  Arcadia_Mil_TokenType_Divide,

  // "isEqualTo" (relational operation)
  Arcadia_Mil_TokenType_IsEqualTo,
  // "isNotEqualTo" (relational operation),
  Arcadia_Mil_TokenType_IsNotEqualTo,
  // "isLowerThan" (relational operation)
  Arcadia_Mil_TokenType_IsLowerThan,
  // "isLowerThanOrEqualTo" (relational operation)
  Arcadia_Mil_TokenType_IsLowerThanOrEqualTo,
  // "isGreaterThan" (relational operation)
  Arcadia_Mil_TokenType_IsGreaterThan,
  // "isGreaterThanOrEqualTo" (relational operation)
  Arcadia_Mil_TokenType_IsGreaterThanOrEqualTo,

  // "negate" (arithmetic operations/logical operations)
  Arcadia_Mil_TokenType_Negate,

  // "not" (boolean operations)
  Arcadia_Mil_TokenType_Not,
  // "and" (boolean operations)
  Arcadia_Mil_TokenType_And,
  // "or" (boolean operations)
  Arcadia_Mil_TokenType_Or,

  // "concatenate" (list operations)
  Arcadia_Mil_TokenType_Concatenate,

  /// A single line comment.
  Arcadia_Mil_TokenType_SingleLineComment,
  /// A multi line comment.
  Arcadia_Mil_TokenType_MultiLineComment,

} Arcadia_Mil_TokenType;

#endif // ARCADIA_MIL_TOKENTYPE_H_INCLUDED
