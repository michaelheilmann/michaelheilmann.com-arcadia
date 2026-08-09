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

#include "Arcadia.Ring1.Tests.ObjectTypeTests/MyObjectA.h"
#include "Arcadia.Ring1.Tests.ObjectTypeTests/MyObjectB.h"

static void
test
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_MyObjectB* o = Arcadia_MyObjectB_create(thread);
  Arcadia_Type const* t = Arcadia_Object_getType(thread, (Arcadia_Object*)o);
  if (t != _Arcadia_MyObjectB_getType(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
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
