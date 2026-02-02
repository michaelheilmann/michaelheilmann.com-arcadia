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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_MODELRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_MODELRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

#define Arcadia_Visuals_Implementation_ModelResource_LocalToWorldMatrixDirty (1)

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Resources.ModelResource", Arcadia_Visuals_Implementation_ModelResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_ModelResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;
  void (*setLocalToWorldMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ModelResource*, Arcadia_Math_Matrix4Real32*);
};

struct Arcadia_Visuals_Implementation_ModelResource {
  Arcadia_Visuals_Implementation_Resource _parent;
  // The dirty flags.
  Arcadia_Natural8Value dirty;
  // The local to world matrix of the model.
  // The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* localToWorldMatrix;
};

void
Arcadia_Visuals_Implementation_ModelResource_setLocalToWorldMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ModelResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_MODELRESOURCE_H_INCLUDED
