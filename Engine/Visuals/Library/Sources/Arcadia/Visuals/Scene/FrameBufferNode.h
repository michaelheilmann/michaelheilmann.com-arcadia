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

#if !defined(ARCADIA_VISUALS_SCENE_FRAMEBUFFERNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_FRAMEBUFFERNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Scene/Node.h"
typedef struct Arcadia_Visuals_Scene_ViewportNode Arcadia_Visuals_Scene_ViewportNode;

// A "framebuffer" node may be attached the "rendering context" node.
// If a "framebuffer" node is attached, rendering is performed to the framebuffer of that node.
// Otherwise rendering is performed to the default framebuffer.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.FrameBufferNode", Arcadia_Visuals_Scene_FrameBufferNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_FrameBufferNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
  void (*setSize)(Arcadia_Thread* thread, Arcadia_Visuals_Scene_FrameBufferNode*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getSize)(Arcadia_Thread* thread, Arcadia_Visuals_Scene_FrameBufferNode*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);
};

struct Arcadia_Visuals_Scene_FrameBufferNode {
  Arcadia_Visuals_Scene_Node _parent;
};

void
Arcadia_Visuals_Scene_FrameBufferNode_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

void
Arcadia_Visuals_Scene_FrameBufferNode_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_FrameBufferNode* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

#endif // ARCADIA_VISUALS_SCENE_FRAMEBUFFERNODE_H_INCLUDED
