// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_TEMPLATEENGINE_SCANNER_WORDTYPE_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_SCANNER_WORDTYPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType(u8"Arcadia.TemplateEngine.WordType", Arcadia_TemplateEngine_WordType);

enum Arcadia_TemplateEngine_WordType {
  Arcadia_TemplateEngine_WordType_StartOfInput,
  Arcadia_TemplateEngine_WordType_EndOfInput,
  Arcadia_TemplateEngine_WordType_Error,

  Arcadia_TemplateEngine_WordType_AtLiteral,
  Arcadia_TemplateEngine_WordType_Name,
  Arcadia_TemplateEngine_WordType_StringLiteral,
  
  Arcadia_TemplateEngine_WordType_Comma,

  Arcadia_TemplateEngine_WordType_LeftCurlyBracket,
  Arcadia_TemplateEngine_WordType_LeftParenthesis,
  
  Arcadia_TemplateEngine_WordType_RightCurlyBracket,
  Arcadia_TemplateEngine_WordType_RightParenthesis,

  Arcadia_TemplateEngine_WordType_StartOfDirective,
  Arcadia_TemplateEngine_WordType_Text,
  
};

#endif // ARCADIA_TEMPLATEENGINE_SCANNER_WORDTYPE_H_INCLUDED
