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
#include <math.h>

typedef float Arcadia_Real32Value;

#define Arcadia_Real32Value_Minimum (-FLOAT_MAX)

#define Arcadia_Real32Value_Maximum (+FLOAT_MAX)

#define Arcadia_Real32Value_NumberOfBytes (sizeof(float))
Arcadia_StaticAssert(Arcadia_Real32Value_NumberOfBytes == 4, "Arcadia.Real32Value.NumberOfByes must be 4");

#define Arcadia_Real32Value_NumberOfBits (Arcadia_Real32Value_NumberOfBytes * 8)

#define Arcadia_Real32Value_Literal(x) (x##f)

Rex_declareScalarType(Arcadia_Real32);

// TODO: Add to documentation.
#define Arcadia_Real32Value_NegativeInfinity (-INFINITY)

// TODO: Add to documentation.
#define Arcadia_Real32Value_PositiveInfinity (+INFINITY)

// The number of bits of the signifcand including the implicit 1 bit.
// Usually 24 = FLT_MANT_DIG.
// TODO: Add to documentation.
#define Arcadia_Real32Value_NumberOfSignificandBitsIncludingImplicit (FLT_MANT_DIG)
// The number of bits of the significand.
// Usually 23 = Arcadia_Real32Value_NumberOfSignificandBitsIncludingImplicit - 1.
// TODO: Add to documentation.
#define Arcadia_Real32Value_NumberOfExplicitSignificandBits (23)
// The shift of the bits of the significand.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the significand.
// Usually 0.
// TODO: Add to documentation.
#define Arcadia_Real32Value_SignificandBitsShift (0)

// The number of bits of the exponent.
// Usually 8.
// TODO: Add to documentation.
#define Arcadia_Real32Value_NumberOfExponentBits (8)
// The shift of the bits of the exponent.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the exponent.
// Usually 23.
// TODO: Add to documentation.
#define Arcadia_Real32Value_ExponentBitsShift Arcadia_Real32Value_NumberOfExplicitSignificandBits

// The number of bits of the sign.
// Usually 1.
// TODO: Add to documentation.
#define Arcadia_Real32Value_NumberOfSignBits (1)
// The shift of the bits of the sign.
// In other terms, if the 32 bits have indices from 0 to 31, then this is the index of the LSB of the sign.
// Usually 31.
// TODO: Add to documentation.
#define Arcadia_Real32Value_SignBitsShift (Arcadia_Real32Value_NumberOfExponentBits + Arcadia_Real32Value_NumberOfExplicitSignificandBits)

Arcadia_StaticAssert(Arcadia_Real32Value_NumberOfBits == Arcadia_Real32Value_NumberOfSignBits + Arcadia_Real32Value_NumberOfExponentBits + Arcadia_Real32Value_NumberOfExplicitSignificandBits, "unsupported floating-point format");

// The bits mask for the bits of the significand.
// TODO: Add to documentation.
#define Arcadia_Real32Value_SignificandBitsMask (((UINT32_C(1) << Arcadia_Real32Value_NumberOfExplicitSignificandBits) - 1) << Arcadia_Real32Value_SignificandBitsShift)
// The bits mask for the bits of the exponent.
// TODO: Add to documentation.
#define Arcdadia_Real32Value_ExponentBitsMask (((UINT32_C(1) << Arcadia_Real32Value_NumberOfExponentBits) - 1) << Arcadia_Real32Value_ExponentBitsShift)
// The bits mask for the bits of the sign.
// TODO: Add to documentation.
#define Arcadia_Real32Value_SignBitsMask (((UINT32_C(1) << Arcadia_Real32Value_NumberOfSignBits) - 1) << Arcadia_Real32Value_SignBitsShift)

// The minimal unbiased exponent.
#define Arcadia_Real32Value_MinimalExponent (-126)
// The maximal unbiased exponent.
#define Arcadia_Real32Value_MaximalExponent (+127)
// The exponent bias.
#define Arcadia_Real32Value_ExponentBias (+127)

#endif // ARCADIA_RING1_IMPLEMENTATION_REAL32_H_INCLUDED
