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
#include "Arcadia/Ring1/Implementation/ImmutableUTF8StringExtensions.h"

#include "Arcadia/Ring1/Implementation/Unicode/UTF8ArrayIterator.h"

Arcadia_Value
Arcadia_ImmutableUTF8String_findFirstOccurrence
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_Natural32Value codePoint
  )
{
  Arcadia_Value index = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  // It's still linear time, its fine :)
  _Arcadia_UTF8ArrayIterator  it;
  _Arcadia_UTF8ArrayIterator_initialize(thread, &it, self->bytes, self->numberOfBytes);
  Arcadia_JumpTarget jt;
  Arcadia_Thread_pushJumpTarget(thread, &jt);
  if (Arcadia_JumpTarget_save(&jt)) {
    while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it)) {
      if (codePoint == _Arcadia_UTF8ArrayIterator_getCodePoint(thread, &it)) {
        index = Arcadia_Value_makeSizeValue(_Arcadia_UTF8ArrayIterator_getCodePointIndex(thread, &it));
        break;
      }
      _Arcadia_UTF8ArrayIterator_next(thread, &it);
    }
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    return index;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    Arcadia_Thread_jump(thread);
  }
}

Arcadia_Value
Arcadia_ImmutableUTF8String_findLastOccurrence
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_Natural32Value codePoint
  )
{
  Arcadia_Value index = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  // It's still linear time, its fine :)
  _Arcadia_UTF8ArrayIterator  it;
  _Arcadia_UTF8ArrayIterator_initialize(thread, &it, self->bytes, self->numberOfBytes);
  Arcadia_JumpTarget jt;
  Arcadia_Thread_pushJumpTarget(thread, &jt);
  if (Arcadia_JumpTarget_save(&jt)) {
    while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it)) {
      if (codePoint == _Arcadia_UTF8ArrayIterator_getCodePoint(thread, &it)) {
        index = Arcadia_Value_makeSizeValue(_Arcadia_UTF8ArrayIterator_getCodePointIndex(thread, &it));
      }
      _Arcadia_UTF8ArrayIterator_next(thread, &it);
    }
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    return index;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    Arcadia_Thread_jump(thread);
  }
}

#include "Arcadia/Ring1/Implementation/ImmutableUTF8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUTF8String/type.h"

Arcadia_ImmutableUTF8String*
Arcadia_ImmutableUTF8String_createEmpty
  (
    Arcadia_Thread* thread
  )
{ 
  _ensureTypeRegistered(thread);
  Arcadia_ImmutableUTF8String* string = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUTF8String));
  string->numberOfBytes = 0;
  string->hash = 0;
  return string;

}

// start must be within the bounds of [0,n].
// in particular, if start = n then length must be 0.
Arcadia_ImmutableUTF8String*
Arcadia_ImmutableUTF8String_substring
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_SizeValue start,
    Arcadia_Value length
  )
{ 
  Arcadia_SizeValue byteIndex, byteLength;
  // It's still linear time, its fine :)
  _Arcadia_UTF8ArrayIterator  it;
  _Arcadia_UTF8ArrayIterator_initialize(thread, &it, self->bytes, self->numberOfBytes);
  Arcadia_JumpTarget jt;
  Arcadia_Thread_pushJumpTarget(thread, &jt);
  if (Arcadia_JumpTarget_save(&jt)) {
    while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it) && _Arcadia_UTF8ArrayIterator_getCodePointIndex(thread, &it) < start) {
      _Arcadia_UTF8ArrayIterator_next(thread, &it);
    }
    // CASE 1:
    // Let's assume n = 0.
    // If start is greater than 0, then this is an error.
    // CASE 2:
    // Let's assume n = 1.
    // If start is greater than 1, then this is an error.
    // CASE 3:
    // Let's assume n > 1.
    // If start is greater than n, then than this is an error.
    // Example: n = 3 then start can be 4.
 
    // So in either case, we count the number of code points visited (n) and test start > n.
    // If start > n, we have an error.
    if (start > _Arcadia_UTF8ArrayIterator_getNumberOfCodePoints(thread, &it)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }

    byteIndex = _Arcadia_UTF8ArrayIterator_getByteIndex(thread, &it);
    byteLength = 0;
    if (Arcadia_Value_isSizeValue(&length)) {
      Arcadia_SizeValue n = 0, m = Arcadia_Value_getSizeValue(&length);
      while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it) && n < m) {
        n++;
        byteLength += _Arcadia_UTF8ArrayIterator_getCodePointLength(thread, &it);
        _Arcadia_UTF8ArrayIterator_next(thread, &it);
      }
      if (n < m) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } else {
      while (_Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &it)) {
        byteLength += _Arcadia_UTF8ArrayIterator_getCodePointLength(thread, &it);
        _Arcadia_UTF8ArrayIterator_next(thread, &it);
      }
    }
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);

    _ensureTypeRegistered(thread);
    Arcadia_ImmutableUTF8String* string = NULL;
    Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUTF8String) + byteLength);
    Arcadia_Memory_copy(thread, string->bytes, self->bytes + byteIndex, byteLength);
    string->numberOfBytes = byteLength;
    string->hash = _hashUTF8(thread, string->bytes, byteLength);
    return string;

  } else {
    Arcadia_Thread_popJumpTarget(thread);
    _Arcadia_UTF8ArrayIterator_uninitialize(thread, &it);
    Arcadia_Thread_jump(thread);
  }
}
