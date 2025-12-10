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

#if !defined(ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Scene/Node.h"
#include "Arcadia/Visuals/VertexDescriptor.h"
#include "Arcadia/Visuals/Texture.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_MeshNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
};

struct Arcadia_Visuals_Scene_MeshNode {
  Arcadia_Visuals_Scene_Node _parent;
  /// A pointer to the vertex descriptor.
  Arcadia_Visuals_VertexDescriptor* vertexDescriptor;
  // The base color of this mesh.
  // The default value is (1, 1, 1, 1).
  struct {
    Arcadia_Real32Value red, green, blue, alpha;
  } baseColor;
  // The number of vertices of this mesh.
  // The default is 3.
  Arcadia_SizeValue numberOfVertices;
  // Pointers to the positions of the vertices of this mesh.
  // The default value is [(-0.5, -0.5, 0.0), (0.5, -0.5, 0.0), (0.0, 0.5, 0.0)].
  void* vertexPositions;
  // Pointers to the ambient colors of the vertices of this mesh.
  // The default value is [(1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)].
  void* vertexColors;
};

void
Arcadia_Visuals_Scene_MeshNode_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_SizeValue* numberOfVertices
  );

void
Arcadia_Visuals_Scene_MeshNode_setBaseColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

void
Arcadia_Visuals_Scene_MeshNode_getBaseColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

#endif // ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED
