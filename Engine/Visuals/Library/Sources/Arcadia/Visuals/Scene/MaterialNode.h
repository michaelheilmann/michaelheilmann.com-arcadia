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

#if !defined(ARCADIA_VISUALS_SCENE_MATERIALNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_MATERIALNODE_H_INCLUDED

#include "Arcadia/Visuals/Scene/Node.h"
#include "Arcadia/ADL/Include.h"
typedef struct Arcadia_Visuals_SceneNodeFactory Arcadia_Visuals_SceneNodeFactory;
typedef struct Arcadia_Visuals_Scene_TextureNode Arcadia_Visuals_Scene_TextureNode;
typedef struct Arcadia_Visuals_VPL_Program Arcadia_Visuals_VPL_Program;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.MaterialNode", Arcadia_Visuals_Scene_MaterialNode,
                          u8"Arcadia.Visuals.Scene.Node");

struct Arcadia_Visuals_Scene_MaterialNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
};

struct Arcadia_Visuals_Scene_MaterialNode {
  Arcadia_Visuals_Scene_Node parent;
  Arcadia_ADL_MaterialDefinition* source;
  Arcadia_Visuals_Scene_TextureNode* ambientColorTexture;
  Arcadia_Visuals_VPL_Program* program;
};

#endif  // ARCADIA_VISUALS_SCENE_MATERIALNODE_H_INCLUDED
