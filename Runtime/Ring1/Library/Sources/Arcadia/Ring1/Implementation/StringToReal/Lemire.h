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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_STRINGTOREAL_LEMIRE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TOREAL_LEMIRE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Real64.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/StringToReal/Result.h"
typedef struct Arcadia_BigInteger Arcadia_BigInteger;

// For q in (0,350), we have that
//   f = (((152170 + 65536) * q ) >> 16);
// is equal to
//   floor(p) + q
// where
//   p = log(5**q)/log(2) = q * log(5)/log(2)
//
// For negative values of q in (-400,0), we have that
//   f = (((152170 + 65536) * q ) >> 16);
// is equal to
//   -ceil(p) + q
// where
//  p = log(5**-q)/log(2) = -q * log(5)/log(2)
//
// Warning:
// Undefined behavior if q not in (-400,350).
// In particular, undefined if q 0.
static inline Arcadia_Integer32Value
Arcadia_power
  (
    Arcadia_Integer32Value q
  )
{ return (((152170 + 65536) * q) >> 16) + 63; }

void
Arcadia_computeProductApproximation
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value w,
    Arcadia_Integer64Value q,
    Arcadia_Natural64Value* upper,
    Arcadia_Natural64Value* lower
  );

// Lemire's method.
void
Arcadia_lemireReal64
  (
    Arcadia_Thread* thread,
    Arcadia_ToReal64_Result* result,
    State* state
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TOREAL_LEMIRE_H_INCLUDED
