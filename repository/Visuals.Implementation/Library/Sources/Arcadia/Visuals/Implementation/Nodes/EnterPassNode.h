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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_NODES_ENTERPASSNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_NODES_ENTERPASSNODE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Engine/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_EnterPassResource Arcadia_Visuals_Implementation_EnterPassResource;

// The implementation of an enter pass node.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.EnterPassNode", Arcadia_Engine_Visuals_Implementation_EnterPassNode,
                          u8"Arcadia.Engine.Visuals.RenderingContextNode");

struct Arcadia_Engine_Visuals_Implementation_EnterPassNodeDispatch {
  Arcadia_Engine_Visuals_EnterPassNodeDispatch parent;
};

struct Arcadia_Engine_Visuals_Implementation_EnterPassNode {
  Arcadia_Engine_Visuals_EnterPassNode parent;

  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_EnterPassResource* enterPassResource;
};

/// @brief Create an enter pass mode.
/// @return A pointer to the enter pass node.
Arcadia_Engine_Visuals_Implementation_EnterPassNode*
Arcadia_Engine_Visuals_Implementation_EnterPassNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_NODES_ENTERPASSNODE_H_INCLUDED
