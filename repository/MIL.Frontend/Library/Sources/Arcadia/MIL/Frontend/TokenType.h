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

#if !defined(ARCADIA_MIL_FRONTEND_TOKENTYPE_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_TOKENTYPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType("Arcadia.MIL.TokenType", Arcadia_MIL_TokenType);

enum Arcadia_MIL_TokenType {

  // Start of input.
  Arcadia_MIL_TokenType_StartOfInput,
  // End of input.
  Arcadia_MIL_TokenType_EndOfInput,

  // LF, CR or CR LF
  Arcadia_MIL_TokenType_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  Arcadia_MIL_TokenType_WhiteSpaces,

  // The `Equals Sign` / `=`  / U+003D.
  Arcadia_MIL_TokenType_EqualsSign,
  // The `Colon` / `:` / U+003A.
  Arcadia_MIL_TokenType_Colon,
  // The `Comma` / `,` / U+002C.
  Arcadia_MIL_TokenType_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  Arcadia_MIL_TokenType_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  Arcadia_MIL_TokenType_RightCurlyBracket,
  // The `Left Parenthesis` / `(` / U+0028.
  Arcadia_MIL_TokenType_LeftParenthesis,
  // The `Right Parenthesis`/ `)` / U+0029.
  Arcadia_MIL_TokenType_RightParenthesis,


  // A name.
  Arcadia_MIL_TokenType_Name,
  // A register.
  Arcadia_MIL_TokenType_Register,

  // A boolean literal.
  // "true" or "false".
  Arcadia_MIL_TokenType_BooleanLiteral,
  // A real number literal.
  Arcadia_MIL_TokenType_RealLiteral,
  // An integer literal.
  Arcadia_MIL_TokenType_IntegerLiteral,
  // A string literal.
  Arcadia_MIL_TokenType_StringLiteral,
  // A void literal.
  // "void".
  Arcadia_MIL_TokenType_VoidLiteral,

  // "class"
  Arcadia_MIL_TokenType_Class,
  // "constructor"
  Arcadia_MIL_TokenType_Constructor,
  // "extends"
  Arcadia_MIL_TokenType_Extends,
  // "implements"
  Arcadia_MIL_TokenType_Implements,
  // "procedure"
  Arcadia_MIL_TokenType_Procedure,
  // "method"
  Arcadia_MIL_TokenType_Method,

  // "invoke"
  Arcadia_MIL_TokenType_Invoke,

  // "native"
  Arcadia_MIL_TokenType_Native,
  // "entry"
  Arcadia_MIL_TokenType_Entry,
  // "return"
  Arcadia_MIL_TokenType_Return,
  // "variable"
  Arcadia_MIL_TokenType_Variable,

  // "jump"
  Arcadia_MIL_TokenType_Jump,
  // "jumpIfTrue"
  Arcadia_MIL_TokenType_JumpIfTrue,
  // "jumpIfFalse"
  Arcadia_MIL_TokenType_JumpIfFalse,

  // "raise"
  Arcadia_MIL_TokenType_Raise,

  // "add" (arithmetic operations)
  Arcadia_MIL_TokenType_Add,
  // "subtract" (arithmetic operations)
  Arcadia_MIL_TokenType_Subtract,
  // "multiply" (arithmetic operations)
  Arcadia_MIL_TokenType_Multiply,
  // "divide" (arithmetic operations)
  Arcadia_MIL_TokenType_Divide,

  // "isEqualTo" (relational operation)
  Arcadia_MIL_TokenType_IsEqualTo,
  // "isNotEqualTo" (relational operation),
  Arcadia_MIL_TokenType_IsNotEqualTo,
  // "isLowerThan" (relational operation)
  Arcadia_MIL_TokenType_IsLowerThan,
  // "isLowerThanOrEqualTo" (relational operation)
  Arcadia_MIL_TokenType_IsLowerThanOrEqualTo,
  // "isGreaterThan" (relational operation)
  Arcadia_MIL_TokenType_IsGreaterThan,
  // "isGreaterThanOrEqualTo" (relational operation)
  Arcadia_MIL_TokenType_IsGreaterThanOrEqualTo,

  // "negate" (arithmetic operations/logical operations)
  Arcadia_MIL_TokenType_Negate,

  // "not" (boolean operations)
  Arcadia_MIL_TokenType_Not,
  // "and" (boolean operations)
  Arcadia_MIL_TokenType_And,
  // "or" (boolean operations)
  Arcadia_MIL_TokenType_Or,

  // "concatenate" (list operations)
  Arcadia_MIL_TokenType_Concatenate,

  // "set"
  Arcadia_MIL_TokenType_Set,

  /// A single line comment.
  Arcadia_MIL_TokenType_SingleLineComment,
  /// A multi line comment.
  Arcadia_MIL_TokenType_MultiLineComment,

};

#endif // ARCADIA_MIL_FRONTEND_TOKENTYPE_H_INCLUDED
