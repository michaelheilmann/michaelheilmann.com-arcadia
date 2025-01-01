#if !defined(R_BIGINTEGER_ADD_H_INCLUDED)
#define R_BIGINTEGER_ADD_H_INCLUDED

#include "R/BigInteger/Include.h"

void
Digits_add
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    R_BigInteger* a,
    R_BigInteger* b
  );

void
Digits_subtract
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    R_BigInteger* a,
    R_BigInteger* b
  );

#endif // R_BIGINTEGER_ADD_H_INCLUDED
