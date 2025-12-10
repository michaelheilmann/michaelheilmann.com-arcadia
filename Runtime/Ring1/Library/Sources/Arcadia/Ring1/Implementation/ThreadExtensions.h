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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Thread.h"

#include "Arcadia/Ring1/Implementation/Atoms.h"
#include "Arcadia/Ring1/Implementation/BigInteger/Include.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"
#include "Arcadia/Ring1/Implementation/ImmutableByteArray.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"
#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Object.h"
#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Types.h"
#include "Arcadia/Ring1/Implementation/Void.h"
#include "Arcadia/Ring1/Implementation/Value.h"

#define Define(Type, Suffix) \
static inline Type \
Arcadia_ValueStack_get##Suffix \
  ( \
    Arcadia_Thread* thread, \
    Arcadia_SizeValue index \
  ) \
{ \
  Arcadia_Value value = Arcadia_ValueStack_getValue(thread, index); \
  if (!Arcadia_Value_is##Suffix(&value)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  return Arcadia_Value_get##Suffix(&value); \
} \
\
static inline void \
Arcadia_ValueStack_push##Suffix \
  ( \
    Arcadia_Thread* thread, \
    Type value \
  ) \
{ \
  Arcadia_Value temporary = Arcadia_Value_make##Suffix(value); \
  Arcadia_ValueStack_pushValue(thread, &temporary); \
} \
\
static inline Arcadia_BooleanValue \
Arcadia_ValueStack_is##Suffix \
  ( \
    Arcadia_Thread* thread, \
    Arcadia_SizeValue index \
  ) \
{ \
  Arcadia_Value value = Arcadia_ValueStack_getValue(thread, index); \
  return Arcadia_Value_is##Suffix(&value); \
}

Define(Arcadia_AtomValue, AtomValue)
Define(Arcadia_BigIntegerValue, BigIntegerValue)
Define(Arcadia_BooleanValue, BooleanValue)
Define(Arcadia_ForeignProcedureValue, ForeignProcedureValue)
Define(Arcadia_ImmutableByteArrayValue, ImmutableByteArrayValue)
Define(Arcadia_ImmutableUtf8StringValue, ImmutableUtf8StringValue)
Define(Arcadia_Integer16Value, Integer16Value)
Define(Arcadia_Integer32Value, Integer32Value)
Define(Arcadia_Integer64Value, Integer64Value)
Define(Arcadia_Integer8Value, Integer8Value)
Define(Arcadia_Natural16Value, Natural16Value)
Define(Arcadia_Natural32Value, Natural32Value)
Define(Arcadia_Natural64Value, Natural64Value)
Define(Arcadia_Natural8Value, Natural8Value)
Define(Arcadia_Real32Value, Real32Value)
Define(Arcadia_Real64Value, Real64Value)
Define(Arcadia_ObjectReferenceValue, ObjectReferenceValue)
Define(Arcadia_SizeValue, SizeValue)
Define(Arcadia_TypeValue, TypeValue)
Define(Arcadia_VoidValue, VoidValue)

#undef Define

static inline Arcadia_ObjectReferenceValue
Arcadia_ValueStack_getObjectReferenceValueChecked
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index,
    Arcadia_Type* type
  )
{
  Arcadia_ObjectReferenceValue objectReferenceValue = Arcadia_ValueStack_getObjectReferenceValue(thread, index);
  if (type) {
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, objectReferenceValue), type)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  return objectReferenceValue;
}

#endif // ARCADIA_RING1_IMPLEMENTATION_THREADEXTENSIONS_H_INCLUDED
