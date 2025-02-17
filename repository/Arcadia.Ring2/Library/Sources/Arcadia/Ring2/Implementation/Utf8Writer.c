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

// Last modified: 2025-02-15

#include "Arcadia/Ring2/Implementation/Utf8Writer.h"

static void
Arcadia_Utf8Writer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8Writer_constructImpl,
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

Rex_defineObjectType(u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Utf8Writer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8Writer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8Writer_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->writeBytes = NULL;
  _self->writeCodePoints = NULL;
  Arcadia_Object_setType(process, _self, _type);
}

void
Arcadia_Utf8Writer_writeBytes
  (
    Arcadia_Process* process,
    Arcadia_Utf8Writer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  self->writeBytes(process, self, bytes, numberOfBytes);
}

void
Arcadia_Utf8Writer_writeCodePoints
  (
    Arcadia_Process* process,
    Arcadia_Utf8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  self->writeCodePoints(process, self, codePoints, numberOfCodePoints);
}
