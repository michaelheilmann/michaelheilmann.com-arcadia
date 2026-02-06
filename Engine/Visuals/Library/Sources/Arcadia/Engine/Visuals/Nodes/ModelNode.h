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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_MODELNODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_MODELNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/Nodes/MeshNode.h"
#include "Arcadia/Engine/Visuals/Nodes/MaterialNode.h"

// A "model node" consists of a
// - a mesh
// - a material
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.ModelNode", Arcadia_Engine_Visuals_ModelNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_Visuals_ModelNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;
};

struct Arcadia_Engine_Visuals_ModelNode {
  Arcadia_Engine_Visuals_Node _parent;
  
  /// The model definition.
  Arcadia_ADL_ModelDefinition* source; 
  /// The mesh of this model.
  Arcadia_Engine_Visuals_MeshNode* mesh;
  /// The material of this model.
  Arcadia_Engine_Visuals_MaterialNode* material;
};

#endif // ARCADIA_ENGINE_VISUALS_NODES_MODELNODE_H_INCLUDED
