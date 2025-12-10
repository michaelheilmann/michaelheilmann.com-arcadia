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

#if !defined(ARCADIA_ENGINE_DEMO_SCENES_PRELOADINGSCENE_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_SCENES_PRELOADINGSCENE_H_INCLUDED

#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"
#include "Arcadia/ADL/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.ArcadiaLogoScene", Arcadia_Engine_Demo_ArcadiaLogoScene,
                          u8"Arcadia.Engine.Demo.Scene");

struct Arcadia_Engine_Demo_ArcadiaLogoSceneDispatch {
  Arcadia_Engine_Demo_SceneDispatch parent;
};

struct Arcadia_Engine_Demo_ArcadiaLogoScene {
  Arcadia_Engine_Demo_Scene parent;
  // The definitions.
  Arcadia_ADL_Definitions* definitions;
  // A framebuffer node.
  Arcadia_Visuals_Scene_FrameBufferNode* frameBufferNode;
  // One viewport.
  Arcadia_Visuals_Scene_ViewportNode* viewportNode;
  // A single camera.
  Arcadia_Visuals_Scene_CameraNode* cameraNode;
  // A single context, update with viewport- and camera-specific information for each render of the scene.
  Arcadia_Visuals_Scene_RenderingContextNode* renderingContextNode;

  /// The duration the scene is displayed so far.
  Arcadia_Real64Value duration;

  // The mesh (the scene).
  Arcadia_Visuals_Scene_MeshNode* meshNode;

  // The list of ADL files to load.
  Arcadia_List* toLoad;
};

Arcadia_Engine_Demo_ArcadiaLogoScene*
Arcadia_Engine_Demo_ArcadiaLogoScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Engine_Demo_SceneManager* sceneManager
  );

#endif // ARCADIA_ENGINE_DEMO_SCENES_PRELOADINGSCENE_H_INCLUDED
