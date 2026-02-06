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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED)
#define ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"

#pragma push_macro("near")
#undef near

#pragma push_macro("far")
#undef far

// https://michaelheilmann.com/Arcadia/Math/#Arcadia_Math_Matrix*x**_setOrthographicProjection
void
Arcadia_Math_Matrix4x4Real32_setOrthographicProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value right,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value top,
    Arcadia_Real64Value near,
    Arcadia_Real64Value far
  );

// https://michaelheilmann.com/Arcadia/Math/#Arcadia_Math_Matrix*x**_setOrthographicProjection
void
Arcadia_Math_Matrix4x4Real64_setOrthographicProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value left,
    Arcadia_Real64Value right,
    Arcadia_Real64Value bottom,
    Arcadia_Real64Value top,
    Arcadia_Real64Value near,
    Arcadia_Real64Value far
  );

#pragma pop_macro("far")

#pragma pop_macro("near")

#endif // ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED
