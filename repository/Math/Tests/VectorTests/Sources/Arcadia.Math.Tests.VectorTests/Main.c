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

#include "Arcadia/Math/Include.h"

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Math_Vector3Real32* u = Arcadia_Math_Vector3Real32_create(thread);
  Arcadia_Math_Vector3Real32* v = Arcadia_Math_Vector3Real32_create(thread);
  Arcadia_Value t;
  t = Arcadia_Value_makeObjectReferenceValue(v);

if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t)) {

  }
  if (Arcadia_Object_isNotEqualTo(thread, (Arcadia_Object*)u, &t)) {

  }
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
