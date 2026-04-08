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

#define ARCADIA_RING2_MODULE (1)
#include "Arcadia/Ring2/Strings/UTF8ByteBufferReader.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"

/// @code
/// construct(source:ByteBuffer)
/// @endcode
static void
Arcadia_UTF8ByteBufferReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  );

static void
Arcadia_UTF8ByteBufferReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReaderDispatch* self
  );

static void
Arcadia_UTF8ByteBufferReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  );

static void
Arcadia_UTF8ByteBufferReader_nextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  );

static Arcadia_Natural32Value
Arcadia_UTF8ByteBufferReader_getCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  );

static Arcadia_BooleanValue
Arcadia_UTF8ByteBufferReader_hasCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  );

static void
Arcadia_UTF8ByteBufferReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
}

static void
Arcadia_UTF8ByteBufferReader_nextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{ _Arcadia_UTF8ArrayIterator_next(thread, &self->iterator); }

static Arcadia_Natural32Value
Arcadia_UTF8ByteBufferReader_getCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{ return _Arcadia_UTF8ArrayIterator_getCodePoint(thread, &self->iterator); }

static Arcadia_BooleanValue
Arcadia_UTF8ByteBufferReader_hasCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{ return _Arcadia_UTF8ArrayIterator_hasCodePoint(thread, &self->iterator); }

static Arcadia_Natural32Value
Arcadia_UTF8ByteBufferReader_getLengthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{ return _Arcadia_UTF8ArrayIterator_getNumberOfBytes(thread, &self->iterator); }

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_UTF8ByteBufferReader_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_UTF8ByteBufferReader_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_UTF8ByteBufferReader_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.UTF8ByteBufferReader", Arcadia_UTF8ByteBufferReader,
                         u8"Arcadia.UTF8Reader", Arcadia_UTF8Reader,
                         &_typeOperations);

void
Arcadia_UTF8ByteBufferReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReader* self
  )
{
  Arcadia_EnterConstructor(Arcadia_UTF8ByteBufferReader);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->source = (Arcadia_ByteBuffer*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ByteBuffer_getType(thread));
  _Arcadia_UTF8ArrayIterator_initialize(thread, &self->iterator, Arcadia_ByteBuffer_getBytes(thread, self->source), Arcadia_ByteBuffer_getNumberOfBytes(thread, self->source));
  Arcadia_LeaveConstructor(Arcadia_UTF8ByteBufferReader);
}

static void
Arcadia_UTF8ByteBufferReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8ByteBufferReaderDispatch* self
  )
{
  ((Arcadia_UTF8ReaderDispatch*)self)->getLength = (Arcadia_Natural32Value(*)(Arcadia_Thread*, Arcadia_UTF8Reader*)) & Arcadia_UTF8ByteBufferReader_getLengthImpl;
  ((Arcadia_UTF8ReaderDispatch*)self)->getCodePoint = (Arcadia_Natural32Value(*)(Arcadia_Thread*, Arcadia_UTF8Reader*)) & Arcadia_UTF8ByteBufferReader_getCodePointImpl;
  ((Arcadia_UTF8ReaderDispatch*)self)->hasCodePoint = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_UTF8Reader*)) & Arcadia_UTF8ByteBufferReader_hasCodePointImpl;
  ((Arcadia_UTF8ReaderDispatch*)self)->next = (void (*)(Arcadia_Thread*, Arcadia_UTF8Reader*)) & Arcadia_UTF8ByteBufferReader_nextImpl;
}

Arcadia_UTF8ByteBufferReader*
Arcadia_UTF8ByteBufferReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* source
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)source);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_UTF8ByteBufferReader);
}
