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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"

static void
test
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_WeakReference* weakReference = 
    Arcadia_WeakReference_create
      (
        thread,
        Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"x", sizeof(u8"x") - 1))
      );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  Arcadia_Object_lock(thread, (Arcadia_Object*)weakReference);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Value v;

    v = Arcadia_WeakReference_getValue(thread, weakReference);
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isImmutableUtf8StringValue(&v));

    Arcadia_Process_runArms(Arcadia_Thread_getProcess(thread), false);

    v = Arcadia_WeakReference_getValue(thread, weakReference);
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isVoidValue(&v));

    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Object_unlock(thread, (Arcadia_Object*)weakReference);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Object_unlock(thread, (Arcadia_Object*)weakReference);
    Arcadia_Thread_jump(thread);
  }
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
