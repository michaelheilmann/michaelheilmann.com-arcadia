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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MODELRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MODELRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/ModelResource.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h> // For GLuint.
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h> // For GLuint.
#else
  #error("environment not (yet) supported")
#endif

typedef struct Arcadia_Visuals_Implementation_OpenGL4_MeshResource Arcadia_Visuals_Implementation_OpenGL4_MeshResource;
typedef struct Arcadia_Visuals_Implementation_OpenGL4_MaterialResource Arcadia_Visuals_Implementation_OpenGL4_MaterialResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ModelResource", Arcadia_Visuals_Implementation_OpenGL4_ModelResource,
                          u8"Arcadia.Visuals.Implementation.ModelResource");

struct Arcadia_Visuals_Implementation_OpenGL4_ModelResourceDispatch {
  Arcadia_Visuals_Implementation_ModelResourceDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_ModelResource {
  Arcadia_Visuals_Implementation_ModelResource _parent;

  Arcadia_Visuals_Implementation_OpenGL4_MeshResource* mesh;
  Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* material;
};

Arcadia_Visuals_Implementation_OpenGL4_ModelResource*
Arcadia_Visuals_Implementation_OpenGL4_ModelResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* mesh,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* material
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_MODELRESOURCE_H_INCLUDED
