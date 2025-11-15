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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHCONTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_MeshContextResource Arcadia_Visuals_Implementation_MeshContextResource;

// This represents state common to all meshes.
// It is set by a) the viewport and b) the camera and passed to each mesh.
// It contains an up-to-date constant buffer which a mesh shall bind to the "viewer" block.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Scene.MeshContext", Arcadia_Visuals_Implementation_Scene_MeshContext,
                          u8"Arcadia.Visuals.Scene.MeshContext");

struct Arcadia_Visuals_Implementation_Scene_MeshContext {
  Arcadia_Visuals_Scene_MeshContext parent;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource;
};

/// @brief Create a mesh context.
/// @return A pointer to the mesh context.
Arcadia_Visuals_Implementation_Scene_MeshContext*
Arcadia_Visuals_Implementation_Scene_MeshContext_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHCONTEXT_H_INCLUDED
