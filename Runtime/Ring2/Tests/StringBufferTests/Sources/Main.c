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

static void
testRemoveCodePointsFront
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_StringBuilder* a = Arcadia_StringBuilder_create(thread),
                      * b = Arcadia_StringBuilder_create(thread);

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 0);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"1");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"1");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 0);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"1");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"12");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"2");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"123");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"23");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"12345");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"45");
  Arcadia_StringBuilder_removeCodePointsFront(thread, a, 3);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));
}

static void
testRemoveCodePointsBack
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_StringBuilder* a = Arcadia_StringBuilder_create(thread),
                      * b = Arcadia_StringBuilder_create(thread);

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 0);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"1");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"1");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 0);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"1");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"12");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"1");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"123");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"12");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 1);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));

  Arcadia_StringBuilder_clear(thread, a);
  Arcadia_StringBuilder_insertBackCxxString(thread, a, u8"12345");
  Arcadia_StringBuilder_clear(thread, b);
  Arcadia_StringBuilder_insertBackCxxString(thread, b, u8"12");
  Arcadia_StringBuilder_removeCodePointsBack(thread, a, 3);
  Arcadia_Tests_assertTrue(thread, 0 == Arcadia_StringBuilder_compareTo(thread, a, Arcadia_Value_makeObjectReferenceValue(b)));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testRemoveCodePointsBack)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRemoveCodePointsFront)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
