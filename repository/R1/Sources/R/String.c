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

#include "R/String.h"

#include <string.h>
#include "R/ArmsIntegration.h"
#include "R.h"

static void
R_String_finalize
  (
    R_String* self
  );

static void
R_String_finalize
  (
    R_String* self
  )
{
  if (self->p) {
    R_Arms_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

void
_R_String_registerType
  (
  )
{
  R_registerObjectType("R.String", sizeof("R.String") - 1, sizeof(R_String), NULL, NULL, &R_String_finalize);
}

R_String*
R_String_create
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();    
  }
  if (!R_isUtf8(bytes, numberOfBytes)) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
  R_String* self = R_allocateObject(R_getObjectType("R.String", sizeof("R.String") - 1));
  self->p = NULL;
  self->sz = 0;
  if (!R_Arms_allocateUnmanaged_nojump(&self->p, numberOfBytes)) {
    R_jump();    
  }
  memcpy(self->p, bytes, numberOfBytes);  
  self->sz = numberOfBytes;
  return self;
}

R_BooleanValue
R_String_endsWith_pn
  (
    R_String const* self,
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
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !memcmp(self->p, bytes, numberOfBytes);
}

R_BooleanValue
R_String_isEqualTo
  (
    R_String const* self,
    R_String const* other
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

R_SizeValue
R_String_getSize
  (
    R_String const* self
  )
{
  return self->sz;
}

R_Natural8Value
R_String_getAt
  (
    R_String const* self,
    R_SizeValue index
  )
{
  if (index >= self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return *(self->p + index);
}

R_BooleanValue
R_String_isEqualTo_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz == numberOfBytes) {
    return !memcmp(self->p, bytes, numberOfBytes);
  } else {
    return R_BooleanValue_False;
  }
}
