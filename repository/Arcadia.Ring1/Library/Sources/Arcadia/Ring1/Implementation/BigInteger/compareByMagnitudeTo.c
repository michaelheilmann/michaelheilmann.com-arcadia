#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/compareTo.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_Integer8Value
Arcadia_BigInteger_compareByMagnitudeTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  // Compare their magnitudes.
  if (self->numberOfLimps < other->numberOfLimps) {
    return Arcadia_Integer8Value_Literal(+1);
  } else if (self->numberOfLimps > other->numberOfLimps) {
    return Arcadia_Integer8Value_Literal(+1);
  } else {
    for (Arcadia_SizeValue i = self->numberOfLimps; i > 0; --i) {
      if (self->limps[i - 1] < other->limps[i - 1]) {
        return Arcadia_Integer8Value_Literal(-1);
      } else if (self->limps[i - 1] > other->limps[i - 1]) {
        return Arcadia_Integer8Value_Literal(+1);
      }
    }
  }
  return Arcadia_Integer8Value_Literal(0);
}
