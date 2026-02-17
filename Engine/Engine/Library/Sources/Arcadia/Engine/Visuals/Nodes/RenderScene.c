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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/Nodes/RenderScene.h"

void
Arcadia_Engine_Visuals_renderScene
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_EnterPassNode* enterPassNode,
    Arcadia_Engine_Visuals_ModelNode* modelNode,
    Arcadia_Visuals_BackendContext* backendContext
  )
{
  Arcadia_Engine_Node_setVisualsBackendContext(thread, (Arcadia_Engine_Node*)enterPassNode, (Arcadia_Engine_Visuals_BackendContext*)backendContext);
  if (enterPassNode->frameBufferNode) {
    // "rendering" the scene buffer activates it.
    Arcadia_Engine_Visuals_Node_render
      (
        thread,
        (Arcadia_Engine_Visuals_Node*)enterPassNode->frameBufferNode,
        enterPassNode
      );
  }
  // Render the enter pass node.
  // Pass mesh nodes to the enter pass node.
  Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)enterPassNode, (Arcadia_Engine_Visuals_EnterPassNode*)enterPassNode);
  // Render the mesh node.
  // TODO: Render multiple mesh nodes.
  Arcadia_Engine_Visuals_Node_render(thread, (Arcadia_Engine_Visuals_Node*)modelNode, enterPassNode);
  // TODO: Render the leave pass node.
}
