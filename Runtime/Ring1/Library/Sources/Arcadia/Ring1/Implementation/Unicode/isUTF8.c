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
#include "Arcadia/Ring1/Implementation/Unicode/isUTF8.h"

#include "Arcadia/Ring1/Implementation/Unicode/UTF8ArrayIterator.h"

Arcadia_BooleanValue
Arcadia_Unicode_isUTF8
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  )
{
  _Arcadia_UTF8ArrayIterator it;
  _Arcadia_UTF8ArrayIterator_initialize(thread, &it, bytes, numberOfBytes);
  Arcadia_JumpTarget jt;
  Arcadia_Thread_pushJumpTarget(thread, &jt);
  if (Arcadia_JumpTarget_save(&jt)) {
    while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it)) {
      _Arcadia_UTF8ArrayIterator_next(thread, &it);
    }
    Arcadia_BooleanValue result = !_Arcadia_UTF8ArrayIterator_hasError(thread, &it);
    if (numberOfSymbols) *numberOfSymbols = _Arcadia_UTF8ArrayIterator_getCodePointIndex(thread, &it);
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    return result;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    Arcadia_Thread_jump(thread);
  }
}
