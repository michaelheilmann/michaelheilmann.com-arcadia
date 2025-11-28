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
  Arcadia_String* filePathStringSource = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, strlen(p))));
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(thread, filePathStringSource);
  Arcadia_String* filePathStringTarget = Arcadia_FilePath_toNative(thread, filePath);

  if (Arcadia_String_getNumberOfBytes(thread, filePathStringTarget) != strlen(q) + 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (memcmp(Arcadia_String_getBytes(thread, filePathStringTarget), q, strlen(q))) {
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

static void
regressionTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_String* u = Arcadia_String_createFromCxxString(thread, u8"./../../x/y");
  Arcadia_FilePath* v = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_getBytes(thread, u), Arcadia_String_getNumberOfBytes(thread, u));
  Arcadia_String* w = Arcadia_FilePath_toGeneric(thread, v);

  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(w);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t));
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
  if (!Arcadia_Tests_safeExecute(&regressionTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
