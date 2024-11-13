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

#include "R/Utf8Reader.h"

#include "R/Object.h"
#include "R/Utf8.h"

// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Utf8Reader", R_Utf8Reader, "R.Object", R_Object, &_typeOperations);

void
R_Utf8Reader_construct
  (
    R_Utf8Reader* self
  )
{
  R_Type* _type = _R_Utf8Reader_getType();
  R_Object_construct((R_Object*)self);
  self->getCodePoint = NULL;
  self->hasCodePoint = NULL;
  self->next = NULL;
  R_Object_setType(self, _type);
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
