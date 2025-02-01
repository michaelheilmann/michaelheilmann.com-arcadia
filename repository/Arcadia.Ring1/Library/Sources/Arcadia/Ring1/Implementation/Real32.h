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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_REAL32_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_REAL32_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <float.h>

typedef float Arcadia_Real32Value;

#define Arcadia_Real32Value_Minimum (-FLOAT_MAX)

#define Arcadia_Real32Value_Maximum (+FLOAT_MAX)

#define Arcadia_Real32Value_NumberOfBytes (sizeof(float))
Arcadia_StaticAssert(Arcadia_Real32Value_NumberOfBytes == 4, "Arcadia.Real32Value.NumberOfByes must be 4");

#define Arcadia_Real32Value_NumberOfBits (Arcadia_Real32Value_NumberOfBytes * 8)

#define Arcadia_Real32Value_Literal(x) (x##f)

Rex_declareScalarType(Arcadia_Real32);

#endif // ARCADIA_RING1_IMPLEMENTATION_REAL32_H_INCLUDED
