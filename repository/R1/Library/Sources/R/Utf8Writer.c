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

// Last modified: 2024-10-07

#include "R/Utf8Writer.h"

#include "R/Object.h"
#include "R/Value.h"
#include "R/cstdlib.h"

static void
R_Utf8Writer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Utf8Writer_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"R.Utf8Writer", R_Utf8Writer, u8"R.Object", R_Object, &_typeOperations);

static void
R_Utf8Writer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Utf8Writer* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Utf8Writer_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    R_Object_constructImpl(process, self, 0, &argumentValues[0]);
  }
  _self->writeBytes = NULL;
  _self->writeCodePoints = NULL;
  R_Object_setType(_self, _type);
}

void
R_Utf8Writer_writeBytes
  (
    Arcadia_Process* process,
    R_Utf8Writer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  self->writeBytes(process, self, bytes, numberOfBytes);
}

void
R_Utf8Writer_writeCodePoints
  (
    Arcadia_Process* process,
    R_Utf8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  self->writeCodePoints(process, self, codePoints, numberOfCodePoints);
}
