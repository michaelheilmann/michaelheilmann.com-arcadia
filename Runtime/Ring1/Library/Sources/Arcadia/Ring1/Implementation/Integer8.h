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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_INTEGER8_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_INTEGER8_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef int8_t Arcadia_Integer8Value;

#define Arcadia_Integer8Value_Minimum (INT8_MIN)

#define Arcadia_Integer8Value_Maximum (INT8_MAX)

#define Arcadia_Integer8Value_NumberOfBytes (sizeof(int8_t))
Arcadia_StaticAssert(Arcadia_Integer8Value_NumberOfBytes == 1, "Arcadia.Integer8Value.NumberOfBytes must be 1");

#define Arcadia_Integer8Value_NumberOfBits (Arcadia_Integer8Value_NumberOfBytes * 8)

#define Arcadia_Integer8Value_Literal(x) INT8_C(x)

Arcadia_declareScalarType(Arcadia_Integer8);

/// The minimum value of an Arcadia.Integer8Value is -128,
/// the maximum value of an Arcadia.Integer8Value is +127.
/// These are three decimal digits.
/// Hence the number of decimal digits which can be safely stored in an Arcadia.Integer8Value is 2.
#define Arcadia_Integer8Value_MaximumNumberOfDecimalDigits (2)

#endif // ARCADIA_RING1_IMPLEMENTATION_INTEGER8_H_INCLUDED
