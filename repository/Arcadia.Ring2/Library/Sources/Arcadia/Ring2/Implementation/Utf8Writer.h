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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_UTF8WRITER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_UTF8WRITER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_ByteBuffer Arcadia_ByteBuffer;

Rex_declareObjectType(u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer, u8"Arcadia.Object");

struct Arcadia_Utf8Writer {
  Arcadia_Object _parent;
  void (*writeBytes)(Arcadia_Thread*, Arcadia_Utf8Writer* self, const void* bytes, Arcadia_SizeValue numberOfBytes);
  void (*writeCodePoints)(Arcadia_Thread*, Arcadia_Utf8Writer* self, Arcadia_Natural32Value const* codePoints, Arcadia_SizeValue numberOfCodePoints);
};

void
Arcadia_Utf8Writer_writeBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
Arcadia_Utf8Writer_writeCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_UTF8WRITER_H_INCLUDED
