#if !defined(ARCADIA_RING1_BIGINTEGER_TONATURAL_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_TONATURAL_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Convert this BigInteger into a Natural16.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Natural16Value
Arcadia_BigInteger_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );
  
// Convert this BigInteger into a Natural32.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Natural32Value
Arcadia_BigInteger_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

// Convert this BigInteger into a Natural64.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails. 
Arcadia_Natural64Value
Arcadia_BigInteger_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

// Convert this BigInteger intoa  Natural64.
// If the value is negative, conversion fails.
// If the magnitude is greater than what can be stored in a Natural64, then lower order bits are dropped and *truncated is set to true.
// Otherwise *truncated is set to false.
Arcadia_Natural64Value
Arcadia_BigInteger_toNatural64WithTruncation
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self,
    Arcadia_BooleanValue* truncated
  );
  
// Convert this BigInteger into a Natural8.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Natural8Value
Arcadia_BigInteger_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

#endif // ARCADIA_RING1_BIGINTEGER_TONATURAL_H_INCLUDED
