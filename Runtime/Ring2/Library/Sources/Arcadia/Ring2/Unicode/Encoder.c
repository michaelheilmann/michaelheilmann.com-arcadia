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
#include "Arcadia/Ring2/Unicode/Encoder.h"

static void
Arcadia_Unicode_Encoder_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self
  );

static void
Arcadia_Unicode_Encoder_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_EncoderDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Unicode_Encoder_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Unicode_Encoder_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Unicode.Encoder", Arcadia_Unicode_Encoder,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Unicode_Encoder_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Unicode_Encoder);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_Unicode_Encoder);
}

static void
Arcadia_Unicode_Encoder_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_EncoderDispatch* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Unicode_Encoder_encodeCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    Arcadia_ByteArrayBuilder* target
  )
{ Arcadia_VirtualCall(Arcadia_Unicode_Encoder, encodeCodePoints, self, codePoints, numberOfCodePoints, target); }

void
Arcadia_Unicode_Encoder_encodeImmutableByteArray
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self,
    Arcadia_RuntimeByteArray* source,
    Arcadia_ByteArrayBuilder* target
  )
{ Arcadia_VirtualCall(Arcadia_Unicode_Encoder, encodeImmutableByteArray, self, source, target); }

void
Arcadia_Unicode_Encoder_encodeRuntimeUTF8String
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self,
    Arcadia_RuntimeUTF8String* source,
    Arcadia_ByteArrayBuilder* target
  )
{ Arcadia_VirtualCall(Arcadia_Unicode_Encoder, encodeRuntimeUTF8String, self, source, target); }

void
Arcadia_Unicode_Encoder_encodeString
  (
    Arcadia_Thread* thread,
    Arcadia_Unicode_Encoder* self,
    Arcadia_String* source,
    Arcadia_ByteArrayBuilder* target
  )
{ Arcadia_VirtualCall(Arcadia_Unicode_Encoder, encodeString, self, source, target); }
