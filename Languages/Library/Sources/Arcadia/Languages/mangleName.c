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

#include "Arcadia/Languages/mangleName.h"

static Arcadia_String*
on
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  static const Arcadia_Natural32Value base16DigitCodePoints[] =
  {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a', // 10
    'b',
    'c',
    'd',
    'e',
    'f', // 15
  };
  Arcadia_StringBuffer* target = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertCodePointBack(thread, target, 'x');
  const Arcadia_Natural8Value* start = bytes,
                             * end = bytes + numberOfBytes;
  const Arcadia_Natural8Value* current = start;
  while (current != end) {
    Arcadia_Natural8Value value = *current;
    // Get the lower digit.
    Arcadia_Natural8Value lower = value % 16;
    // Get the upper digit.
    Arcadia_Natural8Value upper = value / 16;

    Arcadia_StringBuffer_insertCodePointBack(thread, target, base16DigitCodePoints[upper]);
    Arcadia_StringBuffer_insertCodePointBack(thread, target, base16DigitCodePoints[lower]);

    current++;
  }
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(target));
}

static Arcadia_String*
onString
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  )
{ return on(thread, Arcadia_String_getBytes(thread, source), Arcadia_String_getNumberOfBytes(thread, source)); }

static Arcadia_String*
onStringBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* source
  )
{ return on(thread, Arcadia_StringBuffer_getBytes(thread, source), Arcadia_StringBuffer_getNumberOfBytes(thread, source)); }

Arcadia_String*
Arcadia_Languages_mangleName
  (
    Arcadia_Thread* thread,
    Arcadia_Value source
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(&source)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&source);
  if (Arcadia_Object_isInstanceOf(thread, object, _Arcadia_String_getType(thread))) {
    return onString(thread, (Arcadia_String*)object);
  } else if (Arcadia_Object_isInstanceOf(thread, object, _Arcadia_StringBuffer_getType(thread))) {
    return onStringBuffer(thread, (Arcadia_StringBuffer*)object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}
