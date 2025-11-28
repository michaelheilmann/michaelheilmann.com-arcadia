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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETPERSPECTIVEPROJECTION_H_INCLUDED)
#define ARCADIA_MATH_IMPLEMENTATION_SETPERSPECTIVEPROJECTION_H_INCLUDED

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"

#pragma push_macro("near")
#undef near

#pragma push_macro("far")
#undef far

/// @brief Assign this matrix the values of a perspective projection transformation matrix.
/// @param self A pointer to this matrix.
/// @param fieldOfView
/// The field of view angle, in degrees, in the y direction.
/// Must be positive.
/// @param aspectRatio
/// The aspect ratio that determines the field of view in the x-direction. The aspect ratio is the ratio of width and height.
/// Must be positive.
/// @param near The distance from the viewer to the near clippingplane.
/// Must be positive.
/// @param far The distance from the viewer to the far clipping plane.
/// Must be positive.
/// @remarks
/// An orthographic projection transformation matrix has the following form
/// @code
/// f/aspect 0                           0                               0
/// 0        f                           0                               0
/// 0        0 (near + far) / (near - far)   2 * near * far / (near - far)
/// 0        0                          -1                               0
/// @endcode
/// where
/// @code
/// f = cot(degreesToRadians(fieldOfView) / 2)
/// @endcode
/// @remarks
/// The resulting matrix sets up the axes as follows
/// - the positive z-axis points out of the screen (negative z-axis points into the screen)
/// - the positive x-axis points to the right
/// - the positive y-axis points to the top
void
Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value fieldOfView,
    Arcadia_Real32Value aspectRatio,
    Arcadia_Real32Value near,
    Arcadia_Real32Value far
  );

void
Arcadia_Math_Matrix4x4Real64_setPerspectiveProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value fieldOfView,
    Arcadia_Real64Value aspectRatio,
    Arcadia_Real64Value near,
    Arcadia_Real64Value far
  );

#pragma pop_macro("far")

#pragma pop_macro("near")

#endif // ARCADIA_MATH_IMPLEMENTATION_SETPERSPECTIVEPROJECTION_H_INCLUDED
