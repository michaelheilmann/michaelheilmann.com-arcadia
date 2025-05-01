#if !defined(ARCADIA_RING1_BIGINTEGER_COMPAREBYMAGNITUDETO_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_COMPAREBYMAGNITUDETO_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Compare the magnitude of this BigInteger to the magnitude of another BigInteger.
Arcadia_Integer8Value
Arcadia_BigInteger_compareByMagnitudeTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

#endif // ARCADIA_RING1_BIGINTEGER_COMPAREBYMAGNITUDETO_H_INCLUDED
