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

#include "Arcadia/Ring2/Include.h"
#include <stdlib.h>
#include <string.h>

static void
regressionTest1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ByteArrayBuilder* encodingByteBuffer = Arcadia_ByteArrayBuilder_create(thread);
  Arcadia_Unicode_Encoder* encoder = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  Arcadia_Unicode_Encoder_encodeString(thread, encoder, Arcadia_String_createFromCxxString(thread, u8".."), encodingByteBuffer);
  
  Arcadia_String* u = Arcadia_String_createFromCxxString(thread, u8"..");
  Arcadia_String* v = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(encodingByteBuffer));

  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(v);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)u, &t));
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&regressionTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
