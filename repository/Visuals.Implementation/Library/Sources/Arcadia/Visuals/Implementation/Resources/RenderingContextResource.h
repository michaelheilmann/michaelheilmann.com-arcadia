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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_RENDERINGCONTEXTRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_RENDERINGCONTEXTRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;

typedef struct Arcadia_Visuals_Implementation_ConstantBufferResource Arcadia_Visuals_Implementation_ConstantBufferResource;
typedef struct Arcadia_Visuals_Implementation_FrameBufferResource Arcadia_Visuals_Implementation_FrameBufferResource;


#define Arcadia_Visuals_Implementation_RenderingContextResource_ViewToProjectionMatrixDirty (1)
#define Arcadia_Visuals_Implementation_RenderingContextResource_WorldToViewMatrixDirty (2)

// A "rendering context" resource represents is used to pass "per rendering information" between resources.
// For example, "mesh" resources receive information specific to the current rendering via this object.
// Note: There can be multiple "rendering context" resources used in a single frame for example, when you are rendering "meshes" using different cameras and/or to different viewports.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.RenderingContextResource", Arcadia_Visuals_Implementation_RenderingContextResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_RenderingContextResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;

  void (*setTargetFrameBuffer)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Visuals_Implementation_FrameBufferResource*);
  void (*setViewToProjectionMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Math_Matrix4Real32*);
  void (*setWorldToViewMatrix)(Arcadia_Thread*, Arcadia_Visuals_Implementation_RenderingContextResource*, Arcadia_Math_Matrix4Real32*);
};

struct Arcadia_Visuals_Implementation_RenderingContextResource {
  Arcadia_Visuals_Implementation_Resource _parent;
  Arcadia_Natural8Value dirty;
  Arcadia_Math_Matrix4Real32* worldToViewMatrix;
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix;
  Arcadia_Visuals_Implementation_ConstantBufferResource* viewerConstantBuffer;
};

void
Arcadia_Visuals_Implementation_RenderingContextResource_setTargetFrameBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Visuals_Implementation_FrameBufferResource* frameBuffer
  );

void
Arcadia_Visuals_Implementation_RenderingContextResource_setViewToProjectionMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* viewToProjectionMatrix
  );

void
Arcadia_Visuals_Implementation_RenderingContextResource_setWorldToViewMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_RenderingContextResource* self,
    Arcadia_Math_Matrix4Real32* worldToViewMatrix
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_RENDERINGCONTEXTRESOURCE_H_INCLUDED
