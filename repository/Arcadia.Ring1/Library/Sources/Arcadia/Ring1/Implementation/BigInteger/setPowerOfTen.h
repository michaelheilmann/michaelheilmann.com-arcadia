#if !defined(ARCADIA_RING1_BIGINTEGER_SETPOWEROFTEN_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_SETPOWEROFTEN_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Assign 10^k to this BigInteger where k is the specified Natural16 value.
void
Arcadia_BigInteger_setPowerOfTenNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Assign 10^k to this BigInteger where k is the specified Natural32 value.
void
Arcadia_BigInteger_setPowerOfTenNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Assign 10^k to this BigInteger where k is the specified Natural64 value.
void
Arcadia_BigInteger_setPowerOfTenNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Assign 10^k to this BigInteger where k is the specified Natural8 value.
void
Arcadia_BigInteger_setPowerOfTenNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_SETPOWEROFTEN_H_INCLUDED
