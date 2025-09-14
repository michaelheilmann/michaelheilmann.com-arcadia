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
  Arcadia_Deque* a = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);
  Arcadia_Tests_assertTrue(thread, NULL != a);
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(0) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));
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
  Arcadia_Value v;
  Arcadia_Deque* a = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(1));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(2));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(3));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(4));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(5));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(6));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(7));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(8));
  Arcadia_Deque_insertFront(thread, a, Arcadia_Value_makeInteger32Value(9));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 9 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(8) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 8 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(7) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 7 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(6) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 6 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(5) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 5 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(4) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 4 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(3) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 3 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(2) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 2 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(1) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));

  v = Arcadia_Deque_getFront(thread, a);
  Arcadia_Deque_removeFront(thread, a);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isInteger32Value(&v) && 1 == Arcadia_Value_getInteger32Value(&v));
  Arcadia_Tests_assertTrue(thread, Arcadia_SizeValue_Literal(0) == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)a));
}

static void
dequeTest3
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Deque* a = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);
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
