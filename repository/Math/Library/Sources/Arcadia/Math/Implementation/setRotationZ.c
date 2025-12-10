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

#include "Arcadia/Math/Implementation/setRotationX.h"

#include "Arcadia/Math/Implementation/trigonometry.h"

void
Arcadia_Math_MatrixReal32Value_setRotationZ
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Real32Value a
  )
{
  a = Arcadia_degreesToRadiansReal32Value(thread, a);
  Arcadia_Real32Value c = Arcadia_cosReal32Value(thread, a);
  Arcadia_Real32Value s = Arcadia_sinReal32Value(thread, a);

  // column #1
  self->elements[0][0] = c;
  self->elements[1][0] = s;
  self->elements[2][0] = 0.f;
  self->elements[3][0] = 0.f;

  // column #2
  self->elements[0][1] = -s;
  self->elements[1][1] = c;
  self->elements[2][1] = 0.f;
  self->elements[3][1] = 0.f;

  // column #2
  self->elements[0][2] = 0.f;
  self->elements[1][2] = 0.f;
  self->elements[2][2] = 1.f;
  self->elements[3][2] = 0.f;

  // column #3
  self->elements[0][3] = 0.f;
  self->elements[1][3] = 0.f;
  self->elements[2][3] = 0.f;
  self->elements[3][3] = 1.f;
}

void
Arcadia_Math_MatrixReal64Value_setRotationZ
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real64* self,
    Arcadia_Real64Value a
  )
{
  a = Arcadia_degreesToRadiansReal64Value(thread, a);
  Arcadia_Real64Value c = Arcadia_cosReal64Value(thread, a);
  Arcadia_Real64Value s = Arcadia_sinReal64Value(thread, a);

  // column #1
  self->elements[0][0] = c;
  self->elements[1][0] = s;
  self->elements[2][0] = 0.;
  self->elements[3][0] = 0.;

  // column #2
  self->elements[0][1] = -s;
  self->elements[1][1] = c;
  self->elements[2][1] = 0.;
  self->elements[3][1] = 0.;

  // column #2
  self->elements[0][2] = 0.;
  self->elements[1][2] = 0.;
  self->elements[2][2] = 1.;
  self->elements[3][2] = 0.;

  // column #3
  self->elements[0][3] = 0.;
  self->elements[1][3] = 0.;
  self->elements[2][3] = 0.;
  self->elements[3][3] = 1.;
}
