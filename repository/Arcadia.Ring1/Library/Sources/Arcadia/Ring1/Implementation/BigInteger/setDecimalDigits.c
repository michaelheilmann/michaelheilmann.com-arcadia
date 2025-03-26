#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setDecimalDigits.h"

#include "Arcadia/Ring1/Include.h"


void
Arcadia_BigInteger_setDecimalDigits
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  Arcadia_BigInteger_setZero(thread, self);
  for (Arcadia_SizeValue i = Arcadia_SizeValue_Literal(0); i < n; ++i) {
    Arcadia_Natural8Value x = p[i];
    if ('0' <= x && x <= '9') {
      x = x - (Arcadia_Natural8Value)'0';
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_BigInteger_multiplyNatural8(thread, self, 10);
    Arcadia_BigInteger_addNatural8(thread, self, x);
  }
}
