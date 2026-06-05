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

#if !defined(ARCADIA_TEMPLATEENGINE_DIRECTIVES_PARSER_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_DIRECTIVES_PARSER_H_INCLUDED

#include "Arcadia.Tools.TemplateEngine.Library/Directives/Tree.h"
#include "Arcadia.Tools.TemplateEngine.Library/Directives/WordType.h"
#include "Arcadia.Tools.TemplateEngine.Library/Directives/Scanner.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Directives.Parser", Directives_Parser,
                          u8"Arcadia.Object");

struct Directives_ParserDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Directives_Parser {
  Arcadia_Object _parent;
  /// The scanner.
  Directives_Scanner* scanner;
};

Directives_Parser*
Directives_Parser_create
  (
    Arcadia_Thread* thread,
	  Arcadia_String* file,
	  Arcadia_Natural64Value line,
    Arcadia_UnicodeCodePointReader* reader
  );

void
Directives_Parser_setInput
  (
    Arcadia_Thread* thread,
	  Directives_Parser* self,
    Arcadia_String* file,
	  Arcadia_Natural64Value line,
    Arcadia_UnicodeCodePointReader* reader
  );

Directives_Tree*
Directives_Parser_run
  (
    Arcadia_Thread* thread,
    Directives_Parser* self
  );

#endif // ARCADIA_TEMPLATEENGINE_DIRECTIVES_PARSER_H_INCLUDED
