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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.h"

#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"
#include "Arcadia/Ring1/Implementation/ToReal/toReal64.h"

Arcadia_Real32Value
_toReal32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  return (Arcadia_Real32Value)Arcadia_toReal64(thread, Arcadia_ImmutableUtf8String_getBytes(thread, immutableUtf8StringValue), Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, immutableUtf8StringValue));
}

Arcadia_Real64Value
_toReal64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  return Arcadia_toReal64(thread, Arcadia_ImmutableUtf8String_getBytes(thread, immutableUtf8StringValue), Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, immutableUtf8StringValue));

}
