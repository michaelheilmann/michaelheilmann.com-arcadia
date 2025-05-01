#if !defined(ARCADIA_RING1_BIGINTEGER_TOINTEGER_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_TOINTEGER_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Convert this BigInteger into a Integer16.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Integer16Value
Arcadia_BigInteger_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );
  
// Convert this BigInteger into a Integer32.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Integer32Value
Arcadia_BigInteger_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

// Convert this BigInteger into a Integer64.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails. 
Arcadia_Integer64Value
Arcadia_BigInteger_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );
  
// Convert this BigInteger into a Integer8.
// Raise an Arcadia_Status_ConversionFailed error if the conversion fails.
Arcadia_Integer8Value
Arcadia_BigInteger_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

#endif // ARCADIA_RING1_BIGINTEGER_TOINTEGER_H_INCLUDED
