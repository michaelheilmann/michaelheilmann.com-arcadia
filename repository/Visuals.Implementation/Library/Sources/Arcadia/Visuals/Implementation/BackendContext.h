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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/MeshContextResource.h"
#include "Arcadia/Visuals/Implementation/Resources/MeshResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ViewportResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexProgramResource.h"

/// Base of all OpenGL4 backend contexts.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.BackendContext", Arcadia_Visuals_Implementation_BackendContext,
                          u8"Arcadia.Visuals.BackendContext")

struct Arcadia_Visuals_Implementation_BackendContext {
  Arcadia_Visuals_BackendContext _parent;

  Arcadia_Visuals_Implementation_ConstantBufferResource*
  (*createConstantBufferResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_FragmentProgramResource*
  (*createFragmentProgramResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_MeshContextResource*
  (*createMeshContextResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_MeshResource*
  (*createMeshResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer,
      Arcadia_Visuals_Implementation_ProgramResource* program
    );

  Arcadia_Visuals_Implementation_ProgramResource*
  (*createProgramResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgram,
      Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgram
    );

  Arcadia_Visuals_Implementation_VertexBufferResource*
  (*createVertexBufferResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_VertexProgramResource*
  (*createVertexProgramResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_ViewportResource*
  (*createViewportResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );
};

Arcadia_Visuals_Implementation_ConstantBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a fragment program resource. The initial reference count of that resource is 0, hence it'd be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_FragmentProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createFragmentProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

Arcadia_Visuals_Implementation_MeshContextResource*
Arcadia_Visuals_Implementation_BackendContext_createMeshContextResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

Arcadia_Visuals_Implementation_MeshResource*
Arcadia_Visuals_Implementation_BackendContext_createMeshResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer,
    Arcadia_Visuals_Implementation_ProgramResource* program
  );

// Create a program resource. The initial reference count of that resource is 0, hence it'd be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_ProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgram,
    Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgram
  );

// Create a vertex buffer resource. The initial reference count of that resource is 0, hence it'd be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_VertexBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a vertex program resource. The initial reference count of that resource is 0, hence it'd be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_VertexProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a viewport resource. The initial reference count of that resource is 0, hence it'd be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_ViewportResource*
Arcadia_Visuals_Implementation_BackendContext_createViewportResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED
