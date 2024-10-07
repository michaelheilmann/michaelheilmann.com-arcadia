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
  // A string literal.
  Cil_TokenType_StringLiteral,
  // The assignment operator
  Cil_TokenType_Assign,
  // A name.
  Cil_TokenType_Name,
  // A number literal.
  Cil_TokenType_NumberLiteral,

  /// "add"
  Cil_TokenType_Add,
  /// "subtract"
  Cil_TokenType_Subtract,
  /// "multiply"
  Cil_TokenType_Multiply,
  /// "divide"
  Cil_TokenType_Divide,

  /// "negate"
  Cil_TokenType_Negate,
  /// "not"
  Cil_TokenType_Not,

  /// "concatenate"
  Cil_TokenType_concatenate,

  /// A single line comment.
  Cil_TokenType_SingleLineComment,
  /// A multi line comment.
  Cil_TokenType_MultiLineComment,

} Cil_TokenType;

#endif // CIL_TOKENTYPE_H_INCLUDED
