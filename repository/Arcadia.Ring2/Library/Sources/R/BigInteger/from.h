#if !defined(R_BIGINTEGER_FROM_H_INCLUDED)
#define R_BIGINTEGER_FROM_H_INCLUDED

#include "R/BigInteger/Include.h"

void
Digits_fromInteger64
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    Arcadia_Integer64Value v
  );

void
Digits_fromNatural64
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    Arcadia_Natural64Value v
  );

#endif // R_BIGINTEGER_FROM_H_INCLUDED
