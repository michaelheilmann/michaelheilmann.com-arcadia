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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_UTILITIES_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_UTILITIES_H_INCLUDED

#include "Arcadia/Visuals/VPL/Backends/GLSL/Include.h"
#include "Arcadia/Math/Include.h"

Arcadia_Visuals_VPL_Backends_GLSL_Program*
createDefaultProgram
  (
    Arcadia_Thread* thread
  );

static inline void
writeMatrix4x4Real32ToBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue transpose,
    Arcadia_Math_Matrix4Real32 const* source,
    Arcadia_ByteBuffer* target
  )
{
  if (transpose) {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        Arcadia_ByteBuffer_append_pn(thread, target, &(source->elements[j][i]), sizeof(float));
      }
    }
  } else {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        Arcadia_ByteBuffer_append_pn(thread, target, &(source->elements[i][j]), sizeof(float));
      }
    }
  }
}


#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_UTILITIES_H_INCLUDED
