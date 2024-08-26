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

// Last modified: 2024-08-28

#include "bytebuffer.h"

#include <string.h>

#include "arms1.h"
#include "r/jumptarget.h"
#include "r/status.h"
#include "r/object.h"

static void R_ByteBuffer_finalize(R_ByteBuffer* self);

static void R_ByteBuffer_finalize(R_ByteBuffer* self) {
  if (self->p) {
    Arms_deallocateUnmanaged(self->p);
    self->p = NULL;
  }
}

void _R_ByteBuffer_registerType() {
  R_registerObjectType("R.ByteBuffer", sizeof("R.ByteBuffer") - 1, NULL, (Arms_FinalizeCallbackFunction*)&R_ByteBuffer_finalize);
}

R_ByteBuffer*
R_ByteBuffer_create
  (
  )
{
  R_ByteBuffer* self = R_allocateObject("R.ByteBuffer", sizeof("R.ByteBuffer") - 1, sizeof(R_ByteBuffer));
  self->p = NULL;
  self->sz = 0;
  self->cp = 0;
  if (Arms_allocateUnmanaged(&self->p, 1)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  return self;
}

R_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  R_SizeValue d = self->sz - numberOfBytes;
  return !memcmp(self->p + d, bytes, numberOfBytes);
}

R_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !memcmp(self->p, bytes, numberOfBytes);
}

void
R_ByteBuffer_append_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_ByteBuffer_insert_pn(self, self->sz, bytes, numberOfBytes);
}

void
R_ByteBuffer_prepend_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_ByteBuffer_insert_pn(self, R_SizeValue_Literal(0), bytes, numberOfBytes);
}

void
R_ByteBuffer_insert_pn
  (
    R_ByteBuffer* self,
    R_SizeValue index,
    char const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self || !bytes || index > self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!numberOfBytes) {
    return;
  }
  R_SizeValue freeCp = self->cp - self->sz;
  if (freeCp < numberOfBytes) {
    R_SizeValue additionalCp = numberOfBytes - freeCp;
    R_SizeValue oldCp = self->cp;
    if (SIZE_MAX - oldCp < additionalCp) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    R_SizeValue newCp = oldCp + additionalCp;
    if (Arms_reallocateUnmanaged(&self->p, newCp)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    self->cp = newCp;
  }
  if (index < self->sz) {
    memmove(self->p + index, self->p + index + numberOfBytes, self->sz - index);
  }
  memcpy(self->p + index, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

R_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  )
{
  if (self == other) {
    return R_BooleanValue_True;
  }
  if (self->sz == other->sz) {
    return !memcmp(self->p, other->p, self->sz);
  } else {
    return R_BooleanValue_False;
  }
}

void
R_ByteBuffer_clear
  (
    R_ByteBuffer* self
  )
{
  self->sz = 0;
}
