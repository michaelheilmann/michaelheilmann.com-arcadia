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

// Last modified: 2024-09-01

#if !defined(R_BYTEBUFFER_H_INCLUDED)
#define R_BYTEBUFFER_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "R/Object.h"

Rex_declareObjectType(u8"R.ByteBuffer", R_ByteBuffer, u8"R.Object");

struct R_ByteBuffer {
  R_Object _parent;
  char* p;
  Arcadia_SizeValue sz;
  Arcadia_SizeValue cp;
};

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-create
R_ByteBuffer*
R_ByteBuffer_create
  (
    Arcadia_Process* process
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-endswith-pn
Arcadia_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-startswith-pn
Arcadia_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-append-pn
void
R_ByteBuffer_append_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-prepend-pn
void
R_ByteBuffer_prepend_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-insert-pn
void
R_ByteBuffer_insert_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-isequalto
Arcadia_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-isequalto-pn
Arcadia_BooleanValue
R_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-clear
void
R_ByteBuffer_clear
  (
    R_ByteBuffer* self
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-getsize
Arcadia_SizeValue
R_ByteBuffer_getSize
  (
    R_ByteBuffer const* self
  );

Arcadia_SizeValue
R_ByteBuffer_getNumberOfBytes
  (
    R_ByteBuffer const* self
  );

Arcadia_Natural8Value const*
R_ByteBuffer_getBytes
  (
    R_ByteBuffer const* self
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-getat
Arcadia_Natural8Value
R_ByteBuffer_getAt
  (
    Arcadia_Process* process,
    R_ByteBuffer const* self,
    Arcadia_SizeValue index
  );

static inline void
R_ByteBuffer_swap
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    R_ByteBuffer* other
  )
{
  Arcadia_swap_p(process, &self->p, &other->p);
  Arcadia_swap_s(process, &self->sz, &other->sz);
  Arcadia_swap_s(process, &self->cp, &other->cp);
}

#endif // R_BYTEBUFFER_H_INCLUDED
