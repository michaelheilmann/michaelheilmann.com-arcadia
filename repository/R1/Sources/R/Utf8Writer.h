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

#if !defined(R_UTF8WRITER_H_INCLUDED)
#define R_UTF8WRITER_H_INCLUDED

#include "R/Boolean.h"
#include "R/Natural32.h"
#include "R/Size.h"
typedef struct R_ByteBuffer R_ByteBuffer;

#define R_UTF8WRITER(x) ((R_Utf8Writer*)(x))
typedef struct R_Utf8Writer R_Utf8Writer;
void _R_Utf8Writer_registerType();

struct R_Utf8Writer {
  void (*writeBytes)(R_Utf8Writer* self, const void* bytes, R_SizeValue numberOfBytes);
  void (*writeCodePoints)(R_Utf8Writer* self, R_Natural32Value const* codePoints, R_SizeValue numberOfCodePoints);
  
};

void
R_Utf8Writer_construct
  (
    R_Utf8Writer* self
  );

void
R_Utf8Writer_writeBytes
  (
    R_Utf8Writer* self,
    const void* bytes,
    R_SizeValue numberOfBytes
  );

void
R_Utf8Writer_writeCodePoints
  (
    R_Utf8Writer* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  );

#endif // R_UTF8WRITER_H_INCLUDED
