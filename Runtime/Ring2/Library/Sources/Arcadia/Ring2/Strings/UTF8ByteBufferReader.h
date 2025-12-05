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

#if !defined(ARCADIA_RING2_STRINGS_UTF8BYTEBUFFERREADER_H_INCLUDED)
#define ARCADIA_RING2_STRINGS_UTF8BYTEBUFFERREADER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Strings/UTF8Reader.h"
#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_ByteBuffer Arcadia_ByteBuffer;

Arcadia_declareObjectType(u8"Arcadia.UTF8ByteBufferReader", Arcadia_UTF8ByteBufferReader,
                          u8"Arcadia.UTF8Reader");

struct Arcadia_UTF8ByteBufferReader {
  Arcadia_UTF8Reader parent;
  Arcadia_ByteBuffer* source;
  Arcadia_SizeValue byteIndex;
  Arcadia_Natural32Value byteLength;
  Arcadia_Natural32Value codePoint;
};

Arcadia_UTF8ByteBufferReader*
Arcadia_UTF8ByteBufferReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* source
  );

#endif // ARCADIA_RING2_STRINGS_UTF8BYTEBUFFERREADER_H_INCLUDED
