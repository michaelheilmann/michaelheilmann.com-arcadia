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

#include "Arcadia/Ring2/Include.h"
#include "R/R.h"
#include <stdlib.h>
#include <string.h>

static void
checkNormalized
  (
    Arcadia_Process * process,
    char const* p,
    char const* q
  )
{
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(process, p, strlen(p));
  Arcadia_String* filePathString = Arcadia_FilePath_toNative(process, filePath);
  if (Arcadia_String_getNumberOfBytes(process, filePathString) != strlen(q) + 1) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (memcmp(Arcadia_String_getBytes(process, filePathString), q, strlen(q))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
}

static void
normalizationTests
  (
    Arcadia_Process* process
  )
{
  checkNormalized(process, u8"Hello/..", ".");
  checkNormalized(process, u8".", ".");
  checkNormalized(process, u8"./", ".");
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
