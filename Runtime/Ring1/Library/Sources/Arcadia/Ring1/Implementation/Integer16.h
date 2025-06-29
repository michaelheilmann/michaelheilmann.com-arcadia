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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef int16_t Arcadia_Integer16Value;

#define Arcadia_Integer16Value_Minimum (INT16_MIN)

#define Arcadia_Integer16Value_Maximum (INT16_MAX)

#define Arcadia_Integer16Value_NumberOfBytes (sizeof(int16_t))
Arcadia_StaticAssert(Arcadia_Integer16Value_NumberOfBytes == 2, "Arcadia.Integer16Value.NumberOfBytes must be 2");

#define Arcadia_Integer16Value_NumberOfBits (Arcadia_Integer16Value_NumberOfBytes * 8)

#define Arcadia_Integer16Value_Literal(x) INT16_C(x)

Arcadia_declareScalarType(Arcadia_Integer16);

/// The minimum value of an Arcadia.Integer16Value is -32 768,
/// the maximum value of an Arcadia.Integer16Value is +32 767.
/// These are five decimal digits.
/// Hence the number of decimal digits which can be safely stored in an Arcadia.Integer16Value is 4.
#define Arcadia_Integer16Value_MaximumNumberOfDecimalDigits (4)

#endif // ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED
