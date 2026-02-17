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

#if !defined(ARCADIA_MATH_QUATERNIONREAL32_H_INCLUDED)
#define ARCADIA_MATH_QUATERNIONREAL32_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_Math_Matrix4Real32 Arcadia_Math_Matrix4Real32;
typedef struct Arcadia_Math_Vector3Real32 Arcadia_Math_Vector3Real32;

Arcadia_declareObjectType(u8"Arcadia.Math.QuaternionReal32", Arcadia_Math_QuaternionReal32,
                          u8"Arcadia.Object");

struct Arcadia_Math_QuaternionReal32Dispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Math_QuaternionReal32 {
  Arcadia_Object _parent;
  Arcadia_Real32Value elements[4];
};

/// @brief Create the quaternion (x,y,z,w).
/// @param thread A pointer to this thread.
/// @param x, y, z, w The values for the x, y, z, and w elements of the quaternion.
/// @return A pointer to the quaternion. 
Arcadia_Math_QuaternionReal32*
Arcadia_Math_QuaternionReal32_create
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value x,
    Arcadia_Real32Value y,
    Arcadia_Real32Value z,
    Arcadia_Real32Value w
  );

// @brief Create a quaternion representing the specified axis-angle rotation.
// @param axis A pointer to the axis vector.
// @param angle The angle of rotation in degrees.
// @error Arcadia_Status_ArgumentValueInvalid axis is a null pointer or is a zero vector
void
Arcadia_Math_QuaternionReal32_setFromAxisAngle
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self,
    Arcadia_Math_Vector3Real32* axis,
    Arcadia_Real32Value angle
  );
  
/// @brief Normalize this quaterion.
/// @param thread A pointer to this thread.
/// @param self A pointer to this quaternion.
/// @error #Arcadia_Status_DivisionByZero The quaternion is the zero quaterion.
void
Arcadia_Math_QuaternionReal32_normalize
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self
  );
  
/// @brief Get the length of this quaternion.
/// @param thread A pointer to this thread.
/// @param self A pointer to this quaternion.
/// @return The length of this quaternion.
Arcadia_Real32Value
Arcadia_Math_QuaternionReal32_getLength
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self
  );
 
/// @brief Get the squared length of this quaternion.
/// @param thread A pointer to this thread.
/// @param self A pointer to this quaternion.
/// @return The squared length of this quaternion.
Arcadia_Real32Value
Arcadia_Math_QuaternionReal32_getSquaredLength
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self
  );

/// @brief Assign the values of another quaternion to this quaternion.
/// @param thread A pointer to this thread.
/// @param self A pointer to this quaternion.
/// @param other A pointer to the other quaternion.
void
Arcadia_Math_QuaternionReal32_assign
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self,
    Arcadia_Math_QuaternionReal32* other
  );

void
Arcadia_Math_QuaternionReal32_toRotationMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self,
    Arcadia_Math_Matrix4Real32* target
  );

/// @brief Transform a direction vector.
/// @param thread A pointer to this thread.
/// @param self A pointer to this quaternion.
/// @param v A pointer to the vector.
void
Arcadia_Math_QuaternionReal32_transformVector
  (
    Arcadia_Thread* thread,
    Arcadia_Math_QuaternionReal32* self,
    Arcadia_Math_Vector3Real32* v
  );

#endif // ARCADIA_MATH_QUATERNIONREAL32_H_INCLUDED
