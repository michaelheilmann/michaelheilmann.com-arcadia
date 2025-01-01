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

// Last modified: 2024-08-27

#include <stdlib.h>

#include "R.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
    Arcadia_Process_jump(process); \
  }

// We use integers for testing.
// Append range [1,7]. Assert the range was added. Assert getSize returns 7. Assert isEmpty returns false.
// Clear the list. Assert getSize returns 0. Assert isEmpty returns true.
static void
listTest1
  (
    Arcadia_Process* process
  )
{
  R_List* l = R_List_create(process);

  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    R_List_appendInteger32Value(process, l, i);
    R_Test_assert(i == R_List_getSize(l));
  }
  R_Test_assert(7 == R_List_getSize(l));
  R_Test_assert(Arcadia_BooleanValue_False == R_List_isEmpty(l));
  for (Arcadia_Integer32Value i = 1, n = 7; i <= n; ++i) {
    R_Test_assert(i == R_List_getInteger32ValueAt(process, l, i - 1));
  }
  R_List_clear(l);
  R_Test_assert(Arcadia_SizeValue_Literal(0) == R_List_getSize(l));
  R_Test_assert(Arcadia_BooleanValue_True == R_List_isEmpty(l));
}

static bool
safeExecute
  (
    void (*f)(Arcadia_Process* process)
  )
{
  bool result = true;
  Arcadia_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)(process);
  } else {
    result = false;
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
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
