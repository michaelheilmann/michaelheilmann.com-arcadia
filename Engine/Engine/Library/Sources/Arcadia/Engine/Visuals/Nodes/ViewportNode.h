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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_VIEWPORTNODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_VIEWPORTNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/Node.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.ViewportNode", Arcadia_Engine_Visuals_ViewportNode,
                          u8"Arcadia.Engine.Visuals.Node");

struct Arcadia_Engine_Visuals_ViewportNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;

  Arcadia_BooleanValue
  (*getClearColorBuffer)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self
    );

  void
  (*setClearColorBuffer)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_BooleanValue clearColorBuffer
    );

  Arcadia_Math_Color4Real32*
  (*getClearColor)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self
    );

  void
  (*setClearColor)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Math_Color4Real32* clearColor
    );

  Arcadia_BooleanValue
  (*getClearDepthBuffer)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self
    );

  void
  (*setClearDepthBuffer)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_BooleanValue clearDepthBuffer
    );

  Arcadia_Real32Value
  (*getClearDepth)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self
    );

  void
  (*setClearDepth)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Real32Value depth
    );

  void
  (*getRelativeViewportRectangle)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Real32Value* left,
      Arcadia_Real32Value* bottom,
      Arcadia_Real32Value* right,
      Arcadia_Real32Value* top
    );

  void
  (*setRelativeViewportRectangle)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Real32Value left,
      Arcadia_Real32Value bottom,
      Arcadia_Real32Value right,
      Arcadia_Real32Value top
    );

  void
  (*getCanvasSize)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Real32Value* width,
      Arcadia_Real32Value* height
    );

  void
  (*setCanvasSize)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Visuals_ViewportNode* self,
      Arcadia_Real32Value width,
      Arcadia_Real32Value height
    );
};

struct Arcadia_Engine_Visuals_ViewportNode {
  Arcadia_Engine_Visuals_Node _parent;
};

Arcadia_BooleanValue
Arcadia_Engine_Visuals_ViewportNode_getClearColorBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self
  );

/// Set if clearing the color buffer is enabled.
/// Default value is #Arcadia_BooleanValue_True.
void
Arcadia_Engine_Visuals_ViewportNode_setClearColorBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_BooleanValue clearColorBuffer
  );

Arcadia_Math_Color4Real32*
Arcadia_Engine_Visuals_ViewportNode_getClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self
  );

/// Set the clear color.
/// Default values are red = 193, green = 216, blue = 195, and alpha = 255.
void
Arcadia_Engine_Visuals_ViewportNode_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Math_Color4Real32* clearColor
  );

Arcadia_BooleanValue
Arcadia_Engine_Visuals_ViewportNode_getClearDepthBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self
  );

/// Set if clearing the depth buffer is enabled.
/// Default value is #Arcadia_BooleanValue_True.
void
Arcadia_Engine_Visuals_ViewportNode_setClearDepthBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_BooleanValue clearDepthBuffer
  );

Arcadia_Real32Value
Arcadia_Engine_Visuals_ViewportNode_getClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self
  );

/// Set the clear depth.
/// Default value is depth = 1.
void
Arcadia_Engine_Visuals_ViewportNode_setClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Real32Value depth
  );

void
Arcadia_Engine_Visuals_ViewportNode_getRelativeViewportRectangle
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  );

/// Set the viewport relative rectangle.
/// x axis going from left to right, y axis going from bottom to top
/// Default values are left = 0, bottom = 0, right = 1, and top  = 1.
void
Arcadia_Engine_Visuals_ViewportNode_setRelativeViewportRectangle
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

void
Arcadia_Engine_Visuals_ViewportNode_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Real32Value* width,
    Arcadia_Real32Value* height
  );

/// Set the canvas size.
/// Default values are width = 320 and height = 240.
void
Arcadia_Engine_Visuals_ViewportNode_setCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ViewportNode* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

#endif // ARCADIA_ENGINE_VISUALS_NODES_VIEWPORTNODE_H_INCLUDED
