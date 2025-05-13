#if !defined(ARCADIA_RING1_BIGINTEGER_SETDECIMALDIGITS_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_SETDECIMALDIGITS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// @brief Assign a big integer a sequence of decimal digits.
// @param p A pointer to an array of UTF8 symbols. The supported symbols are '0' through '9'.
// @param n The number of UTF8 symbols in the array pointed to by @a p.
void
Arcadia_BigInteger_setDecimalDigits
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  );

#endif // ARCADIA_RING1_BIGINTEGER_SETDECIMALDIGITS_H_INCLUDED
