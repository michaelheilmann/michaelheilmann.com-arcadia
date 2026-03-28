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

#if !defined(ARCADIA_TOOLS_COMPILER_LIBRARY_CONTEXT_H_INCLUDED)
#define ARCADIA_TOOLS_COMPILER_LIBRARY_CONTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Environment Environment;

Arcadia_declareObjectType(u8"Arcadia.Tools.Compiler.Context", Context,
                          u8"Arcadia.Object");

struct ContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Context {
  Arcadia_Object _parent;
  Arcadia_List* files;
  Arcadia_Log* log;
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

#endif // ARCADIA_TOOLS_COMPILER_LIBRARY_CONTEXT_H_INCLUDED
