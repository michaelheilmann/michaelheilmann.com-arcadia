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

#if !defined(ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Size.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Get the length, in Bits, of a big integer.
// The length, in Bits, of a big integer is given by
// n * l - m
// where
// - n is the number of limps
// - m is the number of leading zeroes of the most significand limp
// - l is the number of Bits per limp
Arcadia_SizeValue
Arcadia_BigInteger_getBitLength
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  );

#endif // ARCADIA_RING1_BIGINTEGER_GETBITLENGTH_H_INCLUDED
