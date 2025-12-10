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

#if !defined(ARCADIA_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED)
#define ARCADIA_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED

#include "Arcadia/Visuals/VertexElementSemantics.h"
#include "Arcadia/Visuals/VertexElementSyntactics.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.VertexElementDescriptor", Arcadia_Visuals_VertexElementDescriptor,
                          Arcadia_Object);

struct Arcadia_Visuals_VertexElementDescriptorDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Visuals_VertexElementDescriptor {
  Arcadia_Object parent;
  /// The offset of the vertex element, in Bytes, from the beginning of the vertex.
  Arcadia_Natural32Value offset;
  /// The semantics of the vertex element.
  Arcadia_Visuals_VertexElementSemantics semantics;
  /// The syntax of the vertex element.
  Arcadia_Visuals_VertexElementSyntactics syntactics;
};

Arcadia_Visuals_VertexElementDescriptor*
Arcadia_Visuals_VertexElementDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value offset,
    Arcadia_Visuals_VertexElementSemantics semantics,
    Arcadia_Visuals_VertexElementSyntactics syntactics
  );

#endif // ARCADIA_VISUALS_VERTEXELEMENTDESCRIPTOR_H_INCLUDED
