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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/compareTo.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_Integer8Value
Arcadia_BigInteger_compareByMagnitudeTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  if (self->numberOfLimps < other->numberOfLimps) {
    // self has the smaller magnitude and hence comes after other.
    return Arcadia_Integer8Value_Literal(-1);
  } else if (self->numberOfLimps > other->numberOfLimps) {
    // self has the greater magnitude and hence comes behind other.
    return Arcadia_Integer8Value_Literal(+1);
  } else {
  #if Arcadia_BigInteger_LimpOrder == Arcadia_BigInteger_LimpOrder_LittleEndian
    for (Arcadia_SizeValue i = self->numberOfLimps; i > 0; --i) {
      if (self->limps[i - 1] != other->limps[i - 1]) {
        if (self->limps[i - 1] < other->limps[i - 1]) {
          return Arcadia_Integer8Value_Literal(-1);
        } else if (self->limps[i - 1] > other->limps[i - 1]) {
          return Arcadia_Integer8Value_Literal(+1);
        }
      }
    }
    // Both magnitudes are zero.
    return Arcadia_Integer8Value_Literal(0);
  #elif Arcadia_BigInteger_LimpOrder == Arcadia_BigInteger_LimpOrder_BigEndian
    for (Arcadia_SizeValue i = 0; i < self->numberOfLimps; ++i) {
      if (self->limps[i] != other->limps[i]) {
        if (self->limps[i] < other->limps[i]) {
          return Arcadia_Integer8Value_Literal(-1);
        } else /*if (self->limps[i] > other->limps[i])*/ {
          return Arcadia_Integer8Value_Literal(+1);
        }
      }
    }
    // Both magnitudes are zero.
    return Arcadia_Integer8Value_Literal(0);
  #else
    #error("unknown/unsupported big integer limp order")
  #endif
  }
  return Arcadia_Integer8Value_Literal(0);
}
