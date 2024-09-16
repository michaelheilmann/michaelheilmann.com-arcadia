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

// Last modified: 2024-09-20

#include "R/Utf8Reader.h"

#include <string.h>
#include "R/Utf8.h"
#include "R.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Utf8Reader_visit
  (
    R_Utf8Reader* self
  );

static void
R_Utf8Reader_nextImpl
  (
    R_Utf8Reader* self
  );

static R_Natural32Value
R_Utf8Reader_getCodePointImpl
  (
    R_Utf8Reader* self
  );

static R_BooleanValue
R_Utf8Reader_hasCodePointImpl
  (
    R_Utf8Reader* self
  );

static void
R_Utf8Reader_visit
  (
    R_Utf8Reader* self
  )
{
  R_Object_visit(self->source);
}

static void
R_Utf8Reader_nextImpl
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

static R_Natural32Value
R_Utf8Reader_getCodePointImpl
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

static R_BooleanValue
R_Utf8Reader_hasCodePointImpl
  (
    R_Utf8Reader* self
  )
{
  if (self->codePoint == CodePoint_Start) {
    R_Utf8Reader_next(self);
  }
  return CodePoint_End != self->codePoint;
}

void
_R_Utf8Reader_registerType
  (
  )
{
  R_registerObjectType("R.Utf8Reader", sizeof("R.Utf8Reader") - 1, sizeof(R_Utf8Reader), NULL, &R_Utf8Reader_visit, NULL);
}

R_Utf8Reader*
R_Utf8Reader_create
  (
    R_ByteBuffer* source
  )
{
  R_Utf8Reader* self = R_allocateObject(R_getObjectType("R.Utf8Reader", sizeof("R.Utf8Reader") - 1));
  self->source = source;
  self->index = 0;
  self->codePoint = CodePoint_Start;
  self->getCodePoint = &R_Utf8Reader_getCodePointImpl;
  self->hasCodePoint = &R_Utf8Reader_hasCodePointImpl;
  self->next = &R_Utf8Reader_nextImpl;
  return self;
}

void
R_Utf8Reader_next
  (
    R_Utf8Reader* self
  )
{
  self->next(self);
}

R_Natural32Value
R_Utf8Reader_getCodePoint
  (
    R_Utf8Reader* self
  )
{
  return self->getCodePoint(self);
}

R_BooleanValue
R_Utf8Reader_hasCodePoint
  (
    R_Utf8Reader* self
  )
{
  return self->hasCodePoint(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
