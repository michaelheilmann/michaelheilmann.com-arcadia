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

#include "Tools/RyuLookupTablesGenerator/Common.h"

#include "Arcadia/Ring2/Include.h"

#include <stdio.h>

void
Arcadia_printInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32
  )
{
  Arcadia_printImmutableUtf8String(thread, Arcadia_ImmutableUtf8String_createFromInteger32(thread, integer32));
}

void
Arcadia_printImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* string
  )
{
  fwrite(Arcadia_ImmutableUtf8String_getBytes(thread, string), 1, Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, string), stdout);
}

void
Arcadia_printNewline
  (
    Arcadia_Thread* thread
  )
{
  static const uint8_t v[] = u8"\n";
  fwrite(v, 1, sizeof(v) - 1, stdout);
}

void
Arcadia_printStringBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* stringBuffer
  )
{
  fwrite(Arcadia_StringBuffer_getBytes(thread, stringBuffer), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, stringBuffer), stdout);
}
