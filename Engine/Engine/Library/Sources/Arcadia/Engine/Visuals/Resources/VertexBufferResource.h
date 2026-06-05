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

#if !defined(ARCADIA_ENGINE_VISUALS_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED

#include "Arcadia/Engine/Visuals/Resource.h"
#include "Arcadia/Engine/Visuals/VertexDescriptor.h"

/// @brief Flag indicating the vertex data of a vertex buffer resource is dirty.
#define Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDataDirty (1)

/// @brief Flag indicating the vertex descriptor of a vertex buffer resource is dirty.
#define Arcadia_Engine_Visuals_Implementation_VertexBufferResource_VertexDescriptorDirty (2)

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.VertexBufferResource", Arcadia_Engine_Visuals_Implementation_VertexBufferResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Engine_Visuals_Implementation_VertexBufferResourceDispatch {
  Arcadia_Engine_Visuals_Implementation_ResourceDispatch _parent;

  void (*setData)(Arcadia_Thread* thread, Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self, Arcadia_Engine_Visuals_VertexDescriptor* vertexDescriptor, Arcadia_SizeValue numberOfVertices, const void* bytes, Arcadia_SizeValue numberOfBytes);
  Arcadia_SizeValue (*getNumberOVertices)(Arcadia_Thread* thread, Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self);
};

struct Arcadia_Engine_Visuals_Implementation_VertexBufferResource {
  Arcadia_Engine_Visuals_Implementation_Resource _parent;

  Arcadia_Natural8Value dirty;

  Arcadia_Engine_Visuals_VertexDescriptor* vertexDescriptor;

  Arcadia_SizeValue numberOfVertices;

  void* bytes;
  Arcadia_SizeValue numberOfBytes;
};

void
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_setData
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self,
    Arcadia_Engine_Visuals_VertexDescriptor* vertexDescriptor,
    Arcadia_SizeValue numberOfVertices,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

Arcadia_SizeValue
Arcadia_Engine_Visuals_Implementation_VertexBufferResource_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_VertexBufferResource* self
  );

#endif // ARCADIA_ENGINE_VISUALS_RESOURCES_VERTEXBUFFERRESOURCE_H_INCLUDED
