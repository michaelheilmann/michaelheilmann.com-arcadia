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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/Utf8Reader.h"

/// @code
/// construct()
/// @endcode
static void
Arcadia_Utf8Reader_constructorImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8Reader_constructorImpl,
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

Rex_defineObjectType(u8"Arcadia.Utf8Reader", Arcadia_Utf8Reader, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Utf8Reader_constructorImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8Reader* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8Reader_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->getCodePoint = NULL;
  _self->hasCodePoint = NULL;
  _self->next = NULL;
  Arcadia_Object_setType(process, _self, _type);
}

void
Arcadia_Utf8Reader_next
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* self
  )
{
  self->next(process, self);
}

Arcadia_Natural32Value
Arcadia_Utf8Reader_getCodePoint
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* self
  )
{
  return self->getCodePoint(process, self);
}

Arcadia_BooleanValue
Arcadia_Utf8Reader_hasCodePoint
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* self
  )
{
  return self->hasCodePoint(process, self);
}

Arcadia_SizeValue
Arcadia_Utf8Reader_getByteIndex
  (
    Arcadia_Utf8Reader* self
  )
{
  return self->getByteIndex(self);
}
