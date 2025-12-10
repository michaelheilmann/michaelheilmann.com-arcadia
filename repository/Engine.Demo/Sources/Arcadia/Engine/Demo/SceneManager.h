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

#if !defined(ARCADIA_ENGINE_DEMO_SCENEMANGER_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_SCENEMANGER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Engine/Include.h"
typedef struct Arcadia_Engine_Demo_Scene Arcadia_Engine_Demo_Scene;

/// The scene manager is referenced by any scene.
/// A scene is "active" if sceneManager.scene = scene.
/// A scene can - at any point in time - activate another scene by setting sceneManager.scene to the desired scene.
Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.SceneManager", Arcadia_Engine_Demo_SceneManager,
                          u8"Arcadia.Object")

struct Arcadia_Engine_Demo_SceneManagerDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Engine_Demo_SceneManager {
  Arcadia_Object parent;
  /* The engine. */
  Arcadia_Engine* engine;
  /* The current scene. */
  Arcadia_Engine_Demo_Scene* scene;
};

/// @return The active scene or null.
/// @default The default is null.
Arcadia_Engine_Demo_Scene*
Arcadia_Engine_Demo_SceneManager_getScene
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self
  );

/// @param scene The new active scene if any or null.
void
Arcadia_Engine_Demo_SceneManager_setScene
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_SceneManager* self,
    Arcadia_Engine_Demo_Scene* scene
  );

Arcadia_Engine_Demo_SceneManager*
Arcadia_Engine_Demo_SceneManager_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine
  );

#endif // ARCADIA_ENGINE_DEMO_SCENEMANGER_H_INCLUDED
