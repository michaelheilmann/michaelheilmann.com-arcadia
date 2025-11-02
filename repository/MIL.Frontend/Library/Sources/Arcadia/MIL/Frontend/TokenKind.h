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

#if !defined(ARCADIA_MIL_FRONTEND_TOKENKIND_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_TOKENKIND_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType("Arcadia.MIL.TokenKind", Arcadia_MIL_TokenKind);

enum Arcadia_MIL_TokenKind {

  // Start of input.
  Arcadia_MIL_TokenKind_StartOfInput,
  // End of input.
  Arcadia_MIL_TokenKind_EndOfInput,

  // LF, CR or CR LF
  Arcadia_MIL_TokenKind_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  Arcadia_MIL_TokenKind_WhiteSpaces,

  // The `Equals Sign` / `=`  / U+003D.
  Arcadia_MIL_TokenKind_EqualsSign,
  // The `Colon` / `:` / U+003A.
  Arcadia_MIL_TokenKind_Colon,
  // The `Comma` / `,` / U+002C.
  Arcadia_MIL_TokenKind_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  Arcadia_MIL_TokenKind_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  Arcadia_MIL_TokenKind_RightCurlyBracket,
  // The `Left Parenthesis` / `(` / U+0028.
  Arcadia_MIL_TokenKind_LeftParenthesis,
  // The `Right Parenthesis`/ `)` / U+0029.
  Arcadia_MIL_TokenKind_RightParenthesis,


  // A name.
  Arcadia_MIL_TokenKind_Name,
  // A register.
  Arcadia_MIL_TokenKind_Register,

  // A boolean literal.
  // "true" or "false".
  Arcadia_MIL_TokenKind_BooleanLiteral,
  // A real number literal.
  Arcadia_MIL_TokenKind_RealLiteral,
  // An integer literal.
  Arcadia_MIL_TokenKind_IntegerLiteral,
  // A string literal.
  Arcadia_MIL_TokenKind_StringLiteral,
  // A void literal.
  // "void".
  Arcadia_MIL_TokenKind_VoidLiteral,

  // "class"
  Arcadia_MIL_TokenKind_Class,
  // "constructor"
  Arcadia_MIL_TokenKind_Constructor,
  // "extends"
  Arcadia_MIL_TokenKind_Extends,
  // "implements"
  Arcadia_MIL_TokenKind_Implements,
  // "procedure"
  Arcadia_MIL_TokenKind_Procedure,
  // "method"
  Arcadia_MIL_TokenKind_Method,

  // "invoke"
  Arcadia_MIL_TokenKind_Invoke,

  // "native"
  Arcadia_MIL_TokenKind_Native,
  // "entry"
  Arcadia_MIL_TokenKind_Entry,
  // "return"
  Arcadia_MIL_TokenKind_Return,
  // "variable"
  Arcadia_MIL_TokenKind_Variable,

  // "jump"
  Arcadia_MIL_TokenKind_Jump,
  // "jumpIfTrue"
  Arcadia_MIL_TokenKind_JumpIfTrue,
  // "jumpIfFalse"
  Arcadia_MIL_TokenKind_JumpIfFalse,

  // "raise"
  Arcadia_MIL_TokenKind_Raise,

  // "add" (arithmetic operations)
  Arcadia_MIL_TokenKind_Add,
  // "subtract" (arithmetic operations)
  Arcadia_MIL_TokenKind_Subtract,
  // "multiply" (arithmetic operations)
  Arcadia_MIL_TokenKind_Multiply,
  // "divide" (arithmetic operations)
  Arcadia_MIL_TokenKind_Divide,

  // "isEqualTo" (relational operation)
  Arcadia_MIL_TokenKind_IsEqualTo,
  // "isNotEqualTo" (relational operation),
  Arcadia_MIL_TokenKind_IsNotEqualTo,
  // "isLowerThan" (relational operation)
  Arcadia_MIL_TokenKind_IsLowerThan,
  // "isLowerThanOrEqualTo" (relational operation)
  Arcadia_MIL_TokenKind_IsLowerThanOrEqualTo,
  // "isGreaterThan" (relational operation)
  Arcadia_MIL_TokenKind_IsGreaterThan,
  // "isGreaterThanOrEqualTo" (relational operation)
  Arcadia_MIL_TokenKind_IsGreaterThanOrEqualTo,

  // "negate" (arithmetic operations/logical operations)
  Arcadia_MIL_TokenKind_Negate,

  // "not" (boolean operations)
  Arcadia_MIL_TokenKind_Not,
  // "and" (boolean operations)
  Arcadia_MIL_TokenKind_And,
  // "or" (boolean operations)
  Arcadia_MIL_TokenKind_Or,

  // "concatenate" (list operations)
  Arcadia_MIL_TokenKind_Concatenate,

  // "set"
  Arcadia_MIL_TokenKind_Set,

  /// A single line comment.
  Arcadia_MIL_TokenKind_SingleLineComment,
  /// A multi line comment.
  Arcadia_MIL_TokenKind_MultiLineComment,

};

#endif // ARCADIA_MIL_FRONTEND_TOKENKIND_H_INCLUDED
