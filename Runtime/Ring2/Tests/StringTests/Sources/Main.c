// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include <stdlib.h>

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

// (1) Assert two different Arcadia.String object Arcadia.Value objects a and b are considered as equal
//     - that is, Arcadia.Value.isEqualTo(&a,&b) returns Arcadia.Boolean.True - if
//     the values of their Bytes are equal. Also assert that
//     Arcadia.Value.isNotEqualTo(&a,&b) returns Arcadia.Boolean.False in that case.
// (2) Assert two different Arcadia.String object Arcadia.Vallue objects a and b are considered as NOT equal
//     - that is, Arcadia.Object.isEqualTo(a,b) returns Arcadia.Boolean.False - if
//     the values of their Bytes are NOT equal. Also assert that
//     Arcadia.Value.isNotEqualTo(&a, &b) returns Arcadia.Boolean.True in that case.
static void
testEqualsTo
  (
    Arcadia_Thread* thread
  )
{
  // (1)
  {
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"x")),
                  b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"x"));
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isEqualTo(thread, &a, &b));
    Arcadia_Tests_assertFalse(thread, Arcadia_Value_isNotEqualTo(thread, &a, &b));
  }
  // (2)
  {
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"x")),
                  b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"y"));
    Arcadia_Tests_assertFalse(thread, Arcadia_Value_isEqualTo(thread, &a, &b));
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isNotEqualTo(thread, &a, &b));
  }
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testEqualsTo)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
