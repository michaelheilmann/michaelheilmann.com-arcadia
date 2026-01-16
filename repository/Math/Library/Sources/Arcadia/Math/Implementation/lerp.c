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

#include "Arcadia/Math/Implementation/lerp.h"

void
Arcadia_Math_Color4Real32Value_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color4Real32* self,
    Arcadia_Math_Color4Real32* other,
    Arcadia_Real32Value t,
    Arcadia_Math_Color4Real32* result
  )
{
  if (t == 0.f) {
    Arcadia_Math_Color4Real32_assign(thread, result, self);
  } else if (t == 1.f) {
    Arcadia_Math_Color4Real32_assign(thread, result, other);
  } else {
    Arcadia_Real32Value s = 1.f - t;
    result->components[0] = s * (self->components[0]) + t * (other->components[0]);
    result->components[1] = s * (self->components[1]) + t * (other->components[1]);
    result->components[2] = s * (self->components[2]) + t * (other->components[2]);
    result->components[3] = s * (self->components[3]) + t * (other->components[3]);
  }  
}

void
Arcadia_Math_Color4Real64Value_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color4Real64* self,
    Arcadia_Math_Color4Real64* other,
    Arcadia_Real64Value t,
    Arcadia_Math_Color4Real64* result
  )
{
  if (t == 0.) {
    Arcadia_Math_Color4Real64_assign(thread, result, self);
  } else if (t == 1.) {
    Arcadia_Math_Color4Real64_assign(thread, result, other);
  } else {
    Arcadia_Real64Value s = 1. - t;
    result->components[0] = s * (self->components[0]) + t * (other->components[0]);
    result->components[1] = s * (self->components[1]) + t * (other->components[1]);
    result->components[2] = s * (self->components[2]) + t * (other->components[2]);
    result->components[3] = s * (self->components[3]) + t * (other->components[3]);
  }  
}
