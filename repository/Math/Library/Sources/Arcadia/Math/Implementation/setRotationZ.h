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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETROTATIONZ_H_INCLUDE)
#define ARCADIA_MATH_IMPLEMENTATION_SETROTATIONZ_H_INCLUDE

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"

/// @{
/// @brief Assign this matrix the values of a rotation transformation matrix representing a counter-clockwise rotation around the z-axis by the specified number of degrees.
/// @param self A pointer to this matrix.
/// @param a The angle of rotation, in degrees.
/// @remarks
/// A rotation transformation matrix for a counter-clockwise rotation around the z-axis by a number of degrees a has the following form:
/// @code
/// c -s  0  0 
/// s  c  0  0
/// 0  s  1  0
/// 0  0  0  1
/// @endcode
/// where
/// @code
/// c = cos(a)
/// s = sin(a)
/// @endcode
void
Arcadia_Math_MatrixReal32Value_setRotationZ
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value a
  );

void
Arcadia_Math_MatrixReal64Value_setRotationZ
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value a
  );

/// @}

#endif // ARCADIA_MATH_IMPLEMENTATION_SETROTATIONZ_H_INCLUDE