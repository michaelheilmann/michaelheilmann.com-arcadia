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
#include "Arcadia/Ring1/Implementation/Objects/UnicodeCodePointReader.h"

#include "Arcadia/Ring1/Include.h"

static void
Arcadia_UnicodeCodePointReader_constructorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  );

static void
Arcadia_UnicodeCodePointReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReaderDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_UnicodeCodePointReader_constructorImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_UnicodeCodePointReader_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.UnicodeCodePointReader", Arcadia_UnicodeCodePointReader,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_UnicodeCodePointReader_constructorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  )
{
  Arcadia_EnterConstructor(Arcadia_UnicodeCodePointReader);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_UnicodeCodePointReader);
}

static void
Arcadia_UnicodeCodePointReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReaderDispatch* self
  )
{/*Intentionally empty.*/}

void
Arcadia_UnicodeCodePointReader_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  )
{ Arcadia_VirtualCall(Arcadia_UnicodeCodePointReader, nextValue, self); }

Arcadia_Natural32Value
Arcadia_UnicodeCodePointReader_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_UnicodeCodePointReader, getValue, self); }

Arcadia_BooleanValue
Arcadia_UnicodeCodePointReader_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_UnicodeCodePointReader, hasValue, self); }

Arcadia_BooleanValue
Arcadia_UnicodeCodePointReader_hasError
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_UnicodeCodePointReader, hasError, self); }

void
Arcadia_UnicodeCodePointReader_getByteRange
  (
    Arcadia_Thread* thread,
    Arcadia_UnicodeCodePointReader* self,
    Arcadia_SizeValue* start,
    Arcadia_SizeValue* length
  )
{ Arcadia_VirtualCall(Arcadia_UnicodeCodePointReader, getByteRange, self, start, length); }
