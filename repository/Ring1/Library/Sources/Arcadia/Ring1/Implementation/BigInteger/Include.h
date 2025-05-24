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

#if !defined(ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/BigInteger/add.h"
#include "Arcadia/Ring1/Implementation/BigInteger/compareTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/divide.h"
#include "Arcadia/Ring1/Implementation/BigInteger/equalTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/getBitLength.h"
#include "Arcadia/Ring1/Implementation/BigInteger/getHigh64.h"
#include "Arcadia/Ring1/Implementation/BigInteger/greaterThan.h"
#include "Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/lowerThan.h"
#include "Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/multiply.h"
#include "Arcadia/Ring1/Implementation/BigInteger/notEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setDecimalDigits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setHexadecimalDigits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setInteger.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setNatural.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/shiftLeft.h"
#include "Arcadia/Ring1/Implementation/BigInteger/shiftRight.h"
#include "Arcadia/Ring1/Implementation/BigInteger/subtract.h"
#include "Arcadia/Ring1/Implementation/BigInteger/toInteger.h"
#include "Arcadia/Ring1/Implementation/BigInteger/toNatural.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Void.h"
typedef struct Arcadia_Process Arcadia_Process;

typedef struct Arcadia_BigInteger Arcadia_BigInteger;

typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;


typedef uint32_t Arcadia_BigInteger_Limp;
#define Arcadia_BigInteger_MaximumNumberOfLimps (SIZE_MAX / sizeof(uint32_t))
#define Arcadia_BigInteger_BytesPerLimp (sizeof(uint32_t))
#define Arcadia_BigInteger_BitsPerLimp (Arcadia_BigInteger_BytesPerLimp * 8)
#define Arcadia_BigInteger_Limp_Literal(x) UINT32_C(x)

typedef uint64_t Arcadia_BigInteger_DoubleLimp;

// This big integer type is used a) for decimal to IEEE754 conversion and b) if the Ring1 is set to arbitrary precision mode.
// This is a working horse and should be highly optimized.
struct Arcadia_BigInteger {
  Arcadia_SizeValue numberOfLimps;
  // For non-zero big integers: The most significand limp is non-zero.
  // For zero big integers: The length of the array is 0.
#if Arcadia_Configuration_BigInteger_LimpOrder == Arcadia_Configuration_BigInteger_LimpOrder_BigEndian
  // Limps in big endian order (most significand limp at index 0).
  // For [0,n) limps the magnitude is l[0] * 2^(n-1) + ... + l[0] * 2^(n-1).
  Arcadia_BigInteger_Limp* limps;
#elif Arcadia_Configuration_BigInteger_LimpOrder == Arcadia_Configuration_BigInteger_LimpOrder_LittleEndian
  // Limps in little endian order (least significand limp at index 0).
  // For [0,n) limps the magnitude is l[n-1] * 2^(n-1) + ... + l[0] * 2^0.
  Arcadia_BigInteger_Limp* limps;
#else
  #error("unknown/unsupported limp order")
#endif
  Arcadia_Integer8Value sign; // +1 or -1 if non-zero, 0 if zero.
};

Arcadia_BigInteger*
Arcadia_BigInteger_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_BigInteger_swap
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

void
Arcadia_BigInteger_copy
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

void
Arcadia_BigInteger_setZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isPositive
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isNegative
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

void
Arcadia_BigInteger_visit
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

/// @return A pointer to an "foreign value" type of name "Arcadia.ImmutableByteArray".
Arcadia_TypeValue
_Arcadia_BigIntegerValue_getType
  (
    Arcadia_Thread* thread
  );

void
Arcadia_BigInteger_toStdoutDebug
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

void
_Arcadia_BigInteger_stripLeadingZeroes
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger_Limp** limps,
    Arcadia_SizeValue* numberOfLimps
  );

#endif // ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED
