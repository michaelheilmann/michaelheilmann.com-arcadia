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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_MESHRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_MESHRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"
#include "Arcadia/Math/Include.h"
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.MeshResource", Arcadia_Visuals_Implementation_MeshResource,
                          u8"Arcadia.Visuals.Implementation.Resource")

struct Arcadia_Visuals_Implementation_MeshResource {
  Arcadia_Visuals_Implementation_Resource _parent;
  void (*setLocalToWorldMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*);
  void (*setViewToProjectionMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*);
  void (*setWorldToViewMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Matrix4Real32*);
};

void
Arcadia_Visuals_Implemention_MeshResource_setLocalToWorldMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  );

void
Arcadia_Visuals_Implemention_MeshResource_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

void
Arcadia_Visuals_Implemention_MeshResource_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_MeshResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_MESHRESOURCE_H_INCLUDED
