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

#if !defined(ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Visuals/Scene/MeshNode.h"
#include "Arcadia/Visuals/Scene/ViewportNode.h"
#include "Arcadia/Visuals/Window.h"

/// The singleton object of a type derived from Arcadia.Visuals.Context
/// is the representation of the retained mode renderer's state and the
/// interface to manipulate that state.
Arcadia_declareObjectType(u8"Arcadia.Visuals.SceneNodeFactory", Arcadia_Visuals_SceneNodeFactory,
                          Arcadia_Engine_SceneNodeFactory);

struct Arcadia_Visuals_SceneNodeFactory {
  Arcadia_Engine_SceneNodeFactory parent;

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

  void
  (*render)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_SceneNodeFactory* self,
      Arcadia_Visuals_BackendContext* backendContext,
      Arcadia_Visuals_Window* window
    );
};

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

void
Arcadia_Visuals_SceneNodeFactory_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_SceneNodeFactory* self,
    Arcadia_Visuals_BackendContext* backendContext,
    Arcadia_Visuals_Window* window
  );

#endif // ARCADIA_VISUALS_SCENENODEFACTORY_H_INCLUDED
