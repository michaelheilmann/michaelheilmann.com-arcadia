// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-07

#include "R/Utf8ByteBufferReader.h"

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/Utf8.h"
#include "R/Value.h"

#define CodePoint_Start (R_Utf8CodePoint_Last + 1)
#define CodePoint_End (R_Utf8CodePoint_Last + 2)
#define CodePoint_Error (R_Utf8CodePoint_Last + 3)

/// @code
/// construct(source:ByteBuffer)
/// @endcode
static void
R_Utf8ByteBufferReader_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Utf8ByteBufferReader_visit
  (
    R_Utf8ByteBufferReader* self
  );

static void
R_Utf8ByteBufferReader_nextImpl
  (
    R_Utf8ByteBufferReader* self
  );

static R_Natural32Value
R_Utf8ByteBufferReader_getCodePointImpl
  (
    R_Utf8ByteBufferReader* self
  );

static R_BooleanValue
R_Utf8ByteBufferReader_hasCodePointImpl
  (
    R_Utf8ByteBufferReader* self
  );

static void
R_Utf8ByteBufferReader_visit
  (
    R_Utf8ByteBufferReader* self
  )
{
  R_Object_visit(self->source);
}

static void
R_Utf8ByteBufferReader_nextImpl
  (
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_End || self->codePoint == CodePoint_Error) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  R_SizeValue n = R_ByteBuffer_getSize(self->source);
  if (self->byteIndex == n) {
    self->codePoint = CodePoint_End;
    return;
  }
  R_Natural32Value codePoint;
  R_Natural8Value x = R_ByteBuffer_getAt(self->source, self->byteIndex);
  if (x <= 0b01111111) {
    codePoint = x;
    self->byteIndex += 1;
    self->codePoint = codePoint;
  } else if (x <= 0b11011111) {
    codePoint = x & 0b00011111;
    if (n - self->byteIndex < 2) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    for (size_t i = 1; i < 2; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->byteIndex += 2;
    self->codePoint = codePoint;
  } else if (x <= 0b11101111) {
    codePoint = x & 0b00001111;
    if (n - self->byteIndex < 3) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    for (size_t i = 1; i < 3; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x & 0b00111111;
    }
    self->byteIndex += 3;
    self->codePoint = codePoint;
  } else if (x <= 0b11110111) {
    codePoint = x & 0b00000111;
    if (n - self->byteIndex < 4) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    for (size_t i = 1; i < 4; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->byteIndex += 4;
    self->codePoint = codePoint;
  } else {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
}

static R_Natural32Value
R_Utf8ByteBufferReader_getCodePointImpl
  (
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_Start || self->codePoint == CodePoint_End) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return self->codePoint;
}

static R_BooleanValue
R_Utf8ByteBufferReader_hasCodePointImpl
  (
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_Start) {
    R_Utf8ByteBufferReader_nextImpl(self);
  }
  return CodePoint_End != self->codePoint;
}

static R_SizeValue
R_Utf8ByteBufferReader_getByteIndexImpl
  (
    R_Utf8ByteBufferReader* self
  )
{ return self->byteIndex; }

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Utf8ByteBufferReader_constructImpl,
  .destruct = NULL,
  .visit = &R_Utf8ByteBufferReader_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.Utf8ByteBufferReader", R_Utf8ByteBufferReader, "R.Utf8Reader", R_Utf8Reader, &_typeOperations);

void
R_Utf8ByteBufferReader_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Utf8ByteBufferReader* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Utf8ByteBufferReader_getType();
  {
    R_Value argumentValues[] =  { { .tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, & argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_ByteBuffer_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->source = R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->byteIndex = 0;
  _self->codePoint = CodePoint_Start;
  R_UTF8READER(_self)->getByteIndex = (R_SizeValue(*)(R_Utf8Reader*)) & R_Utf8ByteBufferReader_getByteIndexImpl;
  R_UTF8READER(_self)->getCodePoint = (R_Natural32Value (*)(R_Utf8Reader*)) & R_Utf8ByteBufferReader_getCodePointImpl;
  R_UTF8READER(_self)->hasCodePoint = (R_BooleanValue (*)(R_Utf8Reader*)) &R_Utf8ByteBufferReader_hasCodePointImpl;
  R_UTF8READER(_self)->next = (void (*)(R_Utf8Reader*)) &R_Utf8ByteBufferReader_nextImpl;
  R_Object_setType(_self, _type);
}

R_Utf8ByteBufferReader*
R_Utf8ByteBufferReader_create
  (
    R_ByteBuffer* source
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = source }, };
  R_Utf8ByteBufferReader* self = R_allocateObject(_R_Utf8ByteBufferReader_getType(), 1, &argumentValues[0]);
  return self;
}
