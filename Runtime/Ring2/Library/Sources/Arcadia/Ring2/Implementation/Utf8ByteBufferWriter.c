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
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/String.h"

static void
Arcadia_Utf8ByteBufferWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Utf8ByteBufferWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self
  );

static void
Arcadia_Utf8ByteBufferWriter_writeBytesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

static void
Arcadia_Utf8ByteBufferWriter_writeStringImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_String* string
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8ByteBufferWriter_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Utf8ByteBufferWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Utf8ByteBufferWriter", Arcadia_Utf8ByteBufferWriter,
                         u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer,
                         &_typeOperations);

static void
Arcadia_Utf8ByteBufferWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8ByteBufferWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8ByteBufferWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->target = (Arcadia_ByteBuffer*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ByteBuffer_getType(thread));
  ((Arcadia_Utf8Writer*)_self)->writeBytes = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, void const*, Arcadia_SizeValue)) & Arcadia_Utf8ByteBufferWriter_writeBytesImpl;
  ((Arcadia_Utf8Writer*)_self)->writeCodePoints = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, Arcadia_Natural32Value const*, Arcadia_SizeValue)) & Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl;
  ((Arcadia_Utf8Writer*)_self)->writeString = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, Arcadia_String*))&Arcadia_Utf8ByteBufferWriter_writeStringImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_Utf8ByteBufferWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self
  )
{
  if (self->target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->target);
  }
}

static void
Arcadia_Utf8ByteBufferWriter_writeBytesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_Unicode_encodeBytesUtf8(thread, bytes, numberOfBytes, self->target, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&Arcadia_ByteBuffer_append_pn);
}

static void
Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_Unicode_encodeCodePointsUtf8(thread, codePoints, numberOfCodePoints, self->target, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&Arcadia_ByteBuffer_append_pn);
}

static void
Arcadia_Utf8ByteBufferWriter_writeStringImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_String* string
  )
{ 
  Arcadia_ByteBuffer_append_pn(thread, self->target, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
}

Arcadia_Utf8ByteBufferWriter*
Arcadia_Utf8ByteBufferWriter_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)target);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Utf8ByteBufferWriter);
}
