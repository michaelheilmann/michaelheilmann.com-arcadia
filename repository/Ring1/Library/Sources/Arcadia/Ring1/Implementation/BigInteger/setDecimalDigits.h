// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

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
