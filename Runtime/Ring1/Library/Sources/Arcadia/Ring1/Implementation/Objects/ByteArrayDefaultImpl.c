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
#include "Arcadia/Ring1/Implementation/Objects/ByteArrayDefaultImpl.h"

#include "Arcadia/Ring1/Include.h"

static void
Arcadia_ByteArrayDefaultImpl_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  );

static void
Arcadia_ByteArrayDefaultImpl_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  );

static void
Arcadia_ByteArrayDefaultImpl_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImplDispatch* self
  );

static void
Arcadia_ByteArrayDefaultImpl_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  );

static Arcadia_Natural8Value
Arcadia_ByteArrayDefaultImpl_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self,
    Arcadia_SizeValue index
  );

static Arcadia_Natural8Value const*
Arcadia_ByteArrayDefaultImpl_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  );


static Arcadia_SizeValue
Arcadia_ByteArrayDefaultImpl_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  );


static Arcadia_SizeValue
Arcadia_ByteArrayDefaultImpl_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  );

static Arcadia_BooleanValue
Arcadia_ByteArrayDefaultImpl_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_ByteArrayDefaultImpl_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_ByteArrayDefaultImpl_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ByteArrayDefaultImpl_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_ByteArrayDefaultImpl_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DefaultByteArray", Arcadia_ByteArrayDefaultImpl,
                         u8"Arcadia.ByteArray", Arcadia_ByteArray,
                         &_typeOperations);

static void
Arcadia_ByteArrayDefaultImpl_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ByteArrayDefaultImpl);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->runtimeByteArray = Arcadia_ValueStack_getRuntimeByteArrayValue(thread, 1);
  Arcadia_LeaveConstructor(Arcadia_ByteArrayDefaultImpl);
}

static void
Arcadia_ByteArrayDefaultImpl_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  ) 
{/*Intentionally empty.*/}

static void
Arcadia_ByteArrayDefaultImpl_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImplDispatch* self
  )
{
  ((Arcadia_ByteArrayDispatch*)self)->getAt = (Arcadia_Natural8Value (*)(Arcadia_Thread*, const Arcadia_ByteArray*, Arcadia_SizeValue)) & Arcadia_ByteArrayDefaultImpl_getAt;
  ((Arcadia_ByteArrayDispatch*)self)->getBytes = (Arcadia_Natural8Value const* (*)(Arcadia_Thread*, const Arcadia_ByteArray*)) & Arcadia_ByteArrayDefaultImpl_getBytes;
  ((Arcadia_ByteArrayDispatch*)self)->getNumberOfBytes = (Arcadia_SizeValue (*)(Arcadia_Thread*, const Arcadia_ByteArray*)) & Arcadia_ByteArrayDefaultImpl_getNumberOfBytes;
  ((Arcadia_ByteArrayDispatch*)self)->getSize = (Arcadia_SizeValue (*)(Arcadia_Thread*, const Arcadia_ByteArray*)) & Arcadia_ByteArrayDefaultImpl_getSize;  
  ((Arcadia_ByteArrayDispatch*)self)->isEmpty = (Arcadia_BooleanValue(*)(Arcadia_Thread*, const Arcadia_ByteArray*)) & Arcadia_ByteArrayDefaultImpl_isEmpty;
}

static void
Arcadia_ByteArrayDefaultImpl_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl* self
  )
{
  if (self->runtimeByteArray) {
    Arcadia_RuntimeByteArray_visit(thread, self->runtimeByteArray);
  }
}

Arcadia_ByteArrayDefaultImpl*
Arcadia_ByteArrayDefaultImpl_create
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArray* runtimeByteArray
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushRuntimeByteArrayValue(thread, runtimeByteArray);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_ByteArrayDefaultImpl);
}

static Arcadia_Natural8Value
Arcadia_ByteArrayDefaultImpl_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self,
    Arcadia_SizeValue index
  )
{ 
  if (index >= self->runtimeByteArray->numberOfBytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->runtimeByteArray->bytes[index];
}

static Arcadia_Natural8Value const*
Arcadia_ByteArrayDefaultImpl_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  )
{ return Arcadia_RuntimeByteArray_getBytes(thread, self->runtimeByteArray); }

static Arcadia_SizeValue
Arcadia_ByteArrayDefaultImpl_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  )
{ return Arcadia_RuntimeByteArray_getNumberOfBytes(thread, self->runtimeByteArray); }

static Arcadia_SizeValue
Arcadia_ByteArrayDefaultImpl_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  )
{ return Arcadia_RuntimeByteArray_getNumberOfBytes(thread, self->runtimeByteArray); }

static Arcadia_BooleanValue
Arcadia_ByteArrayDefaultImpl_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayDefaultImpl const* self
  )
{ return Arcadia_SizeValue_Literal(0) == Arcadia_RuntimeByteArray_getNumberOfBytes(thread, self->runtimeByteArray); }
