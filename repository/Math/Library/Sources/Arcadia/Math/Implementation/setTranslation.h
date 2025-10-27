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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_SETTRANSLATION_H_INCLUDE)
#define ARCADIA_MATH_IMPLEMENTATION_SETTRANSLATION_H_INCLUDE

#include "Arcadia/Math/Implementation/Matrix4Real32.h"
#include "Arcadia/Math/Implementation/Matrix4Real64.h"

/// @brief Assign this matrix the values of a translation transformation matrix.
/// @param self A pointer to this matrix.
/// @param x The translation along the x-axis.
/// @param y The translation along the y-axis.
/// @param z The translation along the z-axis.
/// @remarks
/// A translation transformation matrix has the following form:
/// @code
/// 1 0 0 x
/// 0 1 0 y
/// 0 0 1 z
/// 0 0 0 1 
/// @endcode
void
Arcadia_Math_MatrixReal32Value_setTranslation
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value x,
    Arcadia_Real32Value y,
    Arcadia_Real32Value z
  );

/// @brief Assign this matrix the values of a translation transformation matrix.
/// @param self A pointer to this matrix.
/// @param x The translation along the x-axis.
/// @param y The translation along the y-axis.
/// @param z The translation along the z-axis.
/// @remarks
/// A translation transformation matrix has the following form:
/// @code
/// 1 0 0 x
/// 0 1 0 y
/// 0 0 1 z
/// 0 0 0 1 
/// @endcode
void
Arcadia_Math_MatrixReal64Value_setTranslation
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value x,
    Arcadia_Real64Value y,
    Arcadia_Real64Value z
  );

#endif // ARCADIA_MATH_IMPLEMENTATION_SETTRANSLATION_H_INCLUDE