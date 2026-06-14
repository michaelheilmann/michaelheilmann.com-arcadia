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

#if !defined(ARCADIA_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED

#include "Arcadia.Tools.TemplateEngine.Library/Parser/Parser.h"
#include "Arcadia.Tools.TemplateEngine.Library/Scanner/Scanner.h"
#include "Arcadia/Ring2/Include.h"
typedef struct Context Context;
typedef struct Environment Environment;

// The read-evaluate procedure parses a file into a tree
// @code
// file : (text | directive)*
// @endcode
// It then iterates over the file's tree children from left to right
// text trees is directly written to an output buffer
// directive trees directives are evaluated.
Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.FileContext", FileContext,
                          u8"Arcadia.Object");

struct FileContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct FileContext {
  Arcadia_Object _parent;

  /// The underlaying context.
  Context* context;
  /// The path to the including file.
  Arcadia_FilePath* includingFilePath;
  /// The path to the included file.
  Arcadia_FilePath* includedFilePath;

  /// The Bytes of this file.
  Arcadia_ByteArray* fileBytes;

  /// Unicode decoder for the included file.
  Arcadia_UnicodeCodePointReader* reader;
  /// The environment.
  Environment* environment;

  /// The directives parser.
  Arcadia_TemplateEngine_Parser* parser;
  Arcadia_TemplateEngine_Scanner* scanner;

};

FileContext*
FileContext_create
  (
    Arcadia_Thread* thread,
    Context* context,
    Environment* environment,
    Arcadia_FilePath* includingFilePath,
    Arcadia_FilePath* includedFilePath
  );

void
FileContext_execute
  (
    Arcadia_Thread* thread,
    FileContext* context
  );

#endif // ARCADIA_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED
