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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Engine/Include.h"

#include "Arcadia/Visuals/Implementation/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/FrameBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/EnterPassResource.h"
#include "Arcadia/Visuals/Implementation/Resources/MaterialResource.h"
#include "Arcadia/Visuals/Implementation/Resources/MeshResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ModelResource.h"
#include "Arcadia/Visuals/Implementation/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h"

/// Base of all OpenGL4 backend contexts.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.BackendContext", Arcadia_Visuals_Implementation_BackendContext,
                          u8"Arcadia.Engine.Visuals.BackendContext");

struct Arcadia_Visuals_Implementation_BackendContextDispatch {
  Arcadia_Engine_Visuals_BackendContextDispatch _parent;

  Arcadia_Visuals_Implementation_ConstantBufferResource*
  (*createConstantBufferResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_FrameBufferResource*
  (*createFrameBufferResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_EnterPassResource*
  (*createEnterPassResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_MaterialResource*
  (*createMaterialResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource,
      Arcadia_Visuals_Implementation_TextureResource* ambientTexture,
      Arcadia_Visuals_Implementation_ProgramResource* program
    );

  Arcadia_Visuals_Implementation_MeshResource*
  (*createMeshResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer
    );

  Arcadia_Visuals_Implementation_ModelResource*
  (*createModelResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_Visuals_Implementation_MeshResource* mesh,
      Arcadia_Visuals_Implementation_MaterialResource* material
    );

  Arcadia_Visuals_Implementation_ProgramResource*
  (*createProgramResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self,
      Arcadia_VPL_Program* program
    );

  Arcadia_Visuals_Implementation_TextureResource*
  (*createTextureResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );

  Arcadia_Visuals_Implementation_VertexBufferResource*
  (*createVertexBufferResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_BackendContext* self
    );
};

struct Arcadia_Visuals_Implementation_BackendContext {
  Arcadia_Engine_Visuals_BackendContext _parent;
};

// Create a constant buffer resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_ConstantBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a frame buffer resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_FrameBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createFrameBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a rendering context resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_EnterPassResource*
Arcadia_Visuals_Implementation_BackendContext_createEnterPassResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a material resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_MaterialResource*
Arcadia_Visuals_Implementation_BackendContext_createMaterialResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource,
    Arcadia_Visuals_Implementation_TextureResource* ambientTexture,
    Arcadia_Visuals_Implementation_ProgramResource* program
  );

// Create a mesh resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_MeshResource*
Arcadia_Visuals_Implementation_BackendContext_createMeshResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer
  );

// Create a model resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_ModelResource*
Arcadia_Visuals_Implementation_BackendContext_createModelResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_MeshResource* mesh,
    Arcadia_Visuals_Implementation_MaterialResource* material
  );

// Create a program resource
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_ProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_VPL_Program* program
  );

// Create a texture resource
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_TextureResource*
Arcadia_Visuals_Implementation_BackendContext_createTextureResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

// Create a vertex buffer resource.
// The initial reference count of the created resource is @a 0, hence it would be destroyed at the next update of the backend.
Arcadia_Visuals_Implementation_VertexBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED
