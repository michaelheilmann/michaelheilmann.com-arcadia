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

#if !defined(ARCADIA_MEDIA_VERTEXDESCRIPTOR_MODULE_H_INCLUDED)
#define ARCADIA_MEDIA_VERTEXDESCRIPTOR_MODULE_H_INCLUDED

#if !defined(ARCADIA_MEDIA_MODULE) || 1 != ARCADIA_MEDIA_MODULE
  #error("do not include directly, include `Arcadia/Media/Include.h` instead")
#endif
#if defined(ARCADIA_MEDIA_EXPORT) && 1 == ARCADIA_MEDIA_EXPORT
  #error("module internal contents exported")
#endif
#include "Arcadia/Media/VertexDescriptor.h"

Arcadia_Media_VertexDescriptor*
Arcadia_Media_VertexDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue stride,
    Arcadia_ImmutableList* vertexElementDescriptors
  );

#endif // ARCADIA_MEDIA_VERTEXDESCRIPTOR_MODULE_H_INCLUDED
