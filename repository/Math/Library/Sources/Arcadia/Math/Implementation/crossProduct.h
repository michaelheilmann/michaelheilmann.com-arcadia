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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_CROSSPRODUCT_H_INCLUDE)
#define ARCADIA_MATH_IMPLEMENTATION_CROSSPRODUCT_H_INCLUDE

#include "Arcadia/Math/Implementation/Vector3Real32.h"
#include "Arcadia/Math/Implementation/Vector3Real64.h"

/// @{

/// @brief Compute the cross product of this vector and another vector.
/// @param u The first vector.
/// @param v The other vector.
/// @return The cross product of the vector.
/// @return A corresponding angle in degrees.
Arcadia_Math_Vector3Real32*
Arcadia_Math_Vector3Real32_crossProduct
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector3Real32* u,
    Arcadia_Math_Vector3Real32* v
  );

Arcadia_Math_Vector3Real64*
Arcadia_Math_Vector3Real64_crossProduct
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector3Real64* u,
    Arcadia_Math_Vector3Real64* v
  );

/// @}

#endif // ARCADIA_MATH_IMPLEMENTATION_CROSSPRODUCT_H_INCLUDE
