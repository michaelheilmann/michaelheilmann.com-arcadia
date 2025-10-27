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

#include "Arcadia/Math/Implementation/setOrthographicProjection.h"

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
  )
{
  Arcadia_Real32Value a = +2.f / (right - left);
  Arcadia_Real32Value b = +2.f / (top - bottom);
  Arcadia_Real32Value c = -2.f / (far - near);
  Arcadia_Real32Value u = -(right + left) / (right - left);
  Arcadia_Real32Value v = -(top + bottom) / (top - bottom);
  Arcadia_Real32Value w = -(far + near) / (far - near);
  
  self->elements[0][0] = a;
  self->elements[1][0] = 0.f;
  self->elements[2][0] = 0.f;
  self->elements[3][0] = 0.f;

  self->elements[0][1] = 0.f;
  self->elements[1][1] = b;
  self->elements[2][1] = 0.f;
  self->elements[3][1] = 0.f;

  self->elements[0][2] = 0.f;
  self->elements[1][2] = 0.f;
  self->elements[2][2] = c;
  self->elements[3][2] = 0.f;

  self->elements[0][3] = u;
  self->elements[1][3] = v;
  self->elements[2][3] = w;
  self->elements[3][3] = 1.f;
}

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
  )
{
  Arcadia_Real64Value a = +2. / (right - left);
  Arcadia_Real64Value b = +2. / (top - bottom);
  Arcadia_Real64Value c = -2. / (far - near);
  Arcadia_Real64Value u = -(right + left) / (right - left);
  Arcadia_Real64Value v = -(top + bottom) / (top - bottom);
  Arcadia_Real64Value w = -(far + near) / (far - near);
  
  self->elements[0][0] = a;
  self->elements[1][0] = 0.;
  self->elements[2][0] = 0.;
  self->elements[3][0] = 0.;

  self->elements[0][1] = 0.;
  self->elements[1][1] = b;
  self->elements[2][1] = 0.;
  self->elements[3][1] = 0.;

  self->elements[0][2] = 0.;
  self->elements[1][2] = 0.;
  self->elements[2][2] = c;
  self->elements[3][2] = 0.;

  self->elements[0][3] = u;
  self->elements[1][3] = v;
  self->elements[2][3] = w;
  self->elements[3][3] = 1.;
}
