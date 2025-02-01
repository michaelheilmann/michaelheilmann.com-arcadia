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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NATURAL16_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NATURAL16_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef uint16_t Arcadia_Natural16Value;

#define Arcadia_Natural16Value_Minimum (UINT16_C(0))

#define Arcadia_Natural16Value_Maximum (UINT16_MAX)

#define Arcadia_Natural16Value_NumberOfBytes (sizeof(uint16_t))

Arcadia_StaticAssert(Arcadia_Natural16Value_NumberOfBytes == 2, "Arcadia.Natural16Value.NumberOfBytes must be 2");

#define Arcadia_Natural16Value_NumberOfBits (Arcadia_Natural16Value_NumberOfBytes * 8)

#define Arcadia_Natural16Value_Literal(x) UINT16_C(x)

Rex_declareScalarType(Arcadia_Natural16);

#endif // ARCADIA_RING1_IMPLEMENTATION_NATURAL16_H_INCLUDED
