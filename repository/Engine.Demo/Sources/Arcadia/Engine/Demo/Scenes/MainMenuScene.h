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

#if !defined(ARCADIA_ENGINE_DEMO_SCENES_MAINMENUSCENE_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_SCENES_MAINMENUSCENE_H_INCLUDED

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"
#include "Arcadia/ADL/Include.h"
#include "Arcadia/Engine/UI/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.MainMenuScene", Arcadia_Engine_Demo_MainMenuScene,
                          u8"Arcadia.Engine.Demo.Scene");

struct Arcadia_Engine_Demo_MainMenuSceneDispatch {
  Arcadia_Engine_Demo_SceneDispatch parent;
};

struct Arcadia_Engine_Demo_MainMenuScene {
  Arcadia_Engine_Demo_Scene parent;

  // @todo This is should be inter-scene not intra-scene.
  Arcadia_ADL_Definitions* definitions;

  // The viewport.
  Arcadia_Engine_Visuals_ViewportNode* viewportNode;
  // A single camera, re-attached to the respective viewport / model combination for rendering.
  Arcadia_Engine_Visuals_CameraNode* cameraNode;
  // A single context, re-update with the information for the respective viewport / model combination for rendering.
  Arcadia_Engine_Visuals_EnterPassNode* enterPassNode;

  // The models, thee of them.
  Arcadia_Engine_Visuals_ModelNode* modelNode;

  // The 'W', 'A', 'S', and 'D' latches.
  Arcadia_BooleanValue latches[4];
  struct {
    Arcadia_Real32Value oldx;
    Arcadia_Real32Value oldy;
  } mousePosition;
  Arcadia_BooleanValue mouseInWindow;

  // The sound source for some background sound effects.
  Arcadia_Engine_Audials_SoundSourceNode* soundSourceNode;
  // The user interface.
  Arcadia_Engine_UI_CanvasNode* uiCanvasNode;

  struct {

    /// The forward vector of the viewer.
    Arcadia_Math_Vector3Real32* forward;

    /// The up vector of the viewer.
    Arcadia_Math_Vector3Real32* up;

    /// The right vector of the viewer.
    Arcadia_Math_Vector3Real32* right;

    /// The position of the viewer.
    Arcadia_Math_Vector3Real32* position;

    /// "pitch" is the angle, in degrees, of a counter-clockwise rotation of the camera around its local x-axis
    /// The initial value is @a 0.
    Arcadia_Real32Value pitch;
    
    /// "yaw" is the angle, in degrees, of a counter-clockwise rotation of the camera around its local y-axis.
    /// The initial value is @a 0.
    Arcadia_Real32Value yaw;

    /// "roll" is the angle, in degrees, of a counter-clockwise rotation of the camera around its local z-axis
    /// The initial value is @a 0.
    Arcadia_Real32Value roll;

  } viewer;
};

Arcadia_Engine_Demo_MainMenuScene*
Arcadia_Engine_Demo_MainMenuScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Engine_Demo_SceneManager* sceneManager
  );

#endif // ARCADIA_ENGINE_DEMO_SCENES_MAINMENUSCENE_H_INCLUDED
