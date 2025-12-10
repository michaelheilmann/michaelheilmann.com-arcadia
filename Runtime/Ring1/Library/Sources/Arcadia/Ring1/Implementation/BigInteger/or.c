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
#include "Arcadia/Ring1/Implementation/BigInteger/or.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.h"
#include <assert.h>

void
Arcadia_BigInteger_or3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  if (a == b) {
    Arcadia_BigInteger_copy(thread, result, a);
  } else if (Arcadia_BigInteger_isZero(thread, a)) {
    Arcadia_BigInteger_copy(thread, result, b);
  } else if (Arcadia_BigInteger_isZero(thread, b)) {
    Arcadia_BigInteger_copy(thread, result, a);
  } else {
    Arcadia_BigInteger_Limp* x = NULL,
                           * y = NULL,
                           * z = NULL;
    Arcadia_SizeValue xl, yl, zl;

    Arcadia_BigInteger_Limp xextension = (a->sign < 0) ? Arcadia_BigInteger_Limp_Maximum : Arcadia_BigInteger_Limp_Literal(0);
    Arcadia_BigInteger_Limp yextension = (b->sign < 0) ? Arcadia_BigInteger_Limp_Maximum : Arcadia_BigInteger_Limp_Literal(0);

    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_BigInteger_toTwosComplement(thread, a, &x, &xl);
      Arcadia_BigInteger_toTwosComplement(thread, b, &y, &yl);
      zl = Arcadia_maximumSizeValue(thread, xl, yl);
      Arcadia_Memory_reallocateUnmanaged(thread, &z, sizeof(Arcadia_BigInteger_Limp) * zl);
      for (Arcadia_SizeValue i = 0; i < zl; ++i) {
        Arcadia_BigInteger_Limp xu = i < xl ? x[i] : xextension;
        Arcadia_BigInteger_Limp yu = i < yl ? y[i] : yextension;
        z[i] = xu | yu;
      }
      Arcadia_BigInteger_fromTwosComplement(thread, result, z, zl);
      Arcadia_Memory_deallocateUnmanaged(thread, z);
      z = NULL;
      Arcadia_Memory_deallocateUnmanaged(thread, y);
      y = NULL;
      Arcadia_Memory_deallocateUnmanaged(thread, x);
      x = NULL;
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      if (z) {
        Arcadia_Memory_deallocateUnmanaged(thread, z);
        z = NULL;
      }
      if (y) {
        Arcadia_Memory_deallocateUnmanaged(thread, y);
        y = NULL;
      }
      if (x) {
        Arcadia_Memory_deallocateUnmanaged(thread, x);
        x = NULL;
      }
      Arcadia_Thread_jump(thread);
    }
  }
}

void
Arcadia_BigInteger_or
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{ Arcadia_BigInteger_or3(thread, self, self, other); }
