// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-09

#if !defined(TOOLS_TEMPLATEENGINE_CONTEXT_H_INCLUDED)
#define TOOLS_TEMPLATEENGINE_CONTEXT_H_INCLUDED

#include "R.h"

Rex_declareObjectType(u8"Tools.TemplateEngine.Context", Context, u8"R.Object");

struct Context {
  R_Object _parent;
  R_Utf8Writer* target;
  R_ByteBuffer* targetBuffer;

  R_Utf8Writer* temporary;
  R_ByteBuffer* temporaryBuffer;

  R_Stack* stack;
  R_List* files;
};

Context*
Context_create
  (
    Arcadia_Process* process
  );

void
Context_onRun
  (
    Arcadia_Process* process,
    Context* context
  );

#endif // TOOLS_TEMPLATEENGINE_CONTEXT_H_INCLUDED
