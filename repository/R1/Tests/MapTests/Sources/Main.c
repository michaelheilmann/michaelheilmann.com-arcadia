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
static void mapTest1() {
  R_Map* m = R_Map_create();
  R_Value k, v;
  R_Value_setObjectReferenceValue(&k, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("siteAddress", sizeof("siteAddress") - 1)));
  R_Value_setObjectReferenceValue(&v, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("https://michaelheilmann.com", sizeof("https://michaelheilmann.com") - 1)));
  R_Map_set(m, k, v);
  R_Value k2, v2;
  R_Value_setObjectReferenceValue(&k2, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("siteAddress", sizeof("siteAddress") - 1)));
  v2 = R_Map_get(m, k2);
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
  if (!safeExecute(&mapTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
