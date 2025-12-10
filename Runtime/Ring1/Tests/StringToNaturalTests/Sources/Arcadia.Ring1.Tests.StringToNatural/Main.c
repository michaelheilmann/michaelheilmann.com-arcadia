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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"

static void
testFixtureStringToNatural64
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  if (n > SIZE_MAX - 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_ProcessStatus_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  char* q = malloc(n + 1);
  if (!q) {
    Arcadia_Thread_setStatus(thread, Arcadia_ProcessStatus_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  memcpy(q, p, n);
  q[n] = '\0';
  Arcadia_Integer64Value u;
  if (1 != sscanf(q, "%"SCNu64, &u)) {
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_ProcessStatus_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer64Value v;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    v = Arcadia_toInteger64(thread, p, n);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    Arcadia_Thread_jump(thread);
  }
  free(q);
  q = NULL;
  Arcadia_Tests_assertTrue(thread, u == v);
}

static void
stringToNatural64
  (
    Arcadia_Thread* thread
  )
{
  testFixtureStringToNatural64(thread, u8"0", sizeof(u8"0") - 1);
  testFixtureStringToNatural64(thread, u8"00", sizeof(u8"00") - 1);

  testFixtureStringToNatural64(thread, u8"+0", sizeof(u8"+0") - 1);
  testFixtureStringToNatural64(thread, u8"+00", sizeof(u8"+00") - 1);

  testFixtureStringToNatural64(thread, u8"+00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
                                sizeof(u8"+00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001") - 1);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&stringToNatural64)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
