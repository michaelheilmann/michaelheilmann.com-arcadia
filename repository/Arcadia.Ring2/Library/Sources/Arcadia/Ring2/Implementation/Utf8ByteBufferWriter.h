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

// Last modified: 2025-02-15

#if !defined(ARCADIA_RING2_IMPLEMENTATION_UTF8BYTEBUFFERWRITER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_UTF8BYTEBUFFERWRITER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Implementation/Utf8Writer.h"
typedef struct Arcadia_ByteBuffer Arcadia_ByteBuffer;

Arcadia_declareObjectType(u8"Arcadia.Utf8ByteBufferWriter", Arcadia_Utf8ByteBufferWriter, u8"Arcadia.Utf8Writer");

struct Arcadia_Utf8ByteBufferWriter {
  Arcadia_Utf8Writer parent;
  Arcadia_ByteBuffer* target; 
};

Arcadia_Utf8ByteBufferWriter*
Arcadia_Utf8ByteBufferWriter_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_UTF8BYTEBUFFERWRITER_H_INCLUDED
