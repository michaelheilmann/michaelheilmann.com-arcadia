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

#if !defined(ARCADIA_VISUALS_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Scene/Node.h"
typedef struct Arcadia_Visuals_Scene_CameraNode Arcadia_Visuals_Scene_CameraNode;
typedef struct Arcadia_Visuals_Scene_FrameBufferNode Arcadia_Visuals_Scene_FrameBufferNode;

// This represents state common to a rendering of meshes.
//
// The rendering context node must be provided with a rendering context node -> camera node -> viewport node path.
// The rendering context node may be provided with a rendering context node -> frame buffer node path.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.RenderingContextNode", Arcadia_Visuals_Scene_RenderingContextNode,
                          u8"Arcadia.Visuals.Scene.Node");

struct Arcadia_Visuals_Scene_RenderingContextNodeDispatch {
  Arcadia_Visuals_Scene_NodeDispatch parent;
};

struct Arcadia_Visuals_Scene_RenderingContextNode {
  Arcadia_Visuals_Scene_Node parent;

  // A pointer to the camera.
  Arcadia_Visuals_Scene_CameraNode* cameraNode;

  // A pointer to the frame buffer node (render to frame buffer) or null (render to primary frame buffer).
  Arcadia_Visuals_Scene_FrameBufferNode* frameBufferNode;

  struct {
    // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
    // Default is 193.
    Arcadia_Real32Value red;
    // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
    // Default is 216.
    Arcadia_Real32Value green;
    // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
    // Default is 195.
    Arcadia_Real32Value blue;
    // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
    // Default is 255.
    Arcadia_Real32Value alpha;
  } viewportClearColor;

  // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
  // The default value is 1.
  Arcadia_Real32Value viewportClearDepth;

  // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
  // The relative viewport rectangle.
  // The default value is 0, 0, 1, 1.
  struct {
    Arcadia_Real32Value left, bottom, right, top;
  } relativeViewportRectangle;

  // @todo Remove this. We can obtain that from the rendering context node -> camera node -> viewport node path.
  // The size of the canvas.
  // The default value is 320 x 240.
  struct {
    Arcadia_Real32Value width, height;
  } canvasSize;

  // @todo Remove this. We can obtain that from the rendering context node -> camera node.
  // The view matrix.
  // The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix;

  // @todo Remove this. We can obtain that from the rendering context node -> camera node.
  // The projection matrix.
  // The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* worldToViewMatrix;
};

void
Arcadia_Visuals_Scene_RenderingContextNode_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

void
Arcadia_Visuals_Scene_RenderingContextNode_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

void
Arcadia_Visuals_Scene_RenderingContextNode_setFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Visuals_Scene_FrameBufferNode* frameBufferNode
  );

Arcadia_Visuals_Scene_FrameBufferNode*
Arcadia_Visuals_Scene_RenderingContextNode_getFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  );

void
Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self,
    Arcadia_Visuals_Scene_CameraNode* cameraNode
  );

Arcadia_Visuals_Scene_CameraNode*
Arcadia_Visuals_Scene_RenderingContextNode_getCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* self
  );

#endif // ARCADIA_VISUALS_SCENE_RENDERINGCONTEXTNODE_H_INCLUDED
