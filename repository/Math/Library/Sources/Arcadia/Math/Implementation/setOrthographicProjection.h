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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED)
#define ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"

#pragma push_macro("near")
#undef near

#pragma push_macro("far")
#undef far

/// @{
/// @brief Assign this matrix the values of a orthographic projection transformation matrix.
/// @param self A pointer to this matrix.
/// @param left The coordinate of the left clipping plane.
/// @param right The coordinate of the right clipping plane.
/// @param bottom The coordinate of the bottom clipping plane.
/// @param right The coordinate of the right clipping plane.
/// @param near The coordinate of the near clipping plane.
/// @param far The coordinate of the far clipping plane.
/// @remarks
/// An orthographic projection transformation matrix has the following form
/// @code
/// a 0 0 u 
/// 0 b 0 v
/// 0 0 c w
/// 0 0 0 1
/// @endcode
/// where
/// @code
/// a = 2 / (right - left)
/// b = 2 / (top - bottom)
/// c = -2 / (far - near)
///
/// u = -(right + left) / (right - left)
/// u = -(top + bottom) / (top - bottom)
/// u = -(far + near) / (far - near)
/// @endcode
/// @remarks
/// The resulting matrix sets up the axes as follows
/// - the positive z-axis points out of the screen (negative z-axis points into the screen)
/// - the positive x-axis points to the right
/// - the positive y-axis points to the top
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

/// @}

#pragma pop_macro("far")

#pragma pop_macro("near")

#endif // ARCADIA_MATH_IMPLEMENTATION_SETORTHOGRAPHICPROJECTION_H_INCLUDED
