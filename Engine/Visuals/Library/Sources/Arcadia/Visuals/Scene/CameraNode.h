// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_VISUALS_SCENE_CAMERANODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_CAMERANODE_H_INCLUDED

#include "Arcadia/Visuals/Scene/Node.h"
typedef struct Arcadia_Visuals_Scene_ViewportNode Arcadia_Visuals_Scene_ViewportNode;
typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext;
typedef struct Arcadia_Visuals_Implementation_MeshResource Arcadia_Visuals_Implementation_MeshResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.CameraNode", Arcadia_Visuals_Scene_CameraNode,
                          u8"Arcadia.Visuals.Scene.Node")

struct Arcadia_Visuals_Scene_CameraNode {
  Arcadia_Visuals_Scene_Node _parent;
  Arcadia_Visuals_Scene_ViewportNode* viewport;
  void (*setViewToProjectionMatrix)(Arcadia_Thread* thread, Arcadia_Visuals_Scene_CameraNode*, Arcadia_Math_Matrix4Real32*);
  void (*setWorldToViewMatrix)(Arcadia_Thread* thread, Arcadia_Visuals_Scene_CameraNode*, Arcadia_Math_Matrix4Real32*);
};

void
Arcadia_Visuals_Scene_CameraNode_setViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Visuals_Scene_ViewportNode* viewport
  );

void
Arcadia_Visuals_Scene_CameraNode_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

void
Arcadia_Visuals_Scene_CameraNode_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_CameraNode* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

#endif // ARCADIA_VISUALS_SCENE_CAMERANODE_H_INCLUDED
