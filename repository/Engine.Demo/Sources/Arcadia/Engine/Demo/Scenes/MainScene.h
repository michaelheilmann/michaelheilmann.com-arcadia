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

#if !defined(ARCADIA_ENGINE_DEMO_SCENES_MAINSCENE_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_SCENES_MAINSCENE_H_INCLUDED

#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.MainScene", Arcadia_Engine_Demo_MainScene,
                          u8"Arcadia.Engine.Demo.Scene");

struct Arcadia_Engine_Demo_MainSceneDispatch {
  Arcadia_Engine_Demo_SceneDispatch parent;
};

struct Arcadia_Engine_Demo_MainScene {
  Arcadia_Engine_Demo_Scene parent;
  // Two viewports, #1 and #2, one for each side of the window.
  Arcadia_Visuals_Scene_ViewportNode* viewportNodes[2];
  // A single camera, rendering the same scene twice, first to viewport #1 and the to viewport #2.
  Arcadia_Visuals_Scene_CameraNode* cameraNode;
  // A single context, update with viewport- and camera-specific information for each render of the scene.
  Arcadia_Visuals_Scene_RenderingContextNode* renderingContextNode;

  // The mesh (the scene).
  Arcadia_Visuals_Scene_MeshNode* meshNode;

  // The sound source for some background sound effects.
  Arcadia_Audials_Scene_SoundSourceNode* soundSourceNode;
};

Arcadia_Engine_Demo_MainScene*
Arcadia_Engine_Demo_MainScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Engine_Demo_SceneManager* sceneManager
  );

#endif // ARCADIA_ENGINE_DEMO_SCENES_MAINSCENE_H_INCLUDED
