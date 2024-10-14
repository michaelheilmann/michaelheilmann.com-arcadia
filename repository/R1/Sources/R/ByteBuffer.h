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

#if !defined(R_BYTEBUFFER_H_INCLUDED)
#define R_BYTEBUFFER_H_INCLUDED

#include "R/Boolean.h"
#include "R/Natural8.h"
#include "R/Object.h"
#include "R/swap.h"
#include "R/Size.h"

Rex_declareObjectType("R.ByteBuffer", R_ByteBuffer, "R.Object");

struct R_ByteBuffer {
  R_Object _parent;
  char* p;
  R_SizeValue sz;
  R_SizeValue cp;
};

void
R_ByteBuffer_construct
  (
    R_ByteBuffer* self
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-create
R_ByteBuffer*
R_ByteBuffer_create
  (
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-endswith-pn
R_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-startswith-pn
R_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-append-pn
void
R_ByteBuffer_append_pn
  (
    R_ByteBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-prepend-pn
void
R_ByteBuffer_prepend_pn
  (
    R_ByteBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-insert-pn
void
R_ByteBuffer_insert_pn
  (
    R_ByteBuffer* self,
    R_SizeValue index,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-isequalto
R_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-isequalto-pn
R_BooleanValue
R_ByteBuffer_isEqualTo_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-clear
void
R_ByteBuffer_clear
  (
    R_ByteBuffer* self
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-getsize
R_SizeValue
R_ByteBuffer_getSize
  (
    R_ByteBuffer const* self
  );

R_SizeValue
R_ByteBuffer_getNumberOfBytes
  (
    R_ByteBuffer const* self
  );

R_Natural8Value const*
R_ByteBuffer_getBytes
  (
    R_ByteBuffer const* self
  );

// https://michaelheilmann.com/repository/R1/#r-bytebuffer-getat
R_Natural8Value
R_ByteBuffer_getAt
  (
    R_ByteBuffer const* self,
    R_SizeValue index
  );

static inline void
R_ByteBuffer_swap
  (
    R_ByteBuffer* self,
    R_ByteBuffer* other
  )
{
  R_swap_p(&self->p, &other->p);
  R_swap_s(&self->sz, &other->sz);
  R_swap_s(&self->cp, &other->cp);
}

#endif // R_BYTEBUFFER_H_INCLUDED
