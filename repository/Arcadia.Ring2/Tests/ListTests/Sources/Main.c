// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include <stdlib.h>

#include "Arcadia/Ring2/Include.h"
#include "R/R.h"
#include <stdlib.h>
#include <string.h>

// We use integers for testing.
// Append range [1,7]. Assert the range was added. Assert getSize returns 7. Assert isEmpty returns false.
// Clear the list. Assert getSize returns 0. Assert isEmpty returns true.
static void
listTest1
  (
    Arcadia_Process* process
  )
{
  Arcadia_List* l = Arcadia_List_create(process);

  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    Arcadia_List_appendInteger32Value(process, l, i);
    Arcadia_Tests_assertTrue(i == Arcadia_List_getSize(process, l));
  }
  Arcadia_Tests_assertTrue(7 == Arcadia_List_getSize(process, l));
  Arcadia_Tests_assertTrue(Arcadia_BooleanValue_False == Arcadia_List_isEmpty(process, l));
  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    Arcadia_Tests_assertTrue(i == Arcadia_List_getInteger32ValueAt(process, l, i - 1));
  }
  Arcadia_List_clear(process, l);
  Arcadia_Tests_assertTrue(Arcadia_SizeValue_Literal(0) == Arcadia_List_getSize(process, l));
  Arcadia_Tests_assertTrue(Arcadia_BooleanValue_True == Arcadia_List_isEmpty(process, l));
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
