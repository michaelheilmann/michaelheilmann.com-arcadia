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

#include "R.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
    Arcadia_Process_jump(process); \
  }

static void
maximumTests
  (
    Arcadia_Process * process
  )
{
#define Do(Type, Suffix) \
  R_Test_assert(Type##Value_Maximum == R_maximum##Suffix##Value(process, Type##Value_Minimum, Type##Value_Maximum)); \
  R_Test_assert(Type##Value_Maximum == R_maximum##Suffix##Value(process, Type##Value_Maximum, Type##Value_Minimum)); \
  R_Test_assert(Type##Value_Literal(0) == R_maximum##Suffix##Value(process, Type##Value_Literal(0), Type##Value_Minimum)); \
  R_Test_assert(Type##Value_Literal(0) == R_maximum##Suffix##Value(process, Type##Value_Minimum, Type##Value_Literal(0)));

  Do(Arcadia_Integer8, Integer8);
  Do(Arcadia_Integer16, Integer16);
  Do(Arcadia_Integer32, Integer32);
  Do(Arcadia_Integer64, Integer64);

  Do(Arcadia_Natural8, Natural8);
  Do(Arcadia_Natural16, Natural16);
  Do(Arcadia_Natural32, Natural32);
  Do(Arcadia_Natural64, Natural64);

  Do(Arcadia_Size, Size);

#undef Do
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

int
main
  (
    int argc,
    char **argv
  )
{
  if (!safeExecute(&maximumTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
