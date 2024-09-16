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

#include "R/StringBuffer.h"

#include <string.h>
#include "R/ArmsIntegration.h"
#include "R.h"
#include "R/Utf8.h"

static void
R_StringBuffer_finalize
  (
    R_StringBuffer* self
  );

static void
R_StringBuffer_finalize
  (
    R_StringBuffer* self
  )
{
  if (self->p) {
    R_Arms_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

void
_R_StringBuffer_registerType
  (
  )
{
  R_registerObjectType("R.StringBuffer", sizeof("R.StringBuffer") - 1, sizeof(R_StringBuffer), NULL, NULL, &R_StringBuffer_finalize);
}

R_StringBuffer*
R_StringBuffer_create
  (
  )
{
  R_StringBuffer* self = R_allocateObject(R_getObjectType("R.StringBuffer", sizeof("R.StringBuffer") - 1));
  self->p = NULL;
  self->sz = 0;
  self->cp = 0;
  if (!R_Arms_allocateUnmanaged_nojump(&self->p, 0)) {
    R_jump();
  }
  return self;
}

R_BooleanValue
R_StringBuffer_endsWith_pn
  (
    R_StringBuffer* self,
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
R_StringBuffer_startsWith_pn
  (
    R_StringBuffer* self,
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
R_StringBuffer_append_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    size_t numberOfBytes
  )
{
  if (!bytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_isUtf8(bytes, numberOfBytes)) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
  size_t freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    size_t additionalCapacity = numberOfBytes - freeCapacity;
    size_t oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    size_t newCapacity = oldCapacity + additionalCapacity;
    if (!R_Arms_reallocateUnmanaged_nojump(&self->p, newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    self->cp = newCapacity;
  }
  memcpy(self->p + self->sz, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

R_BooleanValue
R_StringBuffer_isEqualTo
  (
    R_StringBuffer* self,
    R_StringBuffer* other
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
R_StringBuffer_clear
  (
    R_StringBuffer* self
  )
{
  self->sz = 0;
}
