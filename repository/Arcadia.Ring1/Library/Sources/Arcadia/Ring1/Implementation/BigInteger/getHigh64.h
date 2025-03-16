#if !defined(ARCADIA_RING1_BIGINTEGER_GETHIGH64_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_GETHIGH64_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Get the most significant 64 bits.
Arcadia_Natural64Value
Arcadia_BigInteger_getHigh64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BooleanValue* truncated
  );

#endif // ARCADIA_RING1_BIGINTEGER_GETHIGH64_H_INCLUDED
