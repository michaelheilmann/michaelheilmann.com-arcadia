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

#if !defined(ARCADIA_VISUALS_SCENE_MODELNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_MODELNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Scene/MeshNode.h"
#include "Arcadia/Visuals/Scene/MaterialNode.h"

// A "model node" consists of a
// - a mesh
// - a material
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.ModelNode", Arcadia_Visuals_Scene_ModelNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_ModelNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
};

struct Arcadia_Visuals_Scene_ModelNode {
  Arcadia_Visuals_Scene_Node _parent;
  
  /// The model definition.
  Arcadia_ADL_ModelDefinition* source; 
  /// The mesh of this model.
  Arcadia_Visuals_Scene_MeshNode* mesh;
  /// The material of this model.
  Arcadia_Visuals_Scene_MaterialNode* material;
};

#endif // ARCADIA_VISUALS_SCENE_MODELNODE_H_INCLUDED
