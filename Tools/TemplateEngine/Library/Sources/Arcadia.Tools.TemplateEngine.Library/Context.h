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

#if !defined(ARCADIA_TEMPLATEENGINE_CONTEXT_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_CONTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Environment Environment;

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Context", Context,
                          u8"Arcadia.Object");

struct Context {
  Arcadia_Object _parent;
  Arcadia_UTF8Writer* target;
  Arcadia_ByteBuffer* targetBuffer;

  Arcadia_UTF8Writer* temporary;
  Arcadia_ByteBuffer* temporaryBuffer;

  Arcadia_FilePath* logFilePath;
  Arcadia_FilePath* dependenciesFilePath;


  Environment* environment;

  Arcadia_Stack* stack;
  /// The include graph.
  /// For example, if we start at X and X includes first A and second B.
  /// Then when processing B this list contains X, B.
  Arcadia_List* files;

  /// The set of all files processed so far.
  /// For example, if we start at X and X includes first A and second B.
  /// The wehn processing B this list contains X, A, B.
  Arcadia_List* allFiles;

  /// The console log.
  Arcadia_Log* consoleLog;
};

Context*
Context_create
  (
    Arcadia_Thread* thread
  );

void
Context_onRun
  (
    Arcadia_Thread* thread,
    Context* self
  );

#endif // ARCADIA_TEMPLATEENGINE_CONTEXT_H_INCLUDED
