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

// Convenient but not essential extensions to the functionality provided by Process.(h|c).
// Not essential but 

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESSEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESSEXTENSIONS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

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
#include "Arcadia/Ring1/Implementation/ObjectReference.h"
#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Types.h"
#include "Arcadia/Ring1/Implementation/Void.h"
#include "Arcadia/Ring1/Implementation/Value.h"

#include "Arcadia/Ring1/Implementation/Process.h"

/// @summary Push an Arcadia_Atom value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param atomValue The Arcadia_Atom value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_Thread_pushAtomValue
  (
    Arcadia_Thread* thread,
    Arcadia_AtomValue atomValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setAtomValue(&value, atomValue);
  Arcadia_Thread_pushValue(thread, &value);
}
  
/// @summary Push an Arcadia_BigIntegerValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param bigIntegerValue The Arcadia_BigIntegerValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_Thread_pushBigIntegerValue
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue bigIntegerValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setBigIntegerValue(&value, bigIntegerValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_BooleanValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param booleanValue The Arcadia_BooleanValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushBooleanValue
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setBooleanValue(&value, booleanValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_ForeignProcedureValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param foreignProcedureValue The Arcadia_ForeignProcedureValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushForeignProcedureValue
  (
    Arcadia_Thread* thread,
    Arcadia_ForeignProcedureValue foreignProcedureValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setForeignProcedureValue(&value, foreignProcedureValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_ImmutableByteArrayValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param immutableByteArrayValue The Arcadia_ImmutableByteArrayValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushImmutableByteArrayValue
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue immutableByteArrayValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setImmutableByteArrayValue(&value, immutableByteArrayValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_ImmutableUtf8StringValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param immutableUtf8StringValue The Arcadia_ImmutableUtf8StringValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushImmutableUtf8StringValue
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue immutableUtf8StringValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setImmutableUtf8StringValue(&value, immutableUtf8StringValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Integer16Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param integer16Value The Arcadia_Integer16Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushInteger16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setInteger16Value(&value, integer16Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Integer32Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param integer32Value The Arcadia_Integer32Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setInteger32Value(&value, integer32Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Integer64Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param integer64Value The Arcadia_Integer64Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushInteger64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setInteger64Value(&value, integer64Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Integer8Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param integer8Value The Arcadia_Integer8Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushInteger8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setInteger8Value(&value, integer8Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Natural16Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param natural16Value The Arcadia_Natural16Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setNatural16Value(&value, natural16Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Natural32Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param natural32Value The Arcadia_Natural32Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setNatural32Value(&value, natural32Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Natural64Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param natural64Value The Arcadia_Natural64Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setNatural64Value(&value, natural64Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Natural8Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param natural8Value The Arcadia_Natural8Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setNatural8Value(&value, natural8Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_ObjectReferenceValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param objectReferenceValue The Arcadia_ObjectReferenceValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushObjectReferenceValue
  (
    Arcadia_Thread* thread,
    Arcadia_ObjectReferenceValue objectReferenceValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setObjectReferenceValue(&value, objectReferenceValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Real32Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param real32Value The Arcadia_Real32Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushReal32alue
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setReal32Value(&value, real32Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_Real64Value value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param real64Value The Arcadia_Real64Value value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushReal64alue
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setReal64Value(&value, real64Value);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_SizeValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param sizeValue The Arcadia_SizeValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushSizeValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setSizeValue(&value, sizeValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_TypeValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param typeValue The Arcadia_TypeValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushTypeValue
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue typeValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setTypeValue(&value, typeValue);
  Arcadia_Thread_pushValue(thread, &value);
}

/// @summary Push an Arcadia_VoidValue value on the value stack of this thread.
/// @param thread A pointer to this thread.
/// @param voidValue The Arcadia_VoidValue value.
/// @error #Arcadia_Status_AllocationFailed An allocation failed.
static inline void
Arcadia_ValueStack_pushVoidValue
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  )
{
  Arcadia_Value value = Arcadia_Value_Initializer();
  Arcadia_Value_setVoidValue(&value, voidValue);
  Arcadia_Thread_pushValue(thread, &value); 
}

#endif // ARCADIA_RING1_IMPLEMENTATION_PROCESSEXTENSIONS_H_INCLUDED
