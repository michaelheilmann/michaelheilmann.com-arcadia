#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.h"

#include "Arcadia/Ring1/Include.h"

static const uint32_t PowersOfFiveTable[] = {
  1, // 5^0
  5, // 5^1
  25, // 5^2
  125, // 5^3
  625, // 5^4
  3125, // 5^5
  15625, // 5^6
  78125, // 5^7
  390625, // 5^8
  1953125, // 5^9
  9765625, // 5^10
  48828125, // 5^11
  244140625, // 5^12
  1220703125, // 5^13  (the next power of ten 5^14 is not representable as uint32_t anymore)
  /*6103515625*/ // 5^14
};

Arcadia_StaticAssert(UINT32_MAX >= 1220703125, "<internal error>");
#define PowersOfFiveTableSize (sizeof(PowersOfFiveTable) / sizeof(uint32_t))

void
Arcadia_BigInteger_setPowerOfFiveNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{ Arcadia_BigInteger_setPowerOfFiveNatural64(thread, self, other); }

void
Arcadia_BigInteger_setPowerOfFiveNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{ Arcadia_BigInteger_setPowerOfFiveNatural64(thread, self, other); }

void
Arcadia_BigInteger_setPowerOfFiveNatural64
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
  Arcadia_StaticAssert(14 == PowersOfFiveTableSize, "<internal error>");
  Arcadia_BigInteger_setNatural64(thread, a, Arcadia_Natural64Value_Literal(1));
  if (other > 13) {
    Arcadia_BigInteger_setNatural32(thread, b, PowersOfFiveTable[13]);
    do {
      other -= 13;
      Arcadia_BigInteger_multiply3(thread, a, a, b);
    } while (other > 13);
  }
  if (other) {
    Arcadia_BigInteger_setNatural32(thread, b, PowersOfFiveTable[other]);
    Arcadia_BigInteger_multiply3(thread, a, a, b);
  }
  Arcadia_BigInteger_swap(thread, self, a);
}

void
Arcadia_BigInteger_setPowerOfFiveNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{ Arcadia_BigInteger_setPowerOfFiveNatural64(thread, self, other); }
