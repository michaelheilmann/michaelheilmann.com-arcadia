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

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Context", Arcadia_Visuals_Implementation_OpenGL4_Context,
                          Arcadia_Visuals_Context);

struct Arcadia_Visuals_Implementation_OpenGL4_Context {
  Arcadia_Visuals_Context parent;

  // Default is 1.
  Arcadia_Real32Value clearDepth;

  struct {
    // Default is 193.
    Arcadia_Natural8Value red;
    // Default is 216.
    Arcadia_Natural8Value green;
    // Default is 195.
    Arcadia_Natural8Value blue;
    // Default is 255.
    Arcadia_Natural8Value alpha;
  } clearColor;

  struct {

    // Default is 0.
    Arcadia_Real32Value left;
    // Default is 0.
    Arcadia_Real32Value bottom;
    // Default is 1.
    Arcadia_Real32Value right;
    // Default is 1.
    Arcadia_Real32Value top;

  } viewport;

  // If this context is attached to a render target.
  // Default is Arcadia_BooleanValue_False.
  Arcadia_BooleanValue hasRenderTarget;

  struct {

    // If attached, the width of the render target.
    // Default is 320.
    Arcadia_Natural32Value width;

    // If attached, the height of the render target.
    // Default is 240.
    Arcadia_Natural32Value height;

  } renderTargetSize;
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
    Arcadia_Visuals_Window* window
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CONTEXT_H_INCLUDED
