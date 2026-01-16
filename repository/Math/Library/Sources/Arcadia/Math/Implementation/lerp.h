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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_LERP_H_INCLUDE)
#define ARCADIA_MATH_IMPLEMENTATION_LERP_H_INCLUDE

#include "Arcadia/Math/Implementation/Color4Real32.h"
#include "Arcadia/Math/Implementation/Color4Real64.h"

// @brief Lerp between two colors.
// @param start The start position.
// @param end The end position.
// @param t The interpolation factor. If outside [0,1] the function extrapolates beyond the start point or end point.
void
Arcadia_Math_Color4Real32Value_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color4Real32* self,
    Arcadia_Math_Color4Real32* other,
    Arcadia_Real32Value t,
    Arcadia_Math_Color4Real32* result
  );

// @brief Lerp between two colors.
// @param start The start position.
// @param end The end position.
// @param t The interpolation factor. If outside [0,1] the function extrapolates beyond the start point or end point.
void
Arcadia_Math_Color4Real64Value_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color4Real64* self,
    Arcadia_Math_Color4Real64* other,
    Arcadia_Real64Value t,
    Arcadia_Math_Color4Real64* result
  );

#endif // ARCADIA_MATH_IMPLEMENTATION_LERP_H_INCLUDE
