#if !defined(ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/BigInteger/add.h"
#include "Arcadia/Ring1/Implementation/BigInteger/compareTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/divide.h"
#include "Arcadia/Ring1/Implementation/BigInteger/equalTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/getBitLength.h"
#include "Arcadia/Ring1/Implementation/BigInteger/getHigh64.h"
#include "Arcadia/Ring1/Implementation/BigInteger/greaterThan.h"
#include "Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/lowerThan.h"
#include "Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/multiply.h"
#include "Arcadia/Ring1/Implementation/BigInteger/notEqualTo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setDecimalDigits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setHexadecimalDigits.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setInteger.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setNatural.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.h"
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.h"
#include "Arcadia/Ring1/Implementation/BigInteger/subtract.h"
#include "Arcadia/Ring1/Implementation/BigInteger/toInteger.h"
#include "Arcadia/Ring1/Implementation/BigInteger/toNatural.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Void.h"
typedef struct Arcadia_Process Arcadia_Process;

typedef struct Arcadia_BigInteger Arcadia_BigInteger;

typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

#define Hidden(X) ___private__##X##__

typedef uint32_t Hidden(BigInteger_Limp);
typedef uint64_t Hidden(BigInteger_LongLimp);

// This big integer type is used a) for decimal to IEEE754 conversion and b) if the Ring1 is set to arbitrary precision mode.
// This is a working horse and should be highly optimized.
struct Arcadia_BigInteger {
  Arcadia_SizeValue numberOfLimps;
  Hidden(BigInteger_Limp)* limps;
  Arcadia_Integer8Value sign; // +1 or -1 if non-zero, 0 if zero.
};

Arcadia_BigInteger*
Arcadia_BigInteger_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_BigInteger_swap
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

void
Arcadia_BigInteger_copy
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

void
Arcadia_BigInteger_setZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isPositive
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isNegative
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );
  
void
Arcadia_BigInteger_visit
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  );

/// @return A pointer to an "foreign value" type of name "Arcadia.ImmutableByteArray".
Arcadia_TypeValue
_Arcadia_BigIntegerValue_getType
  (
    Arcadia_Thread* thread
  );

void
Arcadia_BigInteger_toStdoutDebug
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

#endif // ARCADIA_RING1_BIGINTEGER_INCLUDE_H_INCLUDED
