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

#if !defined(ARCADIA_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED)
#define ARCADIA_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED

#include "Arcadia/Visuals/VertexElementDescriptor.h"
#include "Arcadia/Visuals/VertexDescriptor.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.VertexDescriptorBuilder", Arcadia_Visuals_VertexDescriptorBuilder,
                          Arcadia_Object);

struct Arcadia_Visuals_VertexDescriptorBuilderDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Visuals_VertexDescriptorBuilder {
  Arcadia_Object parent;
  /// The flags.
  Arcadia_Natural8Value flags;
  /// The stride, that is, the distance, in Bytes, from the start of one vertex to the start of the next vertex.
  /// The stride is computed from the vertex element descriptors.
  Arcadia_SizeValue stride;
  /// The list of vertex element descriptors.
  Arcadia_List* vertexElementDescriptors;
};

Arcadia_Visuals_VertexDescriptorBuilder*
Arcadia_Visuals_VertexDescriptorBuilder_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_VertexDescriptor*
Arcadia_Visuals_VertexDescriptorBuilder_build
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VertexDescriptorBuilder* self
  );

#endif // ARCADIA_VISUALS_VERTEXDESCRIPTORBUILDER_H_INCLUDED
