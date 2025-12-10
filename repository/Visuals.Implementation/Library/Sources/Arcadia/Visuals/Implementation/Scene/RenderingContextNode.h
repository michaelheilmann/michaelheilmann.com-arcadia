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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_RenderingContextResource Arcadia_Visuals_Implementation_RenderingContextResource;

// This represents the mutable state of a rendering.
// When nodes are visited, then the state of this node is continously updated.
// Updates values are e.g., the viewport rectangle, the view matrix, the projection matrix, etc.
//
// In the backend this is usually implemented by a constant buffer with variables for the viewport rectangle, the view matrix, the projection matrix, etc.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Scene.RenderingContextNode", Arcadia_Visuals_Implementation_Scene_RenderingContextNode,
                          u8"Arcadia.Visuals.Scene.RenderingContextNode");

struct Arcadia_Visuals_Implementation_Scene_RenderingContextNodeDispatch {
  Arcadia_Visuals_Scene_RenderingContextNodeDispatch parent;
};

struct Arcadia_Visuals_Implementation_Scene_RenderingContextNode {
  Arcadia_Visuals_Scene_RenderingContextNode parent;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextResource;
};

/// @brief Create a rendering context mode.
/// @return A pointer to the rendering context node.
Arcadia_Visuals_Implementation_Scene_RenderingContextNode*
Arcadia_Visuals_Implementation_Scene_RenderingContextNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED
