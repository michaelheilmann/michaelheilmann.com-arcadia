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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"

static void
safeAddNatural8Tests
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural8Value u, v;

  // 0 + 0 = (0, 0)
  Arcadia_safeAddNatural8Value(thread, 0, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 0 = (MAX, 0)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural8Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // 0 + MAX = (MAX, 0)
  Arcadia_safeAddNatural8Value(thread, 0, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural8Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 1 = (0, 1)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, 1, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 1 + MAX = (0, 1)
  Arcadia_safeAddNatural8Value(thread, 1, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 2 = (1, 1)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, 2, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 2 + MAX = (1, 1)
  Arcadia_safeAddNatural8Value(thread, 2, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 37 = (36, 1)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, 37, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 37 + MAX = (36, 1)
  Arcadia_safeAddNatural8Value(thread, 37, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1,1)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural8Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural8Value(thread, Arcadia_Natural8Value_Maximum, Arcadia_Natural8Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural8Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);
}

static void
safeAddNatural16Tests
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural16Value u, v;

  // 0 + 0 = (0, 0)
  Arcadia_safeAddNatural16Value(thread, 0, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 0 = (MAX, 0)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural16Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // 0 + MAX = (MAX, 0)
  Arcadia_safeAddNatural16Value(thread, 0, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural16Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 1 = (0, 1)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, 1, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 1 + MAX = (0, 1)
  Arcadia_safeAddNatural16Value(thread, 1, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 2 = (1, 1)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, 2, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 2 + MAX = (1, 1)
  Arcadia_safeAddNatural16Value(thread, 2, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 37 = (36, 1)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, 37, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 37 + MAX = (36, 1)
  Arcadia_safeAddNatural16Value(thread, 37, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural16Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural16Value(thread, Arcadia_Natural16Value_Maximum, Arcadia_Natural16Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural16Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);
}

static void
safeAddNatural32Tests
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural32Value u, v;

  // 0 + 0 = (0, 0)
  Arcadia_safeAddNatural32Value(thread, 0, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 0 = (MAX, 0)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural32Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // 0 + MAX = (MAX, 0)
  Arcadia_safeAddNatural32Value(thread, 0, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural32Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 1 = (0, 1)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, 1, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 1 + MAX = (0, 1)
  Arcadia_safeAddNatural32Value(thread, 1, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 2 = (1, 1)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, 2, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 2 + MAX = (1, 1)
  Arcadia_safeAddNatural32Value(thread, 2, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 37 = (36, 1)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, 37, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 37 + MAX = (36, 1)
  Arcadia_safeAddNatural32Value(thread, 37, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural32Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural32Value(thread, Arcadia_Natural32Value_Maximum, Arcadia_Natural32Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural32Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);
}

static void
safeAddNatural64Tests
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural64Value u, v;

  // 0 + 0 = (0, 0)
  Arcadia_safeAddNatural64Value(thread, 0, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 0 = (MAX, 0)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, 0, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural64Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // 0 + MAX = (MAX, 0)
  Arcadia_safeAddNatural64Value(thread, 0, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural64Value_Maximum);
  Arcadia_Tests_assertTrue(thread, v == 0);

  // MAX + 1 = (0, 1)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, 1, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 1 + MAX = (0, 1)
  Arcadia_safeAddNatural64Value(thread, 1, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 0);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 2 = (1, 1)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, 2, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 2 + MAX = (1, 1)
  Arcadia_safeAddNatural64Value(thread, 2, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + 37 = (36, 1)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, 37, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // 37 + MAX = (36, 1)
  Arcadia_safeAddNatural64Value(thread, 37, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == 36);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural64Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);

  // MAX + MAX = (MAX - 1, 1)
  Arcadia_safeAddNatural64Value(thread, Arcadia_Natural64Value_Maximum, Arcadia_Natural64Value_Maximum, &v, &u);
  Arcadia_Tests_assertTrue(thread, u == Arcadia_Natural64Value_Maximum - 1);
  Arcadia_Tests_assertTrue(thread, v == 1);
}

#undef Define

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&safeAddNatural16Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeAddNatural32Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeAddNatural64Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeAddNatural8Tests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
