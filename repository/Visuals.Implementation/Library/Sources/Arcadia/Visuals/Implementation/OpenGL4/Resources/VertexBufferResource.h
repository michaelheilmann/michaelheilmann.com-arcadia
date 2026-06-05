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

#if !defined(ARCADIA_ENGINE_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendIncludes.h"
typedef struct Arcadia_Engine_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Engine_Visuals_Implementation_OpenGL4_BackendContext;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.VertexBufferResource", Arcadia_Engine_Visuals_Implementation_OpenGL4_VertexBufferResource,
                          u8"Arcadia.Visuals.Implementation.VertexBufferResource");

struct Arcadia_Engine_Visuals_Implementation_OpenGL4_VertexBufferResourceDispatch {
  Arcadia_Engine_Visuals_Implementation_VertexBufferResourceDispatch _parent;
};

struct Arcadia_Engine_Visuals_Implementation_OpenGL4_VertexBufferResource {
  Arcadia_Engine_Visuals_Implementation_VertexBufferResource _parent;

  GLuint vertexArrayID;
  GLuint vertexBufferID;
};

Arcadia_Engine_Visuals_Implementation_OpenGL4_VertexBufferResource*
Arcadia_Engine_Visuals_Implementation_OpenGL4_VertexBufferResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  );

#endif // ARCADIA_ENGINE_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED
