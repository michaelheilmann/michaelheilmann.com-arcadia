#if !defined(ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Size.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Get the length, in Bits, of a big integer.
// The length, in Bits, of a big integer is given by
// n * l - m
// where
// - n is the number of limps
// - m is the number of leading zeroes of the most significand limp
// - l is the number of Bits per limp
Arcadia_SizeValue
Arcadia_BigInteger_getBitLength
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

#endif // ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED
