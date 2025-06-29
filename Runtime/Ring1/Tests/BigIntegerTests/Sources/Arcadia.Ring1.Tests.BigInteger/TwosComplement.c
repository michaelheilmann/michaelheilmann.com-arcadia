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

#include "Arcadia.Ring1.Tests.BigInteger/TwosComplement.h"

static void
test
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value value
  )
{
  Arcadia_BigInteger* x = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger* y = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, x, value);
  Arcadia_BigInteger_Limp* p = NULL;
  Arcadia_SizeValue n;
  Arcadia_JumpTarget jt;
  Arcadia_Thread_pushJumpTarget(thread, &jt);
  if (Arcadia_JumpTarget_save(&jt)) {
    Arcadia_BigInteger_toTwosComplement(thread, x, &p, &n);
    Arcadia_BigInteger_fromTwosComplement(thread, y, p, n);
    Arcadia_Tests_assertTrue(thread, Arcadia_BigInteger_equalTo(thread, x, y));
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), p);
    p = NULL;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (p) {
      Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), p);
      p = NULL;
    }
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Ring1_Tests_BigInteger_twosComplementOperations
  (
    Arcadia_Thread* thread
  )
{
  test(thread, 0);
  test(thread, -7);
  test(thread, +7);
  test(thread, Arcadia_Integer64Value_Minimum);
  test(thread, Arcadia_Integer64Value_Maximum);
}
