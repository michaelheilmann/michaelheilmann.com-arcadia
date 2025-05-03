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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NATURAL64_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NATURAL64_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef uint64_t Arcadia_Natural64Value;

#define Arcadia_Natural64Value_Minimum (UINT64_C(0))

#define Arcadia_Natural64Value_Maximum (UINT64_MAX)

#define Arcadia_Natural64Value_NumberOfBytes (sizeof(uint64_t))

Arcadia_StaticAssert(Arcadia_Natural64Value_NumberOfBytes == 8, "Arcadia.Natural64Value.NumberOfBytes must be 8");

#define Arcadia_Natural64Value_NumberOfBits (Arcadia_Natural64Value_NumberOfBytes * 8)

#define Arcadia_Natural64Value_Literal(x) UINT64_C(x)

Arcadia_declareScalarType(Arcadia_Natural64);

/// The maximum number of decimal digits which can safely be stored in an Arcadia.Natural64 value.
/// The maximum value of an Arcadia.Natural64Value is Arcadia.Natural64Value.Maximum = 18 446 744 073 709 551 615.
/// These are 20 decimal digits.
/// Hence the number decimal digitis which can safely be stored in an Arcadia.Natural64 value is 19.
#define Arcadia_Natural64Value_MaximumNumberOfDecimalDigits (19)

#endif // ARCADIA_RING1_IMPLEMENTATION_NATURAL64_H_INCLUDED
