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

#if !defined(ARCADIA_RING1_BIGINTEGER_BIGINTEGER_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_BIGINTEGER_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

typedef struct Arcadia_Process Arcadia_Process;

typedef struct Arcadia_BigInteger Arcadia_BigInteger;

typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;


#if Arcadia_Configuration_BigInteger_LimpSize == 4

  typedef uint32_t Arcadia_BigInteger_Limp;
  #define Arcadia_BigInteger_MaximumNumberOfLimps (SIZE_MAX / sizeof(uint32_t))
  #define Arcadia_BigInteger_BytesPerLimp (sizeof(uint32_t))
  #define Arcadia_BigInteger_BitsPerLimp (Arcadia_BigInteger_BytesPerLimp * 8)
  #define Arcadia_BigInteger_Limp_Literal(x) UINT32_C(x)
  #define Arcadia_BigInteger_Limp_Minimum UINT32_(C0)
  #define Arcadia_BigInteger_Limp_Maximum UINT32_MAX

  typedef uint64_t Arcadia_BigInteger_DoubleLimp;

#elif Arcadia_Configuragion_BigInteger_LimpSize == 2

  typedef uint16_t Arcadia_BigInteger_Limp;
  #define Arcadia_BigInteger_MaximumNumberOfLimps (SIZE_MAX / sizeof(uint16_t))
  #define Arcadia_BigInteger_BytesPerLimp (sizeof(uint16_t))
  #define Arcadia_BigInteger_BitsPerLimp (Arcadia_BigInteger_BytesPerLimp * 8)
  #define Arcadia_BigInteger_Limp_Literal(x) UINT16_C(x)
  #define Arcadia_BigInteger_Limp_Minimum UINT16_(C0)
  #define Arcadia_BigInteger_Limp_Maximum UINT16_MAX

  typedef uint32_t Arcadia_BigInteger_DoubleLimp;

#elif Arcadia_Configuration_BigInteger_LimpSize == 1

  typedef uint8_t Arcadia_BigInteger_Limp;
  #define Arcadia_BigInteger_MaximumNumberOfLimps (SIZE_MAX / sizeof(uint8_t))
  #define Arcadia_BigInteger_BytesPerLimp (sizeof(uint8_t))
  #define Arcadia_BigInteger_BitsPerLimp (Arcadia_BigInteger_BytesPerLimp * 8)
  #define Arcadia_BigInteger_Limp_Literal(x) UINT8_C(x)
  #define Arcadia_BigInteger_Limp_Minimum UINT8_(C0)
  #define Arcadia_BigInteger_Limp_Maximum UINT8_MAX

  typedef uint16_t Arcadia_BigInteger_DoubleLimp;

#else

  #error("unsupported limp size")

#endif

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

#endif // ARCADIA_RING1_BIGINTEGER_BIGINTEGER_H_INCLUDED
