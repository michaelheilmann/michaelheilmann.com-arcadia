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
#include "Arcadia/Ring2/Implementation/Utf8FileHandleWriter.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"
#include "Arcadia/Ring2/FileSystem/FileHandle.h"
#include "Arcadia/Ring2/Implementation/String.h"

static void
Arcadia_Utf8FileHandleWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  );

static void
Arcadia_Utf8FileHandleWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  );

static void
Arcadia_Utf8FileHandleWriter_flush
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  );

static void
Arcadia_Utf8FileHandleWriter_writeBytesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
Arcadia_Utf8FileHandleWriter_writeCodePointsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

static void
Arcadia_Utf8FileHandleWriter_writeStringImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    Arcadia_String* string
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Utf8FileHandleWriter_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Utf8FileHandleWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Utf8FileHandleWriter", Arcadia_Utf8FileHandleWriter,
                         u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer,
                         &_typeOperations);

static void
Arcadia_Utf8FileHandleWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Utf8FileHandleWriter_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->target = (Arcadia_FileHandle*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FileHandle_getType(thread));
  self->temporary = Arcadia_ByteBuffer_create(thread);
  ((Arcadia_Utf8Writer*)self)->writeBytes = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, void const*, Arcadia_SizeValue)) & Arcadia_Utf8FileHandleWriter_writeBytesImpl;
  ((Arcadia_Utf8Writer*)self)->writeCodePoints = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, Arcadia_Natural32Value const*, Arcadia_SizeValue)) & Arcadia_Utf8FileHandleWriter_writeCodePointsImpl;
  ((Arcadia_Utf8Writer*)self)->writeString = (void (*)(Arcadia_Thread*, Arcadia_Utf8Writer*, Arcadia_String*)) & Arcadia_Utf8FileHandleWriter_writeStringImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_Utf8FileHandleWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  )
{
  if (self->target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->target);
  }
  if (self->temporary) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->temporary);
  }
}

static void
Arcadia_Utf8FileHandleWriter_flush
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self
  )
{
  Arcadia_SizeValue bytesToWrite = Arcadia_ByteBuffer_getNumberOfBytes(thread, self->temporary),
                    bytesWritten = 0;
  const Arcadia_Natural8Value* bytes = Arcadia_ByteBuffer_getBytes(thread, self->temporary);
  while (bytesToWrite) {
    Arcadia_SizeValue bytesWrittenNow = 0;
    Arcadia_FileHandle_write(thread, self->target, bytes + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  Arcadia_ByteBuffer_clear(thread, self->temporary);
}

static void
Arcadia_Utf8FileHandleWriter_writeBytesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_Unicode_encodeBytesUtf8(thread, bytes, numberOfBytes, self->temporary, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&Arcadia_ByteBuffer_append_pn);
  Arcadia_Utf8FileHandleWriter_flush(thread, self);
}

static void
Arcadia_Utf8FileHandleWriter_writeCodePointsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_Unicode_encodeCodePointsUtf8(thread, codePoints, numberOfCodePoints, self->temporary, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&Arcadia_ByteBuffer_append_pn);
  Arcadia_Utf8FileHandleWriter_flush(thread, self);
}

static void
Arcadia_Utf8FileHandleWriter_writeStringImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8FileHandleWriter* self,
    Arcadia_String* string
  )
{
  Arcadia_ByteBuffer_append_pn(thread, self->temporary, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
  Arcadia_Utf8FileHandleWriter_flush(thread, self);
}

Arcadia_Utf8FileHandleWriter*
Arcadia_Utf8FileHandleWriter_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* target
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)target);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Utf8FileHandleWriter);
}
