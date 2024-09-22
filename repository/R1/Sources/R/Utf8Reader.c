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

// Last modified: 2024-09-20

#include "R/Utf8Reader.h"

#include <string.h>
#include "R/Utf8.h"
#include "R.h"

void
_R_Utf8Reader_registerType
  (
  )
{
  R_registerObjectType("R.Utf8Reader", sizeof("R.Utf8Reader") - 1, sizeof(R_Utf8Reader), NULL, NULL, NULL);
}

void
R_Utf8Reader_construct
  (
    R_Utf8Reader* self
  )
{
  self->getCodePoint = NULL;
  self->hasCodePoint = NULL;
  self->next = NULL;
  R_Object_setType(self, R_getObjectType("R.Utf8Reader", sizeof("R.Utf8Reader") - 1));
}

void
R_Utf8Reader_next
  (
    R_Utf8Reader* self
  )
{
  self->next(self);
}

R_Natural32Value
R_Utf8Reader_getCodePoint
  (
    R_Utf8Reader* self
  )
{
  return self->getCodePoint(self);
}

R_BooleanValue
R_Utf8Reader_hasCodePoint
  (
    R_Utf8Reader* self
  )
{
  return self->hasCodePoint(self);
}

R_SizeValue
R_Utf8Reader_getByteIndex
  (
    R_Utf8Reader* self
  )
{
  return self->getByteIndex(self);
}
