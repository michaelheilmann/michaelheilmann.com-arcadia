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

// Last modified: 2024-09-01

#include "R/Utf8.h"

#include <string.h>

#include "Arms.h"
#include "R.h"

#define CodePoint_Start (0xfffffff1)
#define CodePoint_End (0xfffffff2)

static void
R_Utf8Reader_visit
  (
    R_Utf8Reader* self
  );

R_BooleanValue
R_isUtf8
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  uint8_t const* start = (uint8_t const*)bytes;
  uint8_t const* end = start + numberOfBytes;
  uint8_t const* current = start;

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      current += 1;
    } else if (x <= 0x7ff) {
      if (end - current < 2) {
        return R_BooleanValue_False;
      }
      for (R_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != x & 0xc0) {
          return R_BooleanValue_False;
          R_jump();
        }
      }
      current++;
    } else if (x <= 0xffff) {
      if (end - current < 3) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != x & 0xc0) {
          return R_BooleanValue_False;
          R_jump();
        }
      }
      current++;
    } else if (x <= 0x10ffff) {
      if (end - current < 4) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != x & 0xc0) {
          return R_BooleanValue_False;
          R_jump();
        }
      }
      current++;
    } else {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
  }
  return R_BooleanValue_True;
}

static void
R_Utf8Reader_visit
  (
    R_Utf8Reader* self
  )
{
  if (self->source) {
    Arms_visit(self->source);
  }
}

void
_R_Utf8Reader_registerType
  (
  )
{
  R_registerObjectType("R.Utf8Reader", sizeof("R.Utf8Reader") - 1, sizeof(R_Utf8Reader), &R_Utf8Reader_visit, NULL);
}

R_Utf8Reader*
R_Utf8Reader_create
  (
    R_ByteBuffer* source
  )
{
  R_Utf8Reader* self = R_allocateObject("R.Utf8Reader", sizeof("R.Utf8Reader") - 1, sizeof(R_Utf8Reader));
  self->source = source;
  self->index = 0;
  self->codePoint = CodePoint_Start;
  return self;
}

void
R_Utf8Reader_next
  (
    R_Utf8Reader* self
  )
{
  if (self->codePoint == CodePoint_End) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  R_SizeValue n = R_ByteBuffer_getSize(self->source);
  if (self->index == n) {
    self->codePoint = CodePoint_End;
    return;
  }
  R_Natural32Value codePoint;
  R_Natural8Value x = R_ByteBuffer_getAt(self->source, self->index);
  if (x <= 0b01111111) {
    codePoint = x;
    self->index += 1;
    self->codePoint = codePoint;
  } else if (x <= 0b11011111) {
    codePoint = x & 0b00011111;
    if (n - self->index < 2) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    for (size_t i = 1; i < 2; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->index + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->index += 2;
    self->codePoint = codePoint;
  } else if (x <= 0b11101111) {
    codePoint = x & 0b00001111;
    if (n - self->index < 3) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    for (size_t i = 1; i < 3; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->index + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x & 0b00111111;
    }
    self->index += 3;
    self->codePoint = codePoint;
  } else if (x <= 0b11110111) {
    codePoint = x & 0b00000111;
    if (n - self->index < 4) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
     }
    for (size_t i = 1; i < 4; ++i) {
      x = R_ByteBuffer_getAt(self->source, self->index + i);
      if (0x80 != x & 0xc0) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->index += 4;
    self->codePoint = codePoint;
  } else {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
}

R_Natural32Value
R_Utf8Reader_getCodePoint
  (
    R_Utf8Reader* self
  )
{
  if (self->codePoint == CodePoint_Start || self->codePoint == CodePoint_End) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return self->codePoint;
}

R_BooleanValue 
R_Utf8Reader_hasCodePoint
  (
    R_Utf8Reader* self
  )
{
  if (self->codePoint == CodePoint_Start) {
    R_Utf8Reader_next(self);
  }
  return CodePoint_End != self->codePoint;
}


static void
R_Utf8Writer_visit
  (
    R_Utf8Writer* self
  )
{
  if (self->target) {
    Arms_visit(self->target);
  }
}

void
_R_Utf8Writer_registerType
  (
  )
{
  R_registerObjectType("R.Utf8Writer", sizeof("R.Utf8Writer") - 1, sizeof(R_Utf8Writer), &R_Utf8Writer_visit, NULL);
}

R_Utf8Writer*
R_Utf8Writer_create
  (
    R_ByteBuffer* target
  )
{
  R_Utf8Writer* self = R_allocateObject("R.Utf8Writer", sizeof("R.Utf8Writer") - 1, sizeof(R_Utf8Writer));
  self->target = target;
  return self;
}

void
R_Utf8Writer_writeBytes
  (
    R_Utf8Writer* self,
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

void R_Utf8Writer_writeCodePoints(R_Utf8Writer* self, const R_Natural32Value* codePoints, R_SizeValue numberOfCodePoints) {
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
