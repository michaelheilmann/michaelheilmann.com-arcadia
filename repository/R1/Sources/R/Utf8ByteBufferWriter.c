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

// Last modified: 2024-09-22

#include "R/Utf8ByteBufferWriter.h"

#include <string.h>
#include "R.h"

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
R_Utf8ByteBufferrWriter_writeCodePointsImpl
  (
    R_Utf8Writer* self,
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
  if (!numberOfCodePoints) {
    return;
  }
  for (R_SizeValue i = 0, n = numberOfCodePoints; i < n; ++i) {
    R_Natural32Value codePoint = codePoints[i];
    if (codePoint <= 0x7f) {
      uint8_t x[1];
      x[0] = (codePoint & 0b1111111);
      R_ByteBuffer_append_pn(self->target, &x[0], 1);
    } else if (/*0x80 <=*/ codePoint <= 0x7ff) {
      // This CP uses the lower 11 bit of the 32 Bit number.
      // The first 5 of these bits are stored in the first Byte.
      // The last 6 of these bits are stored in the second Byte.
      uint8_t x[2];
      x[0] = (codePoint & 0b11111000000) >> 6;
      x[1] = (codePoint & 0b00000111111) >> 0;
      // OR in 1100.0000.
      x[0] |= 0b11000000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      R_ByteBuffer_append_pn(self->target, &x[0], 2);
    } else if (/*0x800 <=*/ codePoint <= 0xffff) {
      // This CP uses the lower 16 bit of the 32 Bit number.
      // The first 4 of these bits are stored in the first Byte.
      // The next 6 of these bits are stored in the second Byte.
      // The last 6 of these bits are stored in teh third Byte.
      uint8_t x[3];
      x[0] = (codePoint & 0b1111000000000000) >> 12;
      x[1] = (codePoint & 0b0000111111000000) >> 6;
      x[2] = (codePoint & 0b0000000000111111) >> 0;
      // OR in 1110.0000.
      x[0] |= 0b11100000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      x[2] |= 0b10000000;
      R_ByteBuffer_append_pn(self->target, &x[0], 3);
    } else if (/*0x10000 <=*/ codePoint <= 0x10FFFF) {
      // This CP uses the lower 21 Bit of the code point.
      // The first 3 are stored in the first Byte.
      // The next 6 are stored in the second Byte.
      // The next 6 are stored in the third Byte.
      // The last 6 are stored in the fourth Byte.
      uint8_t x[4];
      x[0] = (codePoint & 0b111000000000000000000) >> 18;
      x[1] = (codePoint & 0b000111111000000000000) >> 12;
      x[2] = (codePoint & 0b000000000111111000000) >> 6;
      x[3] = (codePoint & 0b000000000000000111111) >> 0;
      // OR in 1111.0000.
      x[0] |= 0b1110000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      x[2] |= 0b10000000;
      x[3] |= 0b10000000;
      R_ByteBuffer_append_pn(self->target, &x[0], 4);
    } else {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
  }
}

void
_R_Utf8ByteBufferWriter_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("R.Utf8Writer", sizeof("R.Utf8Writer") - 1);
  R_registerObjectType("R.Utf8ByteBufferWriter", sizeof("R.Utf8ByteBufferWriter") - 1, sizeof(R_Utf8ByteBufferWriter), parentType, &R_Utf8ByteBufferWriter_visit, NULL);
}

void
R_Utf8ByteBufferWriter_construct
  (
    R_Utf8ByteBufferWriter* self,
    R_ByteBuffer* target
  )
{
  R_Utf8Writer_construct(R_UTF8WRITER(self));
  self->target = target;
  R_UTF8WRITER(self)->writeBytes = (void (*)(R_Utf8Writer*, void const*, R_SizeValue)) & R_Utf8ByteBufferWriter_writeBytesImpl;
  R_UTF8WRITER(self)->writeCodePoints = (void (*)(R_Utf8Writer*, R_Natural32Value const*, R_SizeValue)) & R_Utf8ByteBufferWriter_writeCodePointsImpl;
  R_Object_setType(self, R_getObjectType("R.Utf8ByteBufferWriter", sizeof("R.Utf8ByteBufferWriter") - 1));
}

R_Utf8ByteBufferWriter*
R_Utf8ByteBufferWriter_create
  (
    R_ByteBuffer* target
  )
{
  R_Utf8ByteBufferWriter* self = R_allocateObject(R_getObjectType("R.Utf8ByteBufferWriter", sizeof("R.Utf8ByteBufferWriter") - 1));
  self->target = target;
  R_UTF8WRITER(self)->writeBytes = (void (*)(R_Utf8Writer*, void const*, R_SizeValue)) & R_Utf8ByteBufferWriter_writeBytesImpl;
  R_UTF8WRITER(self)->writeCodePoints = (void (*)(R_Utf8Writer*, R_Natural32Value const*, R_SizeValue)) &R_Utf8ByteBufferWriter_writeCodePointsImpl;
  return self;
}
