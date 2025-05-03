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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_TOKENTYPE_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_TOKENTYPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType("Arcadia.DataDefinitionLanguage.TokenType", Arcadia_DataDefinitionLanguage_TokenType);

typedef enum Arcadia_DataDefinitionLanguage_TokenType {

  // Start of input.
  Arcadia_DataDefinitionLanguage_TokenType_StartOfInput,
  // End of input.
  Arcadia_DataDefinitionLanguage_TokenType_EndOfInput,

  // LF, CR or CR LF
  Arcadia_DataDefinitionLanguage_TokenType_LineTerminator,
  // Any non-empty sequence of the symbols tabulator and whitespace.
  Arcadia_DataDefinitionLanguage_TokenType_WhiteSpace,

  // The `Equals Sign` / `=`  / U+003D.
  //Arcadia_Mil_TokenType_EqualsSign,
  // The `Colon` / `:` / U+003A.
  Arcadia_DataDefinitionLanguage_TokenType_Colon,
  // The `Comma` / `,` / U+002C.
  Arcadia_DataDefinitionLanguage_TokenType_Comma,
  // The `Left Curly Bracket` / `{` / U+007B.
  Arcadia_DataDefinitionLanguage_TokenType_LeftCurlyBracket,
  // The `Right Curly Bracket`/ `}` / U+007D.
  Arcadia_DataDefinitionLanguage_TokenType_RightCurlyBracket,
  // The `Left Square Bracket` / `[` / U+005B.
  Arcadia_DataDefinitionLanguage_TokenType_LeftSquareBracket,
  // The `Right Square Bracket`/ `]` / U+005D.
  Arcadia_DataDefinitionLanguage_TokenType_RightSquareBracket,


  // A name.
  Arcadia_DataDefinitionLanguage_TokenType_Name,

  // A boolean literal.
  // "true" or "false".
  Arcadia_DataDefinitionLanguage_TokenType_BooleanLiteral,
  // A real number literal.
  Arcadia_DataDefinitionLanguage_TokenType_RealLiteral,
  // An integer literal.
  Arcadia_DataDefinitionLanguage_TokenType_IntegerLiteral,
  // A string literal.
  Arcadia_DataDefinitionLanguage_TokenType_StringLiteral,
  // A void literal.
  // "void".
  Arcadia_DataDefinitionLanguage_TokenType_VoidLiteral,

  /// A single line comment.
  Arcadia_DataDefinitionLanguage_TokenType_SingleLineComment,
  /// A multi line comment.
  Arcadia_DataDefinitionLanguage_TokenType_MultiLineComment,

} Arcadia_DataDefinitionLanguage_TokenType;

#endif // ARCADIA_DATADEFINITIONLANGUAGE_TOKENTYPE_H_INCLUDED
