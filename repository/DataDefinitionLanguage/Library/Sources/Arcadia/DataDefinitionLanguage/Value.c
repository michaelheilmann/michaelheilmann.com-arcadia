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

#include "Arcadia/DataDefinitionLanguage/Value.h"

static void
Arcadia_DataDefinitionLanguage_Value_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Value_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Value* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Value_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Value_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Value_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Value_typeOperations = {
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Value_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Value", Arcadia_DataDefinitionLanguage_Value, u8"Arcadia.Object", Arcadia_Object, &_Arcadia_DataDefinitionLanguage_Value_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Value_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Value* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Value_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 > numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->type = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[0]);
  switch (_self->type) {
    case Arcadia_DataDefinitionLanguage_ValueType_Boolean:
    case Arcadia_DataDefinitionLanguage_ValueType_List:
    case Arcadia_DataDefinitionLanguage_ValueType_Map:
    case Arcadia_DataDefinitionLanguage_ValueType_Number:
    case Arcadia_DataDefinitionLanguage_ValueType_String:
    case Arcadia_DataDefinitionLanguage_ValueType_Void: {
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Value_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Value* self
  )
{/*Initially empty.*/}
