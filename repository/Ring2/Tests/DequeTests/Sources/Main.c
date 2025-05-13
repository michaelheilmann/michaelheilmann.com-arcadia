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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

// Create a deque.
// Assert the create function does not return null.
// Assert the size of the deque is zero.
static void
dequeTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Deque* a = Arcadia_Deque_create(thread);
  Arcadia_Tests_assertTrue(thread, NULL != a);
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(0) == Arcadia_Deque_getSize(thread, a));
}

// Create a deque.
//
// Assert the create function does not return null.
// Assert the size of the deque is zero.
static void
dequeTest2
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Deque* a = Arcadia_Deque_create(thread);
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(1));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(2));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(3));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(4));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(5));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&dequeTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&dequeTest2)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
