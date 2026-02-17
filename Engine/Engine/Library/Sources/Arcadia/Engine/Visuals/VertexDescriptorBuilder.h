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

#if !defined(ARCADIA_ENGINE_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Visuals/VertexElementDescriptor.h"
#include "Arcadia/Engine/Visuals/VertexDescriptor.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.VertexDescriptorBuilder", Arcadia_Engine_Visuals_VertexDescriptorBuilder,
                          Arcadia_Object);

struct Arcadia_Engine_Visuals_VertexDescriptorBuilderDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Engine_Visuals_VertexDescriptorBuilder {
  Arcadia_Object parent;
  /// The flags.
  Arcadia_Natural8Value flags;
  /// The stride, that is, the distance, in Bytes, from the start of one vertex to the start of the next vertex.
  /// The stride is computed from the vertex element descriptors.
  Arcadia_SizeValue stride;
  /// The list of vertex element descriptors.
  Arcadia_List* vertexElementDescriptors;
};

Arcadia_Engine_Visuals_VertexDescriptorBuilder*
Arcadia_Engine_Visuals_VertexDescriptorBuilder_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Engine_Visuals_VertexDescriptor*
Arcadia_Engine_Visuals_VertexDescriptorBuilder_build
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  );

#endif // ARCADIA_ENGINE_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED
