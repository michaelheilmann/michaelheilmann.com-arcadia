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

static void
checkNormalized
  (
    Arcadia_Thread* thread,
    char const* p,
    char const* q
  )
{
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(thread, p, strlen(p));
  Arcadia_String* filePathString = Arcadia_FilePath_toNative(thread, filePath);
  if (Arcadia_String_getNumberOfBytes(thread, filePathString) != strlen(q) + 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (memcmp(Arcadia_String_getBytes(thread, filePathString), q, strlen(q))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
normalizationTests
  (
    Arcadia_Thread* thread
  )
{
  checkNormalized(thread, u8"Hello/..", ".");
  checkNormalized(thread, u8".", ".");
  checkNormalized(thread, u8"./", ".");
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&normalizationTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
