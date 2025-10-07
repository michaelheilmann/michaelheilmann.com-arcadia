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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CAMERA_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CAMERA_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Mesh", Arcadia_Visuals_Implementation_OpenGL4_Mesh,
                          u8"Arcadia.Object")

struct Arcadia_Visuals_Implementation_OpenGL4_Mesh {
  Arcadia_Visuals_System _parent;
  // Default is 1.
  Arcadia_Real32Value clearDepth;
  struct {
    // Default is 0.
    Arcadia_Natural8Value red;
    // Default is 0.
    Arcadia_Natural8Value green;
    // Default is 0.
    Arcadia_Natural8Value blue;
    // Default is 1.
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
};

Arcadia_Visuals_Implementation_OpenGL4_Mesh*
Arcadia_Visuals_Implementation_OpenGL4_Mesh_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self,
    Arcadia_Visuals_Window* window
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_CAMERA_H_INCLUDED
