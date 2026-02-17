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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_NODES_MODELNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_NODES_MODELNODE_H_INCLUDED

#include "Arcadia/Engine/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_ModelResource Arcadia_Visuals_Implementation_ModelResource;

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.ModelNode", Arcadia_Engine_Visuals_Implementation_ModelNode,
                          u8"Arcadia.Engine.Visuals.ModelNode");

struct Arcadia_Engine_Visuals_Implementation_ModelNodeDispatch {
  Arcadia_Engine_Visuals_ModelNodeDispatch _parent;
};

struct Arcadia_Engine_Visuals_Implementation_ModelNode {
  Arcadia_Engine_Visuals_ModelNode _parent;
  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  Arcadia_Visuals_Implementation_ModelResource* modelResource;
};

Arcadia_Engine_Visuals_Implementation_ModelNode*
Arcadia_Engine_Visuals_Implementation_ModelNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_ModelDefinition* source
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_NODES_MODELNODE_H_INCLUDED
