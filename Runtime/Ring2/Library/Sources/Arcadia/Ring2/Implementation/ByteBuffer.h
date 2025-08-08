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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_BYTEBUFFER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_BYTEBUFFER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.ByteBuffer", Arcadia_ByteBuffer,
                          u8"Arcadia.Object");

struct Arcadia_ByteBuffer {
  Arcadia_Object _parent;
  char* p;
  Arcadia_SizeValue sz;
  Arcadia_SizeValue cp;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_create
Arcadia_ByteBuffer*
Arcadia_ByteBuffer_create
  (
    Arcadia_Thread* thread
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_endsWith_pn
Arcadia_BooleanValue
Arcadia_ByteBuffer_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_startsWith_pn
Arcadia_BooleanValue
Arcadia_ByteBuffer_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_append_pn
void
Arcadia_ByteBuffer_append_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_prepend_pn
void
Arcadia_ByteBuffer_prepend_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_insert_pn
void
Arcadia_ByteBuffer_insert_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_isEqualTo
Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    Arcadia_ByteBuffer const* other
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_isEqualTo_pn
Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Bytebuffer_clear
void
Arcadia_ByteBuffer_clear
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_getSize
Arcadia_SizeValue
Arcadia_ByteBuffer_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_getNumberOfBytes
Arcadia_SizeValue
Arcadia_ByteBuffer_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_getBytes
Arcadia_Natural8Value const*
Arcadia_ByteBuffer_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_getAt
Arcadia_Natural8Value
Arcadia_ByteBuffer_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteBuffer_swap
static inline void
Arcadia_ByteBuffer_swap
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    Arcadia_ByteBuffer* other
  )
{
  Arcadia_swapPointer(thread, &self->p, &other->p);
  Arcadia_swapSize(thread, &self->sz, &other->sz);
  Arcadia_swapSize(thread, &self->cp, &other->cp);
}

#endif // ARCADIA_RING2_IMPLEMENTATION_BYTEBUFFER_H_INCLUDED
