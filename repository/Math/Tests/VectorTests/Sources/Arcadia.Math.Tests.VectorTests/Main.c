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
  Arcadia_Math_Vector3Real32 *u, *v, *w;
  Arcadia_Value t;

  // u must be equal to itself.
  u = Arcadia_Math_Vector3Real32_create(thread);
  t = Arcadia_Value_makeObjectReferenceValue(u);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t));

  // u and v are created with the same component values => u and v must be equal..
  v = Arcadia_Math_Vector3Real32_create(thread);
  t = Arcadia_Value_makeObjectReferenceValue(v);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t));

  // w is clone of u => w and u must be equal.
  w = (Arcadia_Math_Vector3Real32*)Arcadia_Object_clone(thread, (Arcadia_Object*)u);
  t = Arcadia_Value_makeObjectReferenceValue(w);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t));
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
