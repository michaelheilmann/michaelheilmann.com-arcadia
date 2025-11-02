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

#if !defined(ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED

#include "Arcadia/Visuals/Scene/Node.h"
typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext;
typedef struct Arcadia_Visuals_Implementation_MeshResource Arcadia_Visuals_Implementation_MeshResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_MeshNode {
  Arcadia_Visuals_Scene_Node _parent;
  // The base color of this mesh.
  // The default value is (1, 1, 1, 1).
  struct {
    Arcadia_Real32Value red, green, blue, alpha;
  } baseColor;
  // The number of vertices of this mesh.
  // The default is 3.
  Arcadia_SizeValue numberOfVertices;
  // The xy or xyz postions of the vertices of this mesh.
  // The default value is [(-0.5, -0.5, 0.0), (0.5, -0.5, 0.0), (0.0, 0.5, 0.0)].
  void* vertexPositions;
  // The rgb or rgba color of the vertices of this mesh.
  // The default value is [(1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)].
  void* vertexColors;
};

#endif // ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED
