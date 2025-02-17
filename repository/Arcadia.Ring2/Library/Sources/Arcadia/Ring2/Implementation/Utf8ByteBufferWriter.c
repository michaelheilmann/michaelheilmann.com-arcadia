// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-02-15

#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "R/Utf8/EncodeCodePoints.h"

static void
Arcadia_Utf8ByteBufferWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Utf8ByteBufferWriter_visit
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self
  );

static void
Arcadia_Utf8ByteBufferWriter_writeBytesImpl
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8ByteBufferWriter_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Utf8ByteBufferWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Arcadia.Utf8ByteBufferWriter", Arcadia_Utf8ByteBufferWriter, u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer, &_typeOperations);

static void
Arcadia_Utf8ByteBufferWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8ByteBufferWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8ByteBufferWriter_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _Arcadia_ByteBuffer_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  _self->target = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
  ((Arcadia_Utf8Writer*)_self)->writeBytes = (void (*)(Arcadia_Process*, Arcadia_Utf8Writer*, void const*, Arcadia_SizeValue)) & Arcadia_Utf8ByteBufferWriter_writeBytesImpl;
  ((Arcadia_Utf8Writer*)_self)->writeCodePoints = (void (*)(Arcadia_Process*, Arcadia_Utf8Writer*, Arcadia_Natural32Value const*, Arcadia_SizeValue)) & Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl;
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Utf8ByteBufferWriter_visit
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self
  )
{
  if (self->target) {
    Arcadia_Object_visit(process, self->target);
  }
}

static void
Arcadia_Utf8ByteBufferWriter_writeBytesImpl
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!numberOfBytes) {
    return;
  }
  for (Arcadia_Natural8Value const* current = (Arcadia_Natural8Value const*)bytes, *end = (Arcadia_Natural8Value const*)bytes + numberOfBytes; current != end; ) {
    Arcadia_Natural8Value x = *current;
    if (x <= 0x7f) {
      Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
      current++;
    } else if (x <= 0x7ff) {
      Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
      if (end - current < 2) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      current++;
      for (size_t i = 1; i < 2; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
        }
        Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
        current++;
      }
    } else if (x <= 0xffff) {
      Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
      if (end - current < 3) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      current++;
      for (size_t i = 1; i < 3; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
        }
        Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
        current++;
      }
    } else if (x <= 0x10ffff) {
      Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
      if (end - current < 4) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      current++;
      for (size_t i = 1; i < 4; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
        }
        Arcadia_ByteBuffer_append_pn(process, self->target, current, 1);
        current++;
      }
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
  }
}

static void
Arcadia_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    Arcadia_Process* process,
    Arcadia_Utf8ByteBufferWriter* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  R_Utf8_encodeCodePoints(process, codePoints, numberOfCodePoints, self->target, (void (*)(Arcadia_Process*, void*, Arcadia_Natural8Value const*, Arcadia_SizeValue)) & Arcadia_ByteBuffer_append_pn);
}

Arcadia_Utf8ByteBufferWriter*
Arcadia_Utf8ByteBufferWriter_create
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* target
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)target } };
  Arcadia_Utf8ByteBufferWriter* self = R_allocateObject(process, _Arcadia_Utf8ByteBufferWriter_getType(process), 1, &argumentValues[0]);
  return self;
}
