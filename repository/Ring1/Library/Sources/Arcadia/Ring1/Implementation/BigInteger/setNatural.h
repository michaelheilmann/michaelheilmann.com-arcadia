#if !defined(ARCADIA_RING1_BIGINTEGER_SETNATURAL_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_SETNATURAL_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Assign the specified Natural16 to this BigInteger.
void
Arcadia_BigInteger_setNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Assign the specified Natural32 to this BigInteger.
void
Arcadia_BigInteger_setNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Assign the specified Natural64 to this BigInteger.
void
Arcadia_BigInteger_setNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Assign the specified Natural8 to this BigInteger.
void
Arcadia_BigInteger_setNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_SETNATURAL_H_INCLUDED
