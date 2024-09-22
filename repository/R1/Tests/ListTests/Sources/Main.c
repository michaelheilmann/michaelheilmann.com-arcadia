// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-08-27

#include <stdlib.h>

#include "R.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

// We use integers for testing.
// Append range [1,7]. Assert the range was added. Assert getSize returns 7. Assert isEmpty returns false.
// Clear the list. Assert getSize returns 0. Assert isEmpty returns true.
static void listTest1() {
  R_List* l = R_List_create();

  for (R_Integer32Value i = 1, n = 7; i <= n; ++i) {
    R_List_appendInteger32Value(l, i);
    R_Test_assert(i == R_List_getSize(l));
  }
  R_Test_assert(7 == R_List_getSize(l));
  R_Test_assert(R_BooleanValue_False == R_List_isEmpty(l));
  for (R_Integer32Value i = 1, n = 7; i <= n; ++i) {
    R_Test_assert(i == R_List_getInteger32ValueAt(l, i - 1));
  }
  R_List_clear(l);
  R_Test_assert(R_SizeValue_Literal(0) == R_List_getSize(l));
  R_Test_assert(R_BooleanValue_True == R_List_isEmpty(l));
}

static bool safeExecute(void (*f)()) {
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)();
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
  if (status) {
    result = false;
  }
  return result;
}

int main(int argc, char **argv) {
  if (!safeExecute(&listTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
