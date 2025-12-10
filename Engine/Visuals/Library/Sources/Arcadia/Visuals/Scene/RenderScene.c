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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Scene/RenderScene.h"

#include "Arcadia/Visuals/Scene/FrameBufferNode.h"

void
Arcadia_Visuals_renderScene
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* renderingContextNode,
    Arcadia_Visuals_Scene_MeshNode* meshNode,
    Arcadia_Visuals_BackendContext* backendContext
  )
{
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)renderingContextNode,
                                                       backendContext);
  if (renderingContextNode->frameBufferNode) {
    // "rendering" the scene buffer activates it.
    Arcadia_Visuals_Scene_Node_render
      (
        thread,
        (Arcadia_Visuals_Scene_Node*)renderingContextNode->frameBufferNode,
        renderingContextNode
      );
  }
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)renderingContextNode->cameraNode, renderingContextNode);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, renderingContextNode);
}
