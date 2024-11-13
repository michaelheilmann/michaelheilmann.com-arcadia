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

#include "R/Utf8ByteBufferWriter.h"

#include "R/ByteBuffer.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/Utf8/EncodeCodePoints.h"

// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static void
R_Utf8ByteBufferWriter_visit
  (
    R_Utf8ByteBufferWriter* self
  );

static void
R_Utf8ByteBufferWriter_writeBytesImpl
  (
    R_Utf8ByteBufferWriter* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

static void
R_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    R_Utf8ByteBufferWriter* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  );

static void
R_Utf8ByteBufferWriter_visit
  (
    R_Utf8ByteBufferWriter* self
  )
{
  R_Object_visit(self->target);
}

static void
R_Utf8ByteBufferWriter_writeBytesImpl
  (
    R_Utf8ByteBufferWriter* self,
    const void* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!numberOfBytes) {
    return;
  }
  for (R_Natural8Value const* current = (R_Natural8Value const*)bytes, *end = (R_Natural8Value const*)bytes + numberOfBytes; current != end; ) {
    R_Natural8Value x = *current;
    if (x <= 0x7f) {
      R_ByteBuffer_append_pn(self->target, current, 1);
      current++;
    } else if (x <= 0x7ff) {
      R_ByteBuffer_append_pn(self->target, current, 1);
      if (end - current < 2) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      current++;
      for (size_t i = 1; i < 2; ++i) {
        if (0x80 != (*current) & 0xc0) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
        R_ByteBuffer_append_pn(self->target, current, 1);
        current++;
      }
    } else if (x <= 0xffff) {
      R_ByteBuffer_append_pn(self->target, current, 1);
      if (end - current < 3) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      current++;
      for (size_t i = 1; i < 3; ++i) {
        if (0x80 != (*current) & 0xc0) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
        R_ByteBuffer_append_pn(self->target, current, 1);
        current++;
      }
    } else if (x <= 0x10ffff) {
      R_ByteBuffer_append_pn(self->target, current, 1);
      if (end - current < 4) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      current++;
      for (size_t i = 1; i < 4; ++i) {
        if (0x80 != (*current) & 0xc0) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
        R_ByteBuffer_append_pn(self->target, current, 1);
        current++;
      }
    } else {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
  }
}

static void
R_Utf8ByteBufferWriter_writeCodePointsImpl
  (
    R_Utf8ByteBufferWriter* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  )
{
  R_Utf8_encodeCodePoints(codePoints, numberOfCodePoints, self->target, (void (*)(void*, R_Natural8Value const*, R_SizeValue)) & R_ByteBuffer_append_pn);
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Utf8ByteBufferWriter_visit,
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

Rex_defineObjectType("R.Utf8ByteBufferWriter", R_Utf8ByteBufferWriter, "R.Utf8Writer", R_Utf8Writer, &_typeOperations);

void
R_Utf8ByteBufferWriter_construct
  (
    R_Utf8ByteBufferWriter* self,
    R_ByteBuffer* target
  )
{
  R_Type* _type = _R_Utf8ByteBufferWriter_getType();
  R_Utf8Writer_construct(R_UTF8WRITER(self));
  self->target = target;
  R_UTF8WRITER(self)->writeBytes = (void (*)(R_Utf8Writer*, void const*, R_SizeValue)) & R_Utf8ByteBufferWriter_writeBytesImpl;
  R_UTF8WRITER(self)->writeCodePoints = (void (*)(R_Utf8Writer*, R_Natural32Value const*, R_SizeValue)) & R_Utf8ByteBufferWriter_writeCodePointsImpl;
  R_Object_setType(self, _type);
}

R_Utf8ByteBufferWriter*
R_Utf8ByteBufferWriter_create
  (
    R_ByteBuffer* target
  )
{
  R_Utf8ByteBufferWriter* self = R_allocateObject(_R_Utf8ByteBufferWriter_getType());
  R_Utf8ByteBufferWriter_construct(self, target);
  return self;
}
