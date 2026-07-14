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

#if !defined(ARCADIA_ENGINE_VISUALS_RESOURCES_MODELRESOURCE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_RESOURCES_MODELRESOURCE_H_INCLUDED

#include "Arcadia/Engine/Visuals/Resource.h"
typedef struct Arcadia_Engine_Visuals_Implementation_ConstantBufferResource Arcadia_Engine_Visuals_Implementation_ConstantBufferResource;
typedef struct Arcadia_Engine_Visuals_Implementation_MaterialResource Arcadia_Engine_Visuals_Implementation_MaterialResource;
typedef struct Arcadia_Engine_Visuals_Implementation_VertexBufferResource Arcadia_Engine_Visuals_Implementation_VertexBufferResource;

#define Arcadia_Engine_Visuals_Implementation_ModelResource_LocalToWorldMatrixDirty (1)

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Resources.ModelResource", Arcadia_Engine_Visuals_Implementation_ModelResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Engine_Visuals_Implementation_ModelResourceDispatch {
  Arcadia_Engine_Visuals_Implementation_ResourceDispatch _parent;
  void (*setLocalToWorldMatrix)(Arcadia_Thread*, Arcadia_Engine_Visuals_Implementation_ModelResource*, Arcadia_Math_Matrix4Real32*);
};

struct Arcadia_Engine_Visuals_Implementation_ModelResource {
  Arcadia_Engine_Visuals_Implementation_Resource _parent;
  // The dirty flags.
  Arcadia_Natural8Value dirty;
  // The local to world matrix of the model.
  // The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* localToWorldMatrix;

  /// Constant buffer with model-specific information.
  /// This is currently only the model to world matrix.
  Arcadia_Engine_Visuals_Implementation_ConstantBufferResource* constantBuffer;

  /// Constant buffer with mesh-specific information.
  /// This is currently only the mesh color.
  Arcadia_Engine_Visuals_Implementation_ConstantBufferResource* meshConstantBuffer;

  /// The vertices of the mesh.
  Arcadia_Engine_Visuals_Implementation_VertexBufferResource* meshVertexBuffer;

  /// The material of the model.
  Arcadia_Engine_Visuals_Implementation_MaterialResource* material;

};

void
Arcadia_Engine_Visuals_Implementation_ModelResource_setLocalToWorldMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  );

#endif // ARCADIA_ENGINE_VISUALS_RESOURCES_MODELRESOURCE_H_INCLUDED
