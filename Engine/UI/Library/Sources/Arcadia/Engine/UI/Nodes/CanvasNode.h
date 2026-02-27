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

#if !defined(ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED)
#define ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_UI_PRIVATE) || 1 != ARCADIA_ENGINE_UI_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/UI/Include.h` instead")
#endif
#include "Arcadia/Engine/UI/WidgetNode.h"
#include "Arcadia/Engine/Include.h"

// The "UI canvas" node.
Arcadia_declareObjectType(u8"Arcadia.Engine.UI.CanvasNode", Arcadia_Engine_UI_CanvasNode,
                          u8"Arcadia.Engine.UI.WidgetNode")

struct Arcadia_Engine_UI_CanvasNodeDispatch {
  Arcadia_Engine_UI_WidgetNodeDispatch _parent;
};

struct Arcadia_Engine_UI_CanvasNode {
  Arcadia_Engine_UI_WidgetNode _parent;
  /// The width of the visual canvas.
  Arcadia_Integer32Value visualsCanvasWidth;
  /// The height of the visual canvas.
  Arcadia_Integer32Value visualsCanvasHeight;
  /// The viewport node.
  Arcadia_Engine_Visuals_ViewportNode* viewportNode;
};

Arcadia_Engine_UI_CanvasNode*
Arcadia_Engine_UI_CanvasNode_create
  (
    Arcadia_Thread* thread
  );

/// @brief Set the size of the visuals canvass.
/// @param self A pointer to this UI canvas.
/// @param width The width of the visuals canvas.
/// @param height The height of the visuals canvas.
void
Arcadia_Engine_UI_CanvasNode_setVisualsCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_CanvasNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

void
Arcadia_Engine_UI_CanvasNode_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_CanvasNode* self
  );

#endif // ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED
