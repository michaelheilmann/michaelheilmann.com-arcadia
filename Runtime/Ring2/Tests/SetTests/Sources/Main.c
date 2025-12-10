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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

// Add a string object x with string "x".
// Add a string object y with string "y".
static void
setTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Set* v = (Arcadia_Set*)Arcadia_HashSet_create(thread);
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"x")),
                b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"x"));
  Arcadia_Set_add(thread, v, a, NULL);
  Arcadia_Set_add(thread, v, b, NULL);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&setTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
