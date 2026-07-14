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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_MESHNODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_MESHNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/Node.h"
#include "Arcadia/Engine/Visuals/Resources/ConstantBufferResource.h"
#include "Arcadia/Engine/Visuals/Resources/VertexBufferResource.h"
#include "Arcadia/ADL/Include.h"

// A "mesh node" consists of a
// - an ambient mesh color (required):
//   The ambient color used for each of the vertices if a) the vertices provide no color data and b) the material specifies the mesh as an ambient color source.
// - a vertex descriptor: Must be of the form [xyz/position, rgba/ambient, uv/ambient]. Describes the data in the vertex buffer.
// - a vertex buffer: The vertex data. Either of the form [xyz/position] or [xyz/position, rgba/ambient].
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.MeshNode", Arcadia_Engine_Visuals_MeshNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_Visuals_MeshNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;
};

struct Arcadia_Engine_Visuals_MeshNode {
  Arcadia_Engine_Visuals_Node _parent;

  /// The dirty flags.
  Arcadia_Natural8Value dirtyFlags;

  /// The mesh definition.
  Arcadia_ADL_MeshDefinition* source;
  // The ambient color of this mesh.
  Arcadia_Math_Color4Real32* ambientColor;
  // The vertex buffer of this mesh.
  Arcadia_Media_VertexBuffer* vertexBuffer;
  /// The backend context or a null pointer.
  Arcadia_Engine_Visuals_BackendContext* backendContext;
  /// The constant buffer of this mesh.
  /// This contains the mesh ambient color.
  Arcadia_Engine_Visuals_Implementation_ConstantBufferResource* constantBufferResource;
  /// The vertex buffer of this mesh.
  /// This contains the vertices of the mesh.
  Arcadia_Engine_Visuals_Implementation_VertexBufferResource* vertexBufferResource;
};

/// @brief Create a mesh node.
/// @param thread A pointer to this thread.
/// @param backendContext A pointer to the backend context or a null pointer.
/// @return A pointer to the mesh node.
Arcadia_Engine_Visuals_MeshNode*
Arcadia_Engine_Visuals_MeshNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_BackendContext* backendContext,
    Arcadia_ADL_MeshDefinition* source
  );

void
Arcadia_Engine_Visuals_MeshNode_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self,
    Arcadia_SizeValue* numberOfVertices
  );

void
Arcadia_Engine_Visuals_MeshNode_setAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self,
    Arcadia_Math_Color4Real32* baseColor
  );

Arcadia_Math_Color4Real32*
Arcadia_Engine_Visuals_MeshNode_getAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  );

#endif // ARCADIA_ENGINE_VISUALS_NODES_MESHNODE_H_INCLUDED
