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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Strings/StringExtensions.h"

#include <string.h>
#include <limits.h> // INT_MAX, INT_MIN

Arcadia_String*
Arcadia_String_createFromCxxInt
  (
    Arcadia_Thread* thread,
    int x
  )
{
  #if !defined(INT_MAX)
    #error("INT_MAX not defined")
  #endif
  #if !defined(INT_MIN)
    #error("INT_MIN not defined")
  #endif
  #if INT_MAX == Arcadia_Integer64Value_Maximum && INT_MIN == Arcadia_Integer64Value_Minimum
    return Arcadia_String_createFromInteger32(thread, x);
  #elif INT_MAX == Arcadia_Integer32Value_Maximum && INT_MIN == Arcadia_Integer32Value_Minimum
    return Arcadia_String_createFromInteger32(thread, x);
  #else
    #error("environment not (yet) supported");
  #endif
}

Arcadia_String*
Arcadia_String_createFromCxxString
  (
    Arcadia_Thread* thread,
    const char *x
  )
{
  if (!x) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, x, strlen(x))));
}

int
Arcadia_String_toCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_String* self
  )
{
  Arcadia_Integer64Value target = Arcadia_String_toInteger64(thread, self);
  if (target < INT_MIN || target > INT_MAX) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (int)target;
}

void
Arcadia_StringBuffer_insertBackCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    int x
  )
{
  Arcadia_String* string = Arcadia_String_createFromCxxInt(thread, x);
  Arcadia_StringBuffer_insertBack(thread, self, Arcadia_Value_makeObjectReferenceValue(string));
}

void
Arcadia_StringBuffer_insertBackCxxString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    const char *x
  )
{
  Arcadia_String* y = Arcadia_String_createFromCxxString(thread, x);
  Arcadia_StringBuffer_insertBack(thread, self, Arcadia_Value_makeObjectReferenceValue(y));
}

void
Arcadia_StringBuffer_insertBackString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_String* x
  )
{
  Arcadia_StringBuffer_insertBack(thread, self, Arcadia_Value_makeObjectReferenceValue(x));
}
