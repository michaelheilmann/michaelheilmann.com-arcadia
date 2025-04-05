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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NATURAL8_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NATURAL8_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef uint8_t Arcadia_Natural8Value;

#define Arcadia_Natural8Value_Minimum (UINT8_C(0))

#define Arcadia_Natural8Value_Maximum (UINT8_MAX)

#define Arcadia_Natural8Value_NumberOfBytes (sizeof(uint8_t))

Arcadia_StaticAssert(Arcadia_Natural8Value_NumberOfBytes == 1, "Arcadia.Natural8Value.NumberOfBytes must be 1");

#define Arcadia_Natural8Value_NumberOfBits (Arcadia_Natural8Value_NumberOfBytes * 8)

#define Arcadia_Natural8Value_Literal(x) UINT8_C(x)

Arcadia_declareScalarType(Arcadia_Natural8);

/// The maximum number of decimal digits which can safely be stored in an Arcadia.Natural8Value.
/// The maximum vaalue of an Arcadia.Natural8Value is Arcadia.Natural8Value.Maximum = 255.
/// These are three decimal digits.
/// Hence the number decimal digitis which can safely be stored in an Arcadia.Natural8 value is 2.
#define Arcadia_Natural8Value_MaximumNumberOfDecimalDigits (2)

#endif // ARCADIA_RING1_IMPLEMENTATION_NATURAL8_H_INCLUDED
