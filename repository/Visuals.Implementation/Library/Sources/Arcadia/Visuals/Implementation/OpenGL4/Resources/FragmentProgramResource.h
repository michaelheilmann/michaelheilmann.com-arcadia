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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAGMENTPROGRAMRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAGMENTPROGRAMRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendIncludes.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.FragmentProgramResource", Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource,
                          u8"Arcadia.Visuals.Implementation.FragmentProgramResource");

struct Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResourceDispatch {
  Arcadia_Visuals_Implementation_FragmentProgramResourceDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource {
  Arcadia_Visuals_Implementation_FragmentProgramResource _parent;
  GLuint id;
};

Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource*
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_VPL_Program* program
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAGMENTPROGRAMRESOURCE_H_INCLUDED
