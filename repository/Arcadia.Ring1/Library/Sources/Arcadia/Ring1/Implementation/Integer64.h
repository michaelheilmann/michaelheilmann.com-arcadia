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

// Last modified: 2024-10-27

#if !defined(R_INTEGER64VALUE_H_INCLUDED)
#define R_INTEGER64VALUE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef int64_t Arcadia_Integer64Value;

#define Arcadia_Integer64Value_Minimum (INT64_MIN)

#define Arcadia_Integer64Value_Maximum (INT64_MAX)

#define Arcadia_Integer64Value_NumberOfBytes (sizeof(int64_t))
Arcadia_StaticAssert(Arcadia_Integer64Value_NumberOfBytes == 8, "Arcadia.Integer64Value.NumberOfByes must be 8");

#define Arcadia_Integer64Value_NumberOfBits (Arcadia_Integer64Value_NumberOfBytes * 8)

#define Arcadia_Integer64Value_Literal(x) INT64_C(x)

Arcadia_declareScalarType(Arcadia_Integer64);

/// The minimum value of an Arcadia.Integer64Value is -9 223 372 036 854 775 808,
/// the maximum value of an Arcadia.Integer64Value is +9 223 372 036 854 775 807.
/// These are 19 decimal digits.
/// Hence the number of decimal digits which can be safely stored in an Arcadia.Integer64Value is 18.
#define Arcadia_Integer64Value_MaximumNumberOfDecimalDigits (18)

#endif // R_INTEGER64VALUE_H_INCLUDED
