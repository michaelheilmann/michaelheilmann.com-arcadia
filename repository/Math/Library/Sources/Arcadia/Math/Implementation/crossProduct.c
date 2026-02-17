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

#include "Arcadia/Math/Implementation/crossProduct.h"

Arcadia_Math_Vector3Real32*
Arcadia_Math_Vector3Real32_crossProduct
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector3Real32* u,
    Arcadia_Math_Vector3Real32* v
  )
{ 
  Arcadia_Real32Value values[] = 
    {
      u->elements[1] * v->elements[2] - u->elements[2] * v->elements[1],
      u->elements[2] * v->elements[0] - u->elements[0] * v->elements[2],
      u->elements[0] * v->elements[1] - u->elements[1] * v->elements[0],
    };
  return Arcadia_Math_Vector3Real32_createWithValues(thread, values);
}

Arcadia_Math_Vector3Real64*
Arcadia_Math_Vector3Real64_crossProduct
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector3Real64* u,
    Arcadia_Math_Vector3Real64* v
  )
{
  Arcadia_Real64Value values[] =
  {
    u->elements[1] * v->elements[2] - u->elements[2] * v->elements[1],
    u->elements[2] * v->elements[0] - u->elements[0] * v->elements[2],
    u->elements[0] * v->elements[1] - u->elements[1] * v->elements[0],
  };
  return Arcadia_Math_Vector3Real64_createWithValues(thread, values);
}
