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

#if !defined(ARCADIA_MEDIA_VERTEXELEMENTDESCRIPTOR_H_INCLUDED)
#define ARCADIA_MEDIA_VERTEXELEMENTDESCRIPTOR_H_INCLUDED

#if !defined(ARCADIA_MEDIA_MODULE) || 1 != ARCADIA_MEDIA_MODULE
  #error("do not include directly, include `Arcadia/Media/Include.h` instead")
#endif
#include "Arcadia/Media/VertexElementSemantics.h"
#include "Arcadia/Media/VertexElementSyntactics.h"

Arcadia_declareObjectType(u8"Arcadia.Media.VertexElementDescriptor", Arcadia_Media_VertexElementDescriptor,
                          Arcadia_Object);

struct Arcadia_Media_VertexElementDescriptorDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Media_VertexElementDescriptor {
  Arcadia_Object parent;
  /// The source of the vertex element.
  /// This is the index of a vertex buffer in a vertex buffer binding.
  /// @todo This is currently unused and is initialized to @a 0.
  Arcadia_Natural8Value source;
  /// The offset of the vertex element, in Bytes, from the beginning of the vertex.
  Arcadia_Natural32Value offset;
  /// The semantics of the vertex element.
  Arcadia_Media_VertexElementSemantics semantics;
  /// The syntax of the vertex element.
  Arcadia_Media_VertexElementSyntactics syntactics;
};

Arcadia_Media_VertexElementDescriptor*
Arcadia_Media_VertexElementDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value offset,
    Arcadia_Media_VertexElementSemantics semantics,
    Arcadia_Media_VertexElementSyntactics syntactics
  );

/// @brief Get the source of the vertex element.
/// @param thread A pointer to this thread.
/// @param self A pointer to this vertex element descriptor.
/// @return The source of the vertex element.
Arcadia_Natural8Value
Arcadia_Media_VertexElementDescriptor_getSource
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

/// @brief Get the offset of the vertex element.
/// @param thread A pointer to this thread.
/// @param self A pointer to this vertex element descriptor.
/// @return The offset of the vertex element.
Arcadia_Natural32Value
Arcadia_Media_VertexElementDescriptor_getOffset
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

/// @brief Get the semantics of the vertex element.
/// @param thread A pointer to this thread.
/// @param self A pointer to this vertex element descriptor.
/// @return The semantics of the vertex element.
Arcadia_Media_VertexElementSemantics
Arcadia_Media_VertexElementDescriptor_getSemantics
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

/// @brief Get the syntactics of the vertex element.
/// @param thread A pointer to this thread.
/// @param self A pointer to this vertex element descriptor.
/// @return The syntactics of the vertex element.
Arcadia_Media_VertexElementSyntactics
Arcadia_Media_VertexElementDescriptor_getSyntactics
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

/// @brief Get the size, in Bytes, of the vertex element.
/// @param thread A pointer to this thread.
/// @param self A pointer to this vertex element descriptor.
/// @return The size, in Bytes, of the vertex element.
Arcadia_Natural32Value
Arcadia_Media_VertexElementDescriptor_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

#endif // ARCADIA_MEDIA_VERTEXELEMENTDESCRIPTOR_H_INCLUDED
