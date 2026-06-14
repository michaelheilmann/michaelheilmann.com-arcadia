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
#include "Arcadia/Ring1/Implementation/Objects/ByteArray.ByteReader.h"

#include "Arcadia/Ring1/Include.h"

static void
Arcadia_ByteArray_ByteReader_construct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static void
Arcadia_ByteArray_ByteReader_initializeDispatch
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static void
Arcadia_ByteArray_ByteReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static Arcadia_BooleanValue
Arcadia_ByteArray_ByteReader_hasValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static Arcadia_BooleanValue
Arcadia_ByteArray_ByteReader_hasErrorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static Arcadia_Natural8Value
Arcadia_ByteArray_ByteReader_getValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static void
Arcadia_ByteArray_ByteReader_nextValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_ByteArray_ByteReader_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ByteArray_ByteReader_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_ByteArray_ByteReader_initializeDispatch,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ByteArray.ByteReader", Arcadia_ByteArray_ByteReader,
                         u8"Arcadia.ByteReader", Arcadia_ByteReader,
                         &_typeOperations);

static void
Arcadia_ByteArray_ByteReader_construct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ByteArray_ByteReader);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->source = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ByteArray_getType(thread));
  self->index = 0;
  Arcadia_LeaveConstructor(Arcadia_ByteArray_ByteReader);
}

static void
Arcadia_ByteArray_ByteReader_initializeDispatch
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{
  ((Arcadia_ByteReaderDispatch*)self)->getValue = (Arcadia_Natural8Value (*)(Arcadia_Thread*, Arcadia_ByteReader*)) & Arcadia_ByteArray_ByteReader_getValueImpl;
  ((Arcadia_ByteReaderDispatch*)self)->hasError = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_ByteReader*)) & Arcadia_ByteArray_ByteReader_hasErrorImpl;
  ((Arcadia_ByteReaderDispatch*)self)->hasValue = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_ByteReader*)) & Arcadia_ByteArray_ByteReader_hasValueImpl;
  ((Arcadia_ByteReaderDispatch*)self)->nextValue = (void(*)(Arcadia_Thread*, Arcadia_ByteReader*)) & Arcadia_ByteArray_ByteReader_nextValueImpl;
}

static void
Arcadia_ByteArray_ByteReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{/*Intentionally empty.*/}

static Arcadia_BooleanValue
Arcadia_ByteArray_ByteReader_hasValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{ 
  return self->index < Arcadia_ByteArray_getSize(thread,self->source);
}

static Arcadia_BooleanValue
Arcadia_ByteArray_ByteReader_hasErrorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{ return Arcadia_BooleanValue_False; }

static Arcadia_Natural8Value
Arcadia_ByteArray_ByteReader_getValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{
  if (!Arcadia_ByteReader_hasValue(thread, (Arcadia_ByteReader*)self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_ByteArray_getAt(thread, self->source, self->index);
}

static void
Arcadia_ByteArray_ByteReader_nextValueImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray_ByteReader* self
  )
{
  if (!Arcadia_ByteReader_hasValue(thread, (Arcadia_ByteReader*)self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->index++;
}

Arcadia_ByteArray_ByteReader*
Arcadia_ByteArray_ByteReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)source);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_ByteArray_ByteReader); 
}
