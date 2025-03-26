#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/getBitLength.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_SizeValue
Arcadia_BigInteger_getBitLength
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  return self->numberOfLimps * Arcadia_Natural32Value_NumberOfBits - Arcadia_countLeadingZeroesNatural32Value(thread, self->limps[self->numberOfLimps - 1]);
}

