#if !defined(ARCADIA_RING1_BIGINTEGER_COMPARETO_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_COMPARETO_H_INCLUDED

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

// Compare this BigInteger to another BigInteger.
Arcadia_Integer8Value
Arcadia_BigInteger_compareTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

// Compare this BigInteger to the specified Integer16.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  );

// Compare this BigInteger to the specified Integer32.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  );

// Compare this BigInteger to the specified Integer64.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  );

// Compare this BigInteger to the specified Integer8.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  );

// Compare this BigInteger to the specified Natural16.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Compare this BigInteger to the specified Natural32.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Compare this BigInteger to the specified Natural64.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Compare this BigInteger to the specified Natural8.
Arcadia_Integer8Value
Arcadia_BigInteger_compareToNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_COMPARETO_H_INCLUDED
