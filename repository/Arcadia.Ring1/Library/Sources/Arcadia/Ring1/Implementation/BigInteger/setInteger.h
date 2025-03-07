#if !defined(ARCADIA_RING1_BIGINTEGER_SETNTEGER_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_SETNTEGER_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Assign the specified Integer16 to this BigInteger.
void
Arcadia_BigInteger_setInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  );

// Assign the specified Integer32 to this BigInteger.
void
Arcadia_BigInteger_setInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  );

// Assign the specified Integer64 to this BigInteger.
void
Arcadia_BigInteger_setInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  );

// Assign the specified Integer8 to this BigInteger.
void
Arcadia_BigInteger_setInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_SETNTEGER_H_INCLUDED
