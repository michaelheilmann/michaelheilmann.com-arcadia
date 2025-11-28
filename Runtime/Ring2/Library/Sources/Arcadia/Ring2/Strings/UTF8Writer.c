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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Strings/UTF8Writer.h"

static void
Arcadia_UTF8Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_UTF8Writer_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.UTF8Writer", Arcadia_UTF8Writer,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_UTF8Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_UTF8Writer_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->writeBytes = NULL;
  self->writeCodePoints = NULL;
  self->writeImmutableUTF8String = NULL;
  self->writeString = NULL;
  self->flush = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_UTF8Writer_writeBytes
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  self->writeBytes(thread, self, bytes, numberOfBytes);
}

void
Arcadia_UTF8Writer_writeCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  self->writeCodePoints(thread, self, codePoints, numberOfCodePoints);
}

void
Arcadia_UTF8Writer_writeImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self,
    Arcadia_ImmutableUtf8String* immutableUTF8String
  )
{
  self->writeImmutableUTF8String(thread, self, immutableUTF8String);
}

void
Arcadia_UTF8Writer_writeString
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self,
    Arcadia_String* string
  )
{
  self->writeString(thread, self, string);
}

void
Arcadia_UTF8Writer_flush
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Writer* self
  )
{ self->flush(thread, self); }
