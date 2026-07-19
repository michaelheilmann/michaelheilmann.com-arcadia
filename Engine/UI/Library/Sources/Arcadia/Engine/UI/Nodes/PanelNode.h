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

#if !defined(ARCADIA_ENGINE_UI_NODES_PANELNODE_H_INCLUDED)
#define ARCADIA_ENGINE_UI_NODES_PANELNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_UI_PRIVATE) || 1 != ARCADIA_ENGINE_UI_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/UI/Include.h` instead")
#endif
#include "Arcadia/Engine/UI/WidgetNode.h"

// A "model node" consists of a
// - a mesh
// - a material
Arcadia_declareObjectType(u8"Arcadia.Engine.UI.PanelNode", Arcadia_Engine_UI_PanelNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_UI_PanelNodeDispatch {
  Arcadia_Engine_UI_WidgetNodeDispatch parent;
};

struct Arcadia_Engine_UI_PanelNode {
  Arcadia_Engine_UI_WidgetNode _parent;

  /// The model definition.
  Arcadia_ADL_ModelDefinition* source;
  /// The mesh of this model.
  Arcadia_Engine_Visuals_MeshNode* mesh;
  /// The material of this model.
  Arcadia_Engine_Visuals_MaterialNode* material;
  /// The backend context.
  Arcadia_Engine_Visuals_BackendContext* backendContext;
  /// The model resource.
  Arcadia_Engine_Visuals_Implementation_ModelResource* modelResource;
};

Arcadia_Engine_UI_PanelNode*
Arcadia_Engine_UI_PanelNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  );

#endif // ARCADIA_ENGINE_UI_NODES_PANELNODE_H_INCLUDED
