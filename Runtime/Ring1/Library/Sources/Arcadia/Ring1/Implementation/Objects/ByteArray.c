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
#include "Arcadia/Ring1/Implementation/Objects/ByteArray.h"

#include "Arcadia/Ring1/Implementation/Objects/ByteArrayDefaultImpl.h"
#include "Arcadia/Ring1/Implementation/Objects/ByteArraySliceImpl.h"
#include "Arcadia/Ring1/Include.h"

static void
Arcadia_ByteArray_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* self
  );

static void
Arcadia_ByteArray_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDispatch* self
  );

static void
Arcadia_ByteArray_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_ByteArray_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_ByteArray_destruct,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_ByteArray_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ByteArray", Arcadia_ByteArray,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ByteArray_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ByteArray);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_ByteArray);
}

static void
Arcadia_ByteArray_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_ByteArray_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* self
  )
{/*Intentionally empty.*/}

Arcadia_Natural8Value
Arcadia_ByteArray_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self,
    Arcadia_SizeValue index
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ByteArray, getAt, self, index); }

Arcadia_Natural8Value const*
Arcadia_ByteArray_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ByteArray, getBytes, self); }

Arcadia_SizeValue
Arcadia_ByteArray_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ByteArray, getNumberOfBytes, self); }

Arcadia_SizeValue
Arcadia_ByteArray_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ByteArray, getSize, self); }

Arcadia_BooleanValue
Arcadia_ByteArray_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ByteArray, isEmpty, self); }

Arcadia_ByteArray*
Arcadia_ByteArray_slice
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* self,
    Arcadia_SizeValue start,
    Arcadia_SizeValue size
  )
{ return (Arcadia_ByteArray*)Arcadia_ByteArraySliceImpl_create(thread, self, start, size); }

Arcadia_ByteArray*
Arcadia_ByteArray_createByteArray
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArray* runtimeByteArray
  )
{ return (Arcadia_ByteArray*)Arcadia_ByteArrayDefaultImpl_create(thread, runtimeByteArray); }

