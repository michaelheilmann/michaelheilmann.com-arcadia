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
#include "Arcadia/Visuals/Scene/MaterialNode.h"

// A "mesh node" consists of a
// - an ambient base color: The ambient color used for each vertices of the vertices provide no color data
// - a vertex descriptor: Must be of the form [xyz/position, rgba/ambient, uv/ambient]. Describes the data in the vertex buffer.
// - a vertex buffer: The vertex data. Either of the form [xyz/position] or [xyz/position, rgba/ambient].
// - a material
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_MeshNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
};

struct Arcadia_Visuals_Scene_MeshNode {
  Arcadia_Visuals_Scene_Node _parent;
  
  /// The mesh definition.
  Arcadia_ADL_MeshDefinition* source;
  /// A pointer to the vertex descriptor.
  Arcadia_Visuals_VertexDescriptor* vertexDescriptor;
  // The ambient color of this mesh.
  Arcadia_Math_Color4Real32* ambientColor;
  /// The number of vertices of this mesh.
  Arcadia_SizeValue numberOfVertices;
  /// Pointers to the positions of the vertices of this mesh.
  void* vertices;
  
  Arcadia_Visuals_Scene_MaterialNode* material;
};

void
Arcadia_Visuals_Scene_MeshNode_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_SizeValue* numberOfVertices
  );

void
Arcadia_Visuals_Scene_MeshNode_setAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_Math_Color4Real32* baseColor
  );

Arcadia_Math_Color4Real32*
Arcadia_Visuals_Scene_MeshNode_getAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

#endif // ARCADIA_VISUALS_SCENE_MESHNODE_H_INCLUDED
