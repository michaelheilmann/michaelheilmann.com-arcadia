// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.h"

#include "Arcadia/Ring1/Include.h"

static const uint32_t PowersOfTenTable[] = {
  1, // 10^0
  10, // 10^1
  100, // 10^2
  1000, // 10^3
  10000, // 10^4
  100000, // 10^5
  1000000, // 10^6
  10000000, // 10^7
  100000000, // 10^8
  1000000000, // 10^9 (the next power of ten 10^10 is not representable as uint32_t anymore)
  /*10000000000,*/ // 10^10
};

Arcadia_StaticAssert(UINT32_MAX >= 1000000000, "<error>");
#define PowersOfTenTableSize (sizeof(PowersOfTenTable) / sizeof(uint32_t))

void
Arcadia_BigInteger_setPowerOfTenNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{ Arcadia_BigInteger_setPowerOfTenNatural64(thread, self, other); }

void
Arcadia_BigInteger_setPowerOfTenNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{ Arcadia_BigInteger_setPowerOfTenNatural64(thread, self, other); }

void
Arcadia_BigInteger_setPowerOfTenNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BigInteger* a = Arcadia_BigInteger_create(thread),
                    * b = Arcadia_BigInteger_create(thread);
  Arcadia_StaticAssert(10 == PowersOfTenTableSize, "<internal error>");
  Arcadia_BigInteger_setNatural64(thread, a, Arcadia_Natural64Value_Literal(1));
  if (other > 9) {
    do {
      other -= 9;
      Arcadia_BigInteger_setNatural32(thread, b, PowersOfTenTable[9]);
      Arcadia_BigInteger_multiply3(thread, a, a, b);
    } while (other > 9);
  }
  if (other) {
    Arcadia_BigInteger_setNatural32(thread, b, PowersOfTenTable[other]);
    Arcadia_BigInteger_multiply3(thread, a, a, b);
  }
  Arcadia_BigInteger_swap(thread, self, a);
}

void
Arcadia_BigInteger_setPowerOfTenNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{ Arcadia_BigInteger_setPowerOfTenNatural64(thread, self, other); }
