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

#if !defined(ARCADIA_VISUALS_CONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_CONTEXT_INCLUDE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

/// The singleton object of a type derived from Arcadia.Visuals.Context
/// is the representation of the retained mode renderer's state and the
/// interface to manipulate that state.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Context", Arcadia_Visuals_Context,
                          Arcadia_Object);

struct Arcadia_Visuals_Context {
  Arcadia_Object parent;

  void (*getClearColor)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*);
  void (*getClearDepth)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value*);
  void (*getViewport)(Arcadia_Thread* thread, Arcadia_Visuals_Context*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*, Arcadia_Real32Value*);

  void (*setClearColor)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value);
  void (*setClearDepth)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value);
  void (*setViewport)(Arcadia_Thread* thread, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value);
};

void
Arcadia_Visuals_Context_getClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

void
Arcadia_Visuals_Context_getClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* depth
  );

void
Arcadia_Visuals_Context_getViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  );

void
Arcadia_Visuals_Context_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

void
Arcadia_Visuals_Context_setClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value depth
  );

void
Arcadia_Visuals_Context_setViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

#endif // ARCADIA_VISUALS_CONTEXT_INCLUDE_H_INCLUDED
