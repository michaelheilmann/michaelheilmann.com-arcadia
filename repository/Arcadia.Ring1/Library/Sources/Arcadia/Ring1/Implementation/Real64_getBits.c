// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-27

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Real64_getBits.h"

Arcadia_Natural64Value
Arcadia_Real64Value_getBits
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value v
  )
{
  typedef union union_t {
    double f64;
    uint64_t uint64;
  } union_t;
  union_t u;
  u.f64 = v;
  return u.uint64;
}
