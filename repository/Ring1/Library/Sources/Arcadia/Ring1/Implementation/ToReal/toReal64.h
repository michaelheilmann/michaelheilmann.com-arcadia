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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TOREAL_TOREAL64_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TOREAL_TOREAL64_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Real64.h"
#include "Arcadia/Ring1/Implementation/Size.h"
typedef struct Arcadia_BigInteger Arcadia_BigInteger;

Arcadia_Real64Value
Arcadia_toReal64
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value *p,
    Arcadia_SizeValue n
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TOREAL_TOREAL64_H_INCLUDED
