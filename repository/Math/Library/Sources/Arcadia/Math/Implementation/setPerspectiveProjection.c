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

#include "Arcadia/Math/Implementation/setPerspectiveProjection.h"

#include "Arcadia/Math/Implementation/trigonometry.h"

void
Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value fieldOfView,
    Arcadia_Real32Value aspectRatio,
    Arcadia_Real32Value near,
    Arcadia_Real32Value far
  )
{
  fieldOfView = Arcadia_degreesToRadiansReal32Value(thread, fieldOfView);
  Arcadia_Real32Value f = 1 / tanf(fieldOfView / 2.f);

  self->elements[0][0] = f / aspectRatio;
  self->elements[1][0] = 0.f;
  self->elements[2][0] = 0.f;
  self->elements[3][0] = 0.f;

  self->elements[0][1] = 0.f;
  self->elements[1][1] = f;
  self->elements[2][1] = 0.f;
  self->elements[3][1] = 0.f;

  self->elements[0][2] = 0.f;
  self->elements[1][2] = 0.f;
  self->elements[2][2] = (far + near) / (near - far);
  self->elements[3][2] = -1.f;

  self->elements[0][3] = 0.f;
  self->elements[1][3] = 0.f;
  self->elements[2][3] = (2.f * far * near) / (near - far);
  self->elements[3][3] = 0.f;
}

void
Arcadia_Math_Matrix4x4Real64_setPerspectiveProjection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value fieldOfView,
    Arcadia_Real64Value aspectRatio,
    Arcadia_Real64Value near,
    Arcadia_Real64Value far
  )
{
  fieldOfView = Arcadia_degreesToRadiansReal64Value(thread, fieldOfView);
  Arcadia_Real64Value f = 1 / tan(fieldOfView / 2.);

  self->elements[0][0] = f / aspectRatio;
  self->elements[1][0] = 0.;
  self->elements[2][0] = 0.;
  self->elements[3][0] = 0.;

  self->elements[0][1] = 0.;
  self->elements[1][1] = f;
  self->elements[2][1] = 0.;
  self->elements[3][1] = 0.;

  self->elements[0][2] = 0.;
  self->elements[1][2] = 0.;
  self->elements[2][2] = (far + near) / (near - far);
  self->elements[3][2] = -1.;

  self->elements[0][3] = 0.;
  self->elements[1][3] = 0.;
  self->elements[2][3] = (2.f * far * near) / (near - far);
  self->elements[3][3] = 0.;
}
