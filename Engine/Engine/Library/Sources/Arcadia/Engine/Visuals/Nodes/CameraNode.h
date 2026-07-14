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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_CAMERANODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_CAMERANODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/Node.h"
typedef struct Arcadia_Engine_Visuals_ViewportNode Arcadia_Engine_Visuals_ViewportNode;

// @remarks
// This does not operate any resources.
// Arcadia.Engine.Visuals.EnterPassNode operates the required resources for this node.
// @remarks
// The camera is positioned at (0,0,1) looking down the negative z-axis. The positive x-axis is going right and the positive y-axis is going up.
// It applies a perspective projection with a 60 degrees field of view, a 4/3 aspect ratio, a near z plane of 0.1 and a far z zplane of 100.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.CameraNode", Arcadia_Engine_Visuals_CameraNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_Visuals_CameraNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;

  Arcadia_Math_Matrix4Real32* (*getViewToProjectionMatrix)(Arcadia_Thread*, Arcadia_Engine_Visuals_CameraNode*);
  void (*setViewToProjectionMatrix)(Arcadia_Thread*, Arcadia_Engine_Visuals_CameraNode*, Arcadia_Math_Matrix4Real32*);

  Arcadia_Math_Matrix4Real32* (*getWorldToViewMatrix)(Arcadia_Thread*, Arcadia_Engine_Visuals_CameraNode*);
  void (*setWorldToViewMatrix)(Arcadia_Thread*, Arcadia_Engine_Visuals_CameraNode*, Arcadia_Math_Matrix4Real32*);
};

struct Arcadia_Engine_Visuals_CameraNode {
  Arcadia_Engine_Visuals_Node _parent;
  
  Arcadia_Natural8Value dirtyBits;
  Arcadia_Math_Matrix4Real32* worldToViewMatrix;
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix;
  Arcadia_Engine_Visuals_BackendContext* backendContext;
};

/// @brief Create a camera node.
/// @param thread A pointer to this thread.
/// @param backendContext A pointer to the backend context or a null pointer.
/// @return A pointer to the camera node.
Arcadia_Engine_Visuals_CameraNode*
Arcadia_Engine_Visuals_CameraNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_BackendContext* backendContext
  );

Arcadia_Math_Matrix4Real32*
Arcadia_Engine_Visuals_CameraNode_getViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_CameraNode* self
  );

void
Arcadia_Engine_Visuals_CameraNode_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_CameraNode* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

Arcadia_Math_Matrix4Real32*
Arcadia_Engine_Visuals_CameraNode_getWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_CameraNode* self
  );

void
Arcadia_Engine_Visuals_CameraNode_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_CameraNode* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

#endif // ARCADIA_ENGINE_VISUALS_NODES_CAMERANODE_H_INCLUDED
