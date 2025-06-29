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
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

Arcadia_ImmutableUtf8String*
_createFromBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  )
{
  Arcadia_StaticAssert(SIZE_MAX - sizeof(Arcadia_ImmutableUtf8String) >= sizeof(u8"true") - 1, "<internal error>");
  Arcadia_StaticAssert(SIZE_MAX - sizeof(Arcadia_ImmutableUtf8String) >= sizeof(u8"false") - 1, "<internal error>");
  _ensureTypeRegistered(thread);
  Arcadia_ImmutableUtf8String* string = NULL;
  if (booleanValue) {
    Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + (sizeof(u8"true") - 1));
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), string->bytes, u8"true", sizeof(u8"true") - 1);
    string->numberOfBytes = sizeof(u8"true") - 1;
  } else {
    Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + (sizeof(u8"false") - 1));
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), string->bytes, u8"false", sizeof(u8"false") - 1);
    string->numberOfBytes = sizeof(u8"false") - 1;
  }
  string->hash = _hashUtf8(thread, string->bytes, string->numberOfBytes);
  return string;
}
