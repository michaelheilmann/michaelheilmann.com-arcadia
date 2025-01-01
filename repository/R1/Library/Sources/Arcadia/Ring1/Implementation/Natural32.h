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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NATURAL32_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NATURAL32_H_INCLUDED

#include "R/Scalar.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef uint32_t Arcadia_Natural32Value;

#define Arcadia_Natural32Value_Minimum (UINT32_C(0))

#define Arcadia_Natural32Value_Maximum (UINT32_MAX)

#define Arcadia_Natural32Value_NumberOfBytes (sizeof(uint32_t))

Arcadia_StaticAssert(Arcadia_Natural32Value_NumberOfBytes == 4, "Arcadia.Natural32Value.NumberOfBytes must be 4");

#define Arcadia_Natural32Value_NumberOfBits (Arcadia_Natural32Value_NumberOfBytes * 8)

#define Arcadia_Natural32Value_Literal(x) UINT32_C(x)

Rex_declareScalarType(Arcadia_Natural32);

#endif // ARCADIA_RING1_IMPLEMENTATION_NATURAL32_H_INCLUDED
