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

#if !defined(ARCADIA_TEMPLATEENGINE_PARSER_PARSER_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_PARSER_PARSER_H_INCLUDED

#include "Arcadia.Tools.TemplateEngine.Library/Scanner/Scanner.h"
#include "Arcadia.Tools.TemplateEngine.Library/Parser/Tree.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Parser", Arcadia_TemplateEngine_Parser,
                          u8"Arcadia.Languages.Parser");

struct Arcadia_TemplateEngine_ParserDispatch {
  Arcadia_Languages_ParserDispatch _parent;
};

struct Arcadia_TemplateEngine_Parser {
  Arcadia_Languages_Parser _parent;
  /// The scanner.
  Arcadia_TemplateEngine_Scanner* scanner;
};

Arcadia_TemplateEngine_Parser*
Arcadia_TemplateEngine_Parser_create
  (
    Arcadia_Thread* thread,
	  Arcadia_String* file,
	  Arcadia_Natural64Value line,
    Arcadia_UnicodeCodePointReader* reader
  );

void
Arcadia_TemplateEngine_Parser_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_TemplateEngine_Parser* self,
    Arcadia_String* file,
    Arcadia_Natural64Value line
  );

#endif // ARCADIA_TEMPLATEENGINE_PARSER_PARSER_H_INCLUDED
