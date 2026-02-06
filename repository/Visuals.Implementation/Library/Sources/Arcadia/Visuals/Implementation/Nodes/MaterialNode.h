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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_MATERIALNODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_MATERIALNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE) || 1 != ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Implementation/Include.h` instead")
#endif

#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_MaterialResource Arcadia_Visuals_Implementation_MaterialResource;

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.MaterialNode", Arcadia_Engine_Visuals_Implementation_MaterialNode,
                          u8"Arcadia.Engine.Visuals.MaterialNode");

struct Arcadia_Engine_Visuals_Implementation_MaterialNodeDispatch {
  Arcadia_Engine_Visuals_MaterialNodeDispatch parent;
};

struct Arcadia_Engine_Visuals_Implementation_MaterialNode {
  Arcadia_Engine_Visuals_MaterialNode parent;
  /// The material resource of this material node.
  Arcadia_Visuals_Implementation_MaterialResource* materialResource;
  /// The backend context of this material node.
  Arcadia_Visuals_Implementation_BackendContext* backendContext;
};

// @param backendContext A pointer to the backend context or the null pointer.
Arcadia_Engine_Visuals_Implementation_MaterialNode*
Arcadia_Engine_Visuals_Implementation_MaterialNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_MaterialDefinition* source
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_MATERIALNODE_H_INCLUDED
