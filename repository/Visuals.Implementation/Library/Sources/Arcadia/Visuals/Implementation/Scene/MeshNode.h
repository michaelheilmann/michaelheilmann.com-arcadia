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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHNODE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_MeshResource Arcadia_Visuals_Implementation_MeshResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Scene.MeshNode", Arcadia_Visuals_Implementation_Scene_MeshNode,
                          u8"Arcadia.Visuals.Scene.MeshNode");

struct Arcadia_Visuals_Implementation_Scene_MeshNodeDispatch {
  Arcadia_Visuals_Scene_MeshNodeDispatch _parent;
};

struct Arcadia_Visuals_Implementation_Scene_MeshNode {
  Arcadia_Visuals_Scene_MeshNode _parent;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_MeshResource* meshResource;
};

Arcadia_Visuals_Implementation_Scene_MeshNode*
Arcadia_Visuals_Implementation_Scene_MeshNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_SCENE_MESHNODE_H_INCLUDED
