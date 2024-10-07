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

// Last modified: 2024-10-07

#include "ByteBuffer.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static void
R_ByteBuffer_finalize
  (
    R_ByteBuffer* self
  );

static void
R_ByteBuffer_finalize
  (
    R_ByteBuffer* self
  )
{
  if (self->p) {
    R_Arms_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

void
_R_ByteBuffer_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType(u8"R.Object", sizeof(u8"R.Object") - 1);
  R_registerObjectType(u8"R.ByteBuffer", sizeof(u8"R.ByteBuffer") - 1, sizeof(R_ByteBuffer), parentType, NULL, NULL, &R_ByteBuffer_finalize);
}

void
R_ByteBuffer_construct
  (
    R_ByteBuffer* self
  )
{
  R_Type* _type = R_getObjectType(u8"R.ByteBuffer", sizeof(u8"R.ByteBuffer") - 1);
  R_Object_construct((R_Object*)self);
  self->p = NULL;
  self->sz = 0;
  self->cp = 0;
  if (!R_Arms_allocateUnmanaged_nojump(&self->p, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

R_ByteBuffer*
R_ByteBuffer_create
  (
  )
{
  R_ByteBuffer* self = R_allocateObject(R_getObjectType(u8"R.ByteBuffer", sizeof(u8"R.ByteBuffer") - 1));
  R_ByteBuffer_construct(self);
  return self;
}

R_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
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
    R_ByteBuffer const* self,
    void const* bytes,
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
    void const* bytes,
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
    void const* bytes,
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
    void const* bytes,
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
  R_SizeValue freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    R_SizeValue additionalCapacity = numberOfBytes - freeCapacity;
    R_SizeValue oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    R_SizeValue newCapacity = oldCapacity + additionalCapacity;
    if (!R_Arms_reallocateUnmanaged_nojump(&self->p, newCapacity)) {
      R_jump();
    }
    self->cp = newCapacity;
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

R_BooleanValue
R_ByteBuffer_isEqualTo_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self || !bytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (self->sz == numberOfBytes) {
    return !memcmp(self->p, bytes, numberOfBytes);
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

R_SizeValue
R_ByteBuffer_getSize
  (
    R_ByteBuffer const* self
  )
{
  return self->sz;
}

R_SizeValue
R_ByteBuffer_getNumberOfBytes
  (
    R_ByteBuffer const* self
  )
{ return self->sz; }

R_Natural8Value const*
R_ByteBuffer_getBytes
  (
    R_ByteBuffer const* self
  )
{ return self->p; }

R_Natural8Value
R_ByteBuffer_getAt
  (
    R_ByteBuffer const* self,
    R_SizeValue index
  )
{
  if (index >= self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return *(self->p + index);
}
