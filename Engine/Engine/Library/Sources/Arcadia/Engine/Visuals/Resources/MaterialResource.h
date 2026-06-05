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

#if !defined(ARCADIA_ENGINE_VISUALS_RESOURCES_MATERIALRESOURCE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_RESOURCES_MATERIALRESOURCE_H_INCLUDED

#include "Arcadia/Engine/Visuals/Resource.h"
#include "Arcadia/Math/Include.h"

typedef enum Arcadia_Engine_Visuals_Implementation_MaterialResource_AmbientColorSource {
  Arcadia_Engine_Visuals_Implementation_MaterialResource_AmbientColorSource_Mesh,
  Arcadia_Engine_Visuals_Implementation_MaterialResource_AmbientColorSource_Vertex,
  Arcadia_Engine_Visuals_Implementation_MaterialResource_AmbientColorSource_Texture,
} Arcadia_Engine_Visuals_Implementation_MaterialResource_AmbientColorSource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.MaterialResource", Arcadia_Engine_Visuals_Implementation_MaterialResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Engine_Visuals_Implementation_MaterialResourceDispatch {
  Arcadia_Engine_Visuals_Implementation_ResourceDispatch _parent;
};

struct Arcadia_Engine_Visuals_Implementation_MaterialResource {
  Arcadia_Engine_Visuals_Implementation_Resource _parent;
};

#endif // ARCADIA_ENGINE_VISUALS_RESOURCES_MATERIALRESOURCE_H_INCLUDED
