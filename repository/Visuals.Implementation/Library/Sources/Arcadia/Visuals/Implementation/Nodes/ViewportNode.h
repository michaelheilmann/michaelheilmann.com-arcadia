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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_NODES_VIEWPORTNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_NODES_VIEWPORTNODE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_ViewportResource Arcadia_Visuals_Implementation_ViewportResource;

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.ViewportNode", Arcadia_Engine_Visuals_Implementation_ViewportNode,
                          u8"Arcadia.Engine.Visuals.ViewportNode");

struct Arcadia_Engine_Visuals_Implementation_ViewportNodeDispatch {
  Arcadia_Engine_Visuals_ViewportNodeDispatch _parent;
};

struct Arcadia_Engine_Visuals_Implementation_ViewportNode {
  Arcadia_Engine_Visuals_ViewportNode _parent;

  Arcadia_Natural8Value dirtyBits;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_ViewportResource* viewportResource;

  // 193, 216, 195, 255
  Arcadia_Math_Color4Real32* clearColor;

  // Default is 1.
  Arcadia_Real32Value clearDepth;

  struct {
    // Default is 0.
    Arcadia_Real32Value left;
    // Default is 0.
    Arcadia_Real32Value bottom;
    // Default is 1.
    Arcadia_Real32Value right;
    // Default is 1.
    Arcadia_Real32Value top;
  } relativeViewportRectangle;

  struct {
    // The width of the canvas.
    // Default is 320.
    Arcadia_Real32Value width;
    // The height of the canvas.
    // Default is 240.
    Arcadia_Real32Value height;
  } canvasSize;

};

Arcadia_Engine_Visuals_Implementation_ViewportNode*
Arcadia_Engine_Visuals_Implementation_ViewportNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_NODES_VIEWPORTNODE_H_INCLUDED
