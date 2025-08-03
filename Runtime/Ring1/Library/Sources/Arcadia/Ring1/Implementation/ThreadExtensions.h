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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Thread.h"
#include "Arcadia/Ring1/Implementation/Object.h"

static inline Arcadia_AtomValue
Arcadia_Thread_getAtomValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isAtomValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getAtomValue(&value);
}

static inline Arcadia_BooleanValue
Arcadia_Thread_getBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{ 
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isBooleanValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getBooleanValue(&value);
}

static inline Arcadia_ObjectReferenceValue
Arcadia_Thread_getObjectReferenceValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index,
    Arcadia_Type* type
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isObjectReferenceValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue objectReferenceValue = Arcadia_Value_getObjectReferenceValue(&value);
  if (type) {
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, objectReferenceValue), type)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  return objectReferenceValue;
}

static inline Arcadia_ImmutableByteArrayValue
Arcadia_Thread_getImmutableByteArrayValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isImmutableByteArrayValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getImmutableByteArrayValue(&value);
}

static inline Arcadia_ImmutableUtf8StringValue
Arcadia_Thread_getImmutableUtf8StringValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isImmutableUtf8StringValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getImmutableUtf8StringValue(&value);
}

static inline Arcadia_Integer16Value
Arcadia_Thread_getInteger16Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isInteger16Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getInteger16Value(&value);
}

static inline Arcadia_Integer16Value
Arcadia_Thread_getInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isInteger32Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getInteger32Value(&value);
}

static inline Arcadia_Integer16Value
Arcadia_Thread_getInteger64Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isInteger64Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getInteger64Value(&value);
}

static inline Arcadia_Integer8Value
Arcadia_Thread_getInteger8Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isInteger8Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getInteger8Value(&value);
}

static inline Arcadia_Natural16Value
Arcadia_Thread_getNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isNatural16Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural16Value(&value);
}


static inline Arcadia_Natural32Value
Arcadia_Thread_getNatural32Value
(
  Arcadia_Thread* thread,
  Arcadia_SizeValue index
) {
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isNatural32Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural32Value(&value);
}

static inline Arcadia_Natural64Value
Arcadia_Thread_getNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isNatural64Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural64Value(&value);
}

static inline Arcadia_Natural8Value
Arcadia_Thread_getNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isNatural8Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural8Value(&value);
}

static inline Arcadia_VoidValue
Arcadia_Thread_getVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_Thread_getValue(thread, index);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getVoidValue(&value);
}

#endif // ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED
