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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_SCENE_VIEWPORTNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_SCENE_VIEWPORTNODE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_ViewportResource Arcadia_Visuals_Implementation_ViewportResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Scene.ViewportNode", Arcadia_Visuals_Implementation_Scene_ViewportNode,
                          u8"Arcadia.Visuals.Scene.ViewportNode");

struct Arcadia_Visuals_Implementation_Scene_ViewportNodeDispatch {
  Arcadia_Visuals_Scene_ViewportNodeDispatch _parent;
};

struct Arcadia_Visuals_Implementation_Scene_ViewportNode {
  Arcadia_Visuals_Scene_ViewportNode _parent;

  Arcadia_Natural8Value dirtyBits;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_ViewportResource* viewportResource;

  struct {
    // Default is 193.
    Arcadia_Real32Value red;
    // Default is 216.
    Arcadia_Real32Value green;
    // Default is 195.
    Arcadia_Real32Value blue;
    // Default is 255.
    Arcadia_Real32Value alpha;
  } clearColor;

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

Arcadia_Visuals_Implementation_Scene_ViewportNode*
Arcadia_Visuals_Implementation_Scene_ViewportNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_SCENE_VIEWPORTNODE_H_INCLUDED
