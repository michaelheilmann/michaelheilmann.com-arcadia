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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_NODES_CAMERANODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_NODES_CAMERANODE_H_INCLUDED

#include "Arcadia/Engine/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;

// This does not operate any resources.
// Arcadia.Engine.Visuals.EnterPassNode operates the required resources for this node.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.CameraNode", Arcadia_Engine_Visuals_Implementation_CameraNode,
                          u8"Arcadia.Engine.Visuals.CameraNode");

struct Arcadia_Engine_Visuals_Implementation_CameraNodeDispatch {
  Arcadia_Engine_Visuals_CameraNodeDispatch _parent;
};

struct Arcadia_Engine_Visuals_Implementation_CameraNode {
  Arcadia_Engine_Visuals_CameraNode _parent;

  Arcadia_Natural8Value dirtyBits;
  Arcadia_Math_Matrix4Real32* worldToViewMatrix;
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix;
  Arcadia_Visuals_Implementation_BackendContext* backendContext;
};

Arcadia_Engine_Visuals_Implementation_CameraNode*
Arcadia_Engine_Visuals_Implementation_CameraNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_NODES_CAMERANODE_H_INCLUDED
