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
  Arcadia_Real32Value axisValues[] = { 0.f, 1.f, 0.f };
  
  Arcadia_Math_QuaternionReal32* p = Arcadia_Math_QuaternionReal32_create(thread, 0.f, 0.f, 0.f, 0.f);
  Arcadia_Math_QuaternionReal32_setFromAxisAngle(thread, p, Arcadia_Math_Vector3Real32_createWithValues(thread, axisValues), 0.f);
  Arcadia_Math_Matrix4Real32* a = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_QuaternionReal32_toRotationMatrix(thread, p, a);
  
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
