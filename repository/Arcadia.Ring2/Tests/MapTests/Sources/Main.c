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

// Last modified: 2025-02-14

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

// We use integers for testing.
// Append range [1,7]. Assert the range was added. Assert getSize returns 7. Assert isEmpty returns false.
// Clear the list. Assert getSize returns 0. Assert isEmpty returns true.
static void
mapTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Map* m = Arcadia_Map_create(thread);
  Arcadia_Value k, v;
  Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"siteAddress", sizeof(u8"siteAddress") - 1)));
  Arcadia_Value_setObjectReferenceValue(&v, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"https://michaelheilmann.com", sizeof(u8"https://michaelheilmann.com") - 1)));
  Arcadia_Map_set(thread, m, k, v);
  Arcadia_Value k2, v2;
  Arcadia_Value_setObjectReferenceValue(&k2, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"siteAddress", sizeof(u8"siteAddress") - 1)));
  v2 = Arcadia_Map_get(thread, m, k2);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&mapTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
