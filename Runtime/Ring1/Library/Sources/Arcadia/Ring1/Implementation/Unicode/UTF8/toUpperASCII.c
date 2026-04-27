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

#define ARCADIA_RING1_MODULE (1)
#include "Arcadia/Ring1/Implementation/Unicode/UTF8/toUpperASCII.h"

#include "Arcadia/Ring1/Implementation/Status.h"
#include "Arcadia/Ring1/Implementation/Thread.h"
#include <assert.h>

#include "Arcadia/Ring1/Implementation/Unicode/UTF8/mapASCIIToASCII.h"

static inline void
f
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value source,
    Arcadia_Natural8Value* target
  )
{
  if ('a' <= source && source <= 'z') {
    *target = source - 32;
  } else {
    *target = source;
  }
}

void
Arcadia_Unicode_UTF8_toUpperASCII
  (
    Arcadia_Thread* thread,
    void* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* index,
    Arcadia_SizeValue* length
  )
{ Arcadia_Unicode_UTF8_mapASCIIToASCII(thread, bytes, numberOfBytes, &f, index, length); }
