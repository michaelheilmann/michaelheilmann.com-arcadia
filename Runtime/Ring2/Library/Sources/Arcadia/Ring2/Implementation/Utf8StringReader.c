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
#include "Arcadia/Ring2/Implementation/Utf8StringReader.h"

#include "Arcadia/Ring2/Include.h"

#define CodePoint_Start (Arcadia_Unicode_CodePoint_Last + 1)
#define CodePoint_End (Arcadia_Unicode_CodePoint_Last + 2)
#define CodePoint_Error (Arcadia_Unicode_CodePoint_Last + 3)

/// @code
/// construct(source:String)
/// @endcode
static void
Arcadia_Utf8StringReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Utf8StringReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  );

static void
Arcadia_Utf8StringReader_nextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  );

static Arcadia_Natural32Value
Arcadia_Utf8StringReader_getCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  );

static Arcadia_BooleanValue
Arcadia_Utf8StringReader_hasCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  );

static Arcadia_SizeValue
Arcadia_Utf8StringReader_getByteIndexImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8StringReader_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Utf8StringReader_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcada.Utf8StringReader", Arcadia_Utf8StringReader,
                         u8"Arcadia.Utf8Reader", Arcadia_Utf8Reader,
                         &_typeOperations);

static void
Arcadia_Utf8StringReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8StringReader* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8StringReader_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->source = (Arcadia_String*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->byteIndex = 0;
  _self->codePoint = CodePoint_Start;
  ((Arcadia_Utf8Reader*)_self)->getByteIndex = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Utf8Reader*)) & Arcadia_Utf8StringReader_getByteIndexImpl;
  ((Arcadia_Utf8Reader*)_self)->getCodePoint = (Arcadia_Natural32Value(*)(Arcadia_Thread*, Arcadia_Utf8Reader*)) & Arcadia_Utf8StringReader_getCodePointImpl;
  ((Arcadia_Utf8Reader*)_self)->hasCodePoint = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Utf8Reader*)) & Arcadia_Utf8StringReader_hasCodePointImpl;
  ((Arcadia_Utf8Reader*)_self)->next = (void (*)(Arcadia_Thread*, Arcadia_Utf8Reader*)) & Arcadia_Utf8StringReader_nextImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Utf8StringReader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  )
{
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
}

static void
Arcadia_Utf8StringReader_nextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  )
{
  if (self->codePoint == CodePoint_End || self->codePoint == CodePoint_Error) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfBytes = Arcadia_String_getNumberOfBytes(thread, self->source);
  if (self->byteIndex == numberOfBytes) {
    self->codePoint = CodePoint_End;
  } else {
    Arcadia_Natural8Value byte = Arcadia_String_getByteAt(thread, self->source, self->byteIndex);
    Arcadia_SizeValue expectedNumberOfBytes = Arcadia_Unicode_Utf8_classifyFirstByte(thread, byte);
    if (expectedNumberOfBytes == Arcadia_SizeValue_Maximum || numberOfBytes - self->byteIndex < expectedNumberOfBytes) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
    // The masks to remove the prefix bits from the first Byte.
    static const Arcadia_Natural8Value mask[] = {
      0b11111111,
      0b00011111,
      0b00001111,
      0b00000111,
    };
    Arcadia_Natural32Value codePoint = byte & mask[expectedNumberOfBytes - 1];
    for (Arcadia_SizeValue i = 1; i < expectedNumberOfBytes; ++i) {
      byte = Arcadia_String_getByteAt(thread, self->source, self->byteIndex + i);
      if (0x80 != (byte & 0xc0)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(thread);
      }
      codePoint <<= 6;
      codePoint |= byte;
    }
    self->byteIndex += expectedNumberOfBytes;
    self->codePoint = codePoint;
  }
}

static Arcadia_Natural32Value
Arcadia_Utf8StringReader_getCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  )
{
  if (self->codePoint == CodePoint_Start || self->codePoint == CodePoint_End) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->codePoint;
}

static Arcadia_BooleanValue
Arcadia_Utf8StringReader_hasCodePointImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  )
{
  if (self->codePoint == CodePoint_Start) {
    Arcadia_Utf8StringReader_nextImpl(thread, self);
  }
  return CodePoint_End != self->codePoint;
}

static Arcadia_SizeValue
Arcadia_Utf8StringReader_getByteIndexImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8StringReader* self
  )
{ return self->byteIndex; }

Arcadia_Utf8StringReader*
Arcadia_Utf8StringReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(source),
  };
  Arcadia_Utf8StringReader* self = Arcadia_allocateObject(thread, _Arcadia_Utf8StringReader_getType(thread), 1, &argumentValues[0]);
  return self;
}
