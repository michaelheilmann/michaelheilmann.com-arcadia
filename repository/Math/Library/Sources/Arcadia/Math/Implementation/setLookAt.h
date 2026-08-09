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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETLOOKAT_H_INCLUDED)
#define ARCADIA_MATH_IMPLEMENTATION_SETLOOKAT_H_INCLUDED

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"
#include "Arcadia/Math/Implementation/Vector3Real32.h"
#include "Arcadia/Math/Implementation/Vector3Real64.h"

/// Assign this matrix the value a of a view matrix.
/// @param source the position vector of the point at which the viewer is located
/// @param target the position vector of the point at which the viewer is looking at
/// @param uo the direction vector indicating the upward direction of the viewer
/// @remarks
/// This function constructs a view matrix <code>V</code>given
/// - the position the viewer is located at <code>source</code>,
/// - the position the viewer is looking at <code>target</code>, and
/// - the vector indicating the up direction of the viewer <code>up</code>.
/// The view matrix <code>V</code> is constructed as follows
/// Let
/// @code
/// forward := norm(target - source)
/// right := forward x norm(up)
/// up' := right x forward
/// @endcode
/// Then the view matrix <code>V</code> is given by
/// @code
/// V :=
/// | right.x    | right.y    | right.z    | 0
/// | up'.x      | up'.y      | up'.z      | 0
/// | -forward.x | -forward.y | -forward.z | 0
/// | 0          | 0          | 0          | 1
/// @endcode

// https://michaelheilmann.com/Arcadia/Math/#Arcadia_Math_Matrix*x**_setLookAt
void
Arcadia_Math_Matrix4x4Real32_setLookAt
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Math_Vector3Real32* source,
    Arcadia_Math_Vector3Real32* target,
    Arcadia_Math_Vector3Real32* up
  );

// https://michaelheilmann.com/Arcadia/Math/#Arcadia_Math_Matrix*x**_setLookAt
void
Arcadia_Math_Matrix4x4Real64_setLookAt
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Math_Vector3Real64* source,
    Arcadia_Math_Vector3Real64* target,
    Arcadia_Math_Vector3Real64* up
  );

#endif // ARCADIA_MATH_IMPLEMENTATION_SETLOOKAT_H_INCLUDED
