#if !defined(ARCADIA_RING1_BIGINTEGER_DIVIDE_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_DIVIDE_H_INCLUDED

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

void
Arcadia_BigInteger_divide3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b,
    Arcadia_BigInteger* quotient,
    Arcadia_BigInteger* remainder
  );

// Compute the quotient of this BigInteger and another BigInteger and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divide
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

// Compute the quotient of this BigInteger and an Integer16 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  );

// Compute the quotient of this BigInteger and an Integer32 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  );

// Compute the quotient of this BigInteger and an Integer64 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  );

// Compute the quotient of this BigInteger and an Integer8 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  );

// Compute the quotient of this BigInteger and an Natural16 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Compute the quotient of this BigInteger and an Natural32 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Compute the quotient of this BigInteger and an Natural64 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Compute the quotient of this BigInteger and an Natural8 and assign the quotient to this BigInteger.
void
Arcadia_BigInteger_divideNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_DIVIDE_H_INCLUDED
