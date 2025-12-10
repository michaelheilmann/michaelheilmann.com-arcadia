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

#if !defined(ARCADIA_VISUALS_SCENE_RENDERSCENE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_RENDERSCENE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Scene/RenderingContextNode.h"
#include "Arcadia/Visuals/Scene/MeshNode.h"

void
Arcadia_Visuals_renderScene
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_RenderingContextNode* renderingContextNode,
    Arcadia_Visuals_Scene_MeshNode* meshNode,
    Arcadia_Visuals_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_SCENE_RENDERSCENE_H_INCLUDED
