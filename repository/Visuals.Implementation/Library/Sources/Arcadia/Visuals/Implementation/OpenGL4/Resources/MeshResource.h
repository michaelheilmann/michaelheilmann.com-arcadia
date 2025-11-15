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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MESHRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MESHRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/MeshResource.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h> // For GLuint.
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h> // For GLuint.
#else
  #error("environment not (yet) supported")
#endif

typedef struct Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource;
typedef struct Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource;
typedef struct Arcadia_Visuals_Implementation_OpenGL4_ProgramResource Arcadia_Visuals_Implementation_OpenGL4_ProgramResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.MeshResource", Arcadia_Visuals_Implementation_OpenGL4_MeshResource,
                          u8"Arcadia.Visuals.Implementation.MeshResource")

struct Arcadia_Visuals_Implementation_OpenGL4_MeshResource {
  Arcadia_Visuals_Implementation_MeshResource _parent;
  Arcadia_Natural8Value dirty;
  Arcadia_Math_Matrix4Real32* localToWorldMatrix;
  Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource* meshConstantBuffer;
  Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBuffer;
  Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* program;
};

Arcadia_Visuals_Implementation_OpenGL4_MeshResource*
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBuffer,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* program
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MESHRESOURCE_H_INCLUDED
