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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_TEXTURENODE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_TEXTURENODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE) || 1 != ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Implementation/Include.h` instead")
#endif

#include "Arcadia/Visuals/Include.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;
typedef struct Arcadia_Visuals_Implementation_TextureResource Arcadia_Visuals_Implementation_TextureResource;

// The implementation of a texture.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Implementation.TextureNode", Arcadia_Engine_Visuals_Implementation_TextureNode,
                          u8"Arcadia.Engine.Visuals.TextureNode");

struct Arcadia_Engine_Visuals_Implementation_TextureNodeDispatch {
  Arcadia_Engine_Visuals_TextureNodeDispatch parent;
};

struct Arcadia_Engine_Visuals_Implementation_TextureNode {
  Arcadia_Engine_Visuals_TextureNode parent;
  // Bitmask of the dirty properties, that is, properties which were not uploaded.
  Arcadia_Natural8Value dirtyBits;
  // The backend context.
  Arcadia_Visuals_Implementation_BackendContext* backendContext;
  // The texture resource.
  Arcadia_Visuals_Implementation_TextureResource* textureResource;
};

// @param backendContext A pointer to the backend context or the null pointer.
Arcadia_Engine_Visuals_Implementation_TextureNode*
Arcadia_Engine_Visuals_Implementation_TextureNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext,
    Arcadia_ADL_TextureDefinition* source
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_TEXTURENODE_H_INCLUDED
