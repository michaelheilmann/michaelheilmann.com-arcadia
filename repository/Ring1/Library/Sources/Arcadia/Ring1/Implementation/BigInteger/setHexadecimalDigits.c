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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setHexadecimalDigits.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_BigInteger_setHexadecimalDigits
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
      x = x - '0';
    } else if ('a' <= x && x <= 'f') {
      x = x - 'a' + 10;
    } else if ('A' <= x && x <= 'F') {
      x = x - 'A' + 10;
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_BigInteger_multiplyInteger8(thread, self, 10);
    Arcadia_BigInteger_addInteger8(thread, self, x);
  }
}
