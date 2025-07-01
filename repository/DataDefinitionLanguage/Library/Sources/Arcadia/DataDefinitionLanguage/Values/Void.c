// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/DataDefinitionLanguage/Values/Void.h"

static void
Arcadia_DataDefinitionLanguage_Values_Void_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Values_Void_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_Void* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Values_Void_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Values_Void_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Values_Void_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Values_Void_typeOperations = {
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Values_Void_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Values.Void", Arcadia_DataDefinitionLanguage_Values_Void,
                         u8"Arcadia.DataDefinitionLanguage.Value", Arcadia_DataDefinitionLanguage_Value,
                         &_Arcadia_DataDefinitionLanguage_Values_Void_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Values_Void_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Values_Void* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Values_Void_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_ValueType_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  switch (Arcadia_Value_getTag(&argumentValues[0])) {
    case Arcadia_ValueTag_Void: {
      _self->value = Arcadia_ImmutableUtf8String_createFromBoolean(thread, Arcadia_Value_getVoidValue(&argumentValues[0]));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Values_Void_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_Void* self
  )
{
  if (self->value) {
    Arcadia_ImmutableUtf8String_visit(thread, self->value);
  }
}

Arcadia_DataDefinitionLanguage_Values_Void*
Arcadia_DataDefinitionLanguage_Values_Void_createVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(voidValue),
  };
  Arcadia_DataDefinitionLanguage_Values_Void* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Void_getType(thread), 1, &argumentValues[0]);
  return self;
}
