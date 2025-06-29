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

#if !defined (ARCADIA_RING2_IMPLEMENTATION_ARGUMENTSVALIDATION_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_ARGUMENTSVALIDATION_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

static inline Arcadia_ObjectReferenceValue
Arcadia_ArgumentsValidation_getObjectReferenceValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value,
    Arcadia_TypeValue type
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue objectReferenceValue = Arcadia_Value_getObjectReferenceValue(value);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, objectReferenceValue), type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return objectReferenceValue;
}

static inline Arcadia_ObjectReferenceValue
Arcadia_ArgumentsValidation_getObjectReferenceValueOrNull
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value,
    Arcadia_TypeValue type
  )
{
  if (Arcadia_Value_isVoidValue(value)) {
    return NULL;
  }
  if (!Arcadia_Value_isObjectReferenceValue(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue objectReferenceValue = Arcadia_Value_getObjectReferenceValue(value);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, objectReferenceValue), type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return objectReferenceValue;
}

static inline Arcadia_BooleanValue
Arcadia_ArgumentsValidation_getBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isBooleanValue(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue booleanValue = Arcadia_Value_getBooleanValue(value);
  return booleanValue;
}

static inline Arcadia_Integer32Value
Arcadia_ArgumentsValidation_getInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isInteger32Value(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getInteger32Value(value);
}

static inline Arcadia_Natural64Value
Arcadia_ArgumentsValidation_getNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isNatural16Value(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural16Value(value);
}

static inline Arcadia_Natural64Value
Arcadia_ArgumentsValidation_getNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isNatural32Value(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural32Value(value);
}

static inline Arcadia_Natural64Value
Arcadia_ArgumentsValidation_getNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isNatural64Value(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getNatural64Value(value);
}

static inline Arcadia_ImmutableUtf8StringValue
Arcadia_ArgumentsValidation_getImmutableUtf8StringValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (!Arcadia_Value_isImmutableUtf8StringValue(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getImmutableUtf8StringValue(value);
}

static inline Arcadia_ImmutableUtf8StringValue
Arcadia_ArgumentsValidation_getImmutableUtf8StringValueOrNull
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  if (Arcadia_Value_isVoidValue(value)) {
    return NULL;
  }
  if (!Arcadia_Value_isImmutableUtf8StringValue(value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Value_getImmutableUtf8StringValue(value);
}

#endif // ARCADIA_RING2_IMPLEMENTATION_ARGUMENTSVALIDATION_H_INCLUDED
