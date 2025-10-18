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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_PROGRAMRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_PROGRAMRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

typedef struct Arcadia_Visuals_Implementation_VertexProgramResource Arcadia_Visuals_Implementation_VertexProgramResource;
typedef struct Arcadia_Visuals_Implementation_FragmentProgramResource Arcadia_Visuals_Implementation_FragmentProgramResource;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.ProgramResource", Arcadia_Visuals_Implementation_ProgramResource,
                          u8"Arcadia.Visuals.Implementation.Resource")

struct Arcadia_Visuals_Implementation_ProgramResource {
  Arcadia_Visuals_Implementation_Resource _parent;
};

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_PROGRAMRESOURCE_H_INCLUDED
