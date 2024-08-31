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

#if !defined(R_UTF8_H_INCLUDED)
#define R_UTF8_H_INCLUDED

#include "R/ByteBuffer.h"
#include "R/Natural32.h"

R_BooleanValue
R_isUtf8
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

typedef struct R_Utf8Reader R_Utf8Reader;

void _R_Utf8Reader_registerType();

struct R_Utf8Reader {
  R_ByteBuffer* source;
  R_SizeValue index;
  R_Natural32Value codePoint;
};

R_Utf8Reader* R_Utf8Reader_create(R_ByteBuffer* source);

void R_Utf8Reader_next(R_Utf8Reader* self);

R_Natural32Value R_Utf8Reader_getCodePoint(R_Utf8Reader* self);

R_BooleanValue R_Utf8Reader_hasCodePoint(R_Utf8Reader* self);

typedef struct R_Utf8Writer R_Utf8Writer;

void _R_Utf8Writer_registerType();

struct R_Utf8Writer {
  R_ByteBuffer* target;
};

R_Utf8Writer* R_Utf8Writer_create(R_ByteBuffer* target);

void R_Utf8Writer_writeBytes(R_Utf8Writer* self, const void* bytes, R_SizeValue numberOfBytes);

void R_Utf8Writer_writeCodePoints(R_Utf8Writer* self, const R_Natural32Value* codePoints, R_SizeValue numberOfCodePoints);

#endif // R_UTF8_H_INCLUDED
