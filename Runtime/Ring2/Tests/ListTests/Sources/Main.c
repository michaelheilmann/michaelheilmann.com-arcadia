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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

// We use integers for testing.
// Append range [1,7]. Assert the range was added. Assert getSize returns 7. Assert isEmpty returns false.
// Clear the list. Assert getSize returns 0. Assert isEmpty returns true.
static void
listTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_List* l = Arcadia_List_create(thread);

  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    Arcadia_List_insertBackInteger32Value(thread, l, i);
    Arcadia_Tests_assertTrue(thread, i == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)l));
  }
  Arcadia_Tests_assertTrue(thread, 7 == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)l));
  Arcadia_Tests_assertTrue(thread, Arcadia_BooleanValue_False == Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)l));
  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    Arcadia_Tests_assertTrue(thread, i == Arcadia_List_getInteger32ValueAt(thread, l, i - 1));
  }
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)l);
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(0) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)l));
  Arcadia_Tests_assertTrue(thread, Arcadia_BooleanValue_True == Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)l));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&listTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
