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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Context", Arcadia_Visuals_Implementation_OpenGL4_Context,
                          Arcadia_Visuals_Context);

struct Arcadia_Visuals_Implementation_OpenGL4_Context {
  Arcadia_Visuals_Context parent;
};

Arcadia_Visuals_Implementation_OpenGL4_Context*
Arcadia_Visuals_Implementation_OpenGL4_Context_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Implementation_OpenGL4_Context_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Window* window
  );

// "invalidate" all resources in the context.
// Effectively, this iterates over all resources and set the OpenGL resource IDs of each object to 0
void
Arcadia_Visuals_Implementation_OpenGL4_Context_invalidateAll
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CONTEXT_H_INCLUDED
