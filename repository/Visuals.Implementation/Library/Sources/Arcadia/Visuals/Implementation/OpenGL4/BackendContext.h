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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.h"

/// Base of all OpenGL4 backend contexts.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.BackendContext", Arcadia_Visuals_Implementation_OpenGL4_BackendContext,
                          u8"Arcadia.Visuals.Implementation.BackendContext");

struct Arcadia_Visuals_Implementation_OpenGL4_BackendContextDispatch {
  Arcadia_Visuals_Implementation_BackendContextDispatch _parent;

  _Arcadia_Visuals_Implementation_OpenGL4_Functions*
  (*getFunctions)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
    );
};

struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext {
  Arcadia_Visuals_Implementation_BackendContext _parent;

  // The list of resources.
  Arcadia_List* resources;
};

_Arcadia_Visuals_Implementation_OpenGL4_Functions*
Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_BACKENDCONTEXT_H_INCLUDED
