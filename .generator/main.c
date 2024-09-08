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

// Last modified: 2024-09-01

#include "R.h"

#include "stringbuffer.h"

#include <stdlib.h>

void test1() {
  StringBuffer* received = StringBuffer_create();
  StringBuffer* expected = StringBuffer_create();

#define TEST(RECEIVED, EXPECTED) \
  { \
    StringBuffer_clear(received); \
    StringBuffer_clear(expected); \
    StringBuffer_append_pn(received, RECEIVED, sizeof(RECEIVED) - 1); \
    StringBuffer_append_pn(expected, EXPECTED, sizeof(EXPECTED) - 1); \
    g_fs_normalize(received); \
    if (!StringBuffer_areEqual(received, expected)) { \
      R_setStatus(R_Status_ArgumentValueInvalid); /*@todo Add and use R_Status_TestFailed);*/\
      R_jump(); \
    } \
  }

  TEST("", "");
  TEST("\\", "\\");
  TEST("/", "\\");
  TEST("a\\b\\\\c/\\d", "a\\b\\c\\d");

#undef TEST
}
