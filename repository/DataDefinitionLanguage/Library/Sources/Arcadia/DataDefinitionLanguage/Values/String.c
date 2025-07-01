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

#include "Arcadia/DataDefinitionLanguage/Values/String.h"

static void
Arcadia_DataDefinitionLanguage_Values_String_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Values_String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_String* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Values_String_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Values_String_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Values_String_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Values_String_typeOperations = {
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Values_String_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Values.String", Arcadia_DataDefinitionLanguage_Values_String,
                         u8"Arcadia.DataDefinitionLanguage.Value", Arcadia_DataDefinitionLanguage_Value,
                         &_Arcadia_DataDefinitionLanguage_Values_String_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Values_String_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Values_String* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Values_String_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_ValueType_String),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  switch (Arcadia_Value_getTag(&argumentValues[0])) {
    case Arcadia_ValueTag_ImmutableUtf8String: {

    } break;
    default: {

    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Values_String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_String* self
  )
{
  if (self->value) {
    Arcadia_ImmutableUtf8String_visit(thread, self->value);
  }
}

Arcadia_DataDefinitionLanguage_Values_String*
Arcadia_DataDefinitionLanguage_Values_String_createImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8String
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeImmutableUtf8StringValue(immutableUtf8String),
  };
  Arcadia_DataDefinitionLanguage_Values_String* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_String_getType(thread), 1, &argumentValues[0]);
  return self;
}