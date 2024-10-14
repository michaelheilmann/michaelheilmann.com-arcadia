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

#include "R/Utf8Writer.h"

#include "R/Object.h"

// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

Rex_defineObjectType("R.Utf8Writer", R_Utf8Writer, "R.Object", R_Object, NULL, NULL);

void
R_Utf8Writer_construct
  (
    R_Utf8Writer* self
  )
{
  R_Type* _type = _R_Utf8Writer_getType();
  R_Object_construct((R_Object*)self);
  self->writeBytes = NULL;
  self->writeCodePoints = NULL;
  R_Object_setType(self, _type);
}

void
R_Utf8Writer_writeBytes
  (
    R_Utf8Writer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  self->writeBytes(self, bytes, numberOfBytes);
}

void
R_Utf8Writer_writeCodePoints
  (
    R_Utf8Writer* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  )
{
  self->writeCodePoints(self, codePoints, numberOfCodePoints);
}
