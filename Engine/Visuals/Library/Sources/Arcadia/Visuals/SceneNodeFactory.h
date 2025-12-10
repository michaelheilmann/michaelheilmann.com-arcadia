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

#if !defined(ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Engine/Include.h"
#include "Arcadia/Visuals/Scene/CameraNode.h"
#include "Arcadia/Visuals/Scene/FrameBufferNode.h"
#include "Arcadia/Visuals/Scene/RenderingContextNode.h"
#include "Arcadia/Visuals/Scene/MeshNode.h"
#include "Arcadia/Visuals/Scene/ViewportNode.h"

/// The implementation of a scene node factory for visuals scene nodes.
Arcadia_declareObjectType(u8"Arcadia.Visuals.SceneNodeFactory", Arcadia_Visuals_SceneNodeFactory,
                          Arcadia_Engine_SceneNodeFactory);

struct Arcadia_Visuals_SceneNodeFactoryDispatch {
  Arcadia_Engine_SceneNodeFactoryDispatch parent;

  Arcadia_Visuals_Scene_CameraNode*
  (*createCameraNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext
    );

  Arcadia_Visuals_Scene_FrameBufferNode*
  (*createFrameBufferNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext
    );

  Arcadia_Visuals_Scene_RenderingContextNode*
  (*createRenderingContextNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext
    );

  Arcadia_Visuals_Scene_MeshNode*
  (*createMeshNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext
    );

  Arcadia_Visuals_Scene_ViewportNode*
  (*createViewportNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext
    );
};

struct Arcadia_Visuals_SceneNodeFactory {
  Arcadia_Engine_SceneNodeFactory parent;
};

Arcadia_Visuals_Scene_CameraNode*
Arcadia_Visuals_SceneNodeFactory_createCameraNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

Arcadia_Visuals_Scene_FrameBufferNode*
Arcadia_Visuals_SceneNodeFactory_createFrameBufferNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

Arcadia_Visuals_Scene_RenderingContextNode*
Arcadia_Visuals_SceneNodeFactory_createRenderingContextNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

Arcadia_Visuals_Scene_MeshNode*
Arcadia_Visuals_SceneNodeFactory_createMeshNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

Arcadia_Visuals_Scene_ViewportNode*
Arcadia_Visuals_SceneNodeFactory_createViewportNode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED
