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

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"
#include "Arcadia/ADL/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.MainScene", Arcadia_Engine_Demo_MainScene,
                          u8"Arcadia.Engine.Demo.Scene");

struct Arcadia_Engine_Demo_MainSceneDispatch {
  Arcadia_Engine_Demo_SceneDispatch parent;
};

struct Arcadia_Engine_Demo_MainScene {
  Arcadia_Engine_Demo_Scene parent;

  // @todo This is should be inter-scene not intra-scene.
  Arcadia_ADL_Definitions* definitions;

  // Two viewports, three of them.
  Arcadia_Engine_Visuals_ViewportNode* viewportNodes[3];
  // A single camera, re-attached to the respective viewport / model combination for rendering.
  Arcadia_Engine_Visuals_CameraNode* cameraNode;
  // A single context, re-update with the information for the respective viewport / model combination for rendering.
  Arcadia_Engine_Visuals_EnterPassNode* enterPassNode;

  // The models, thee of them.
  Arcadia_Engine_Visuals_ModelNode* modelNode[3];

  // The sound source for some background sound effects.
  Arcadia_Engine_Audials_SoundSourceNode* soundSourceNode;
};

Arcadia_Engine_Demo_MainScene*
Arcadia_Engine_Demo_MainScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Engine_Demo_SceneManager* sceneManager
  );

#endif // ARCADIA_ENGINE_DEMO_SCENES_MAINSCENE_H_INCLUDED
