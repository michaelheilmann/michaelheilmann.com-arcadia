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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VERTEXPROGRAMRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VERTEXPROGRAMRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.VertexProgramResource", Arcadia_Visuals_Implementation_VertexProgramResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_VertexProgramResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;
};

struct Arcadia_Visuals_Implementation_VertexProgramResource {
  Arcadia_Visuals_Implementation_Resource _parent;
};

Arcadia_Visuals_Implementation_VertexProgramResource*
Arcadia_Visuals_Implementation_VertexProgramResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VERTEXPROGRAMRESOURCE_H_INCLUDED
