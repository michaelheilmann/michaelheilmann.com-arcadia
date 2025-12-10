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

#if !defined(ARCADIA_RING2_STRINGS_STRINGEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING2_STRINGS_STRINGEXTENSIONS_H_INCLUDED

#include "Arcadia/Ring2/Strings/String.h"
#include "Arcadia/Ring2/Strings/StringBuffer.h"

Arcadia_String*
Arcadia_String_createFromCxxInt
  (
    Arcadia_Thread* thread,
    int x
  );

int
Arcadia_String_toCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_String* self
  );

Arcadia_String*
Arcadia_String_createFromCxxString
  (
    Arcadia_Thread* thread,
    const char *x
  );

void
Arcadia_StringBuffer_insertBackCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    int x
  );

void
Arcadia_StringBuffer_insertBackCxxString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    const char *x
  );

void
Arcadia_StringBuffer_insertBackString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_String* x
  );

#endif // ARCADIA_RING2_STRINGS_STRINGEXTENSIONS_H_INCLUDED
