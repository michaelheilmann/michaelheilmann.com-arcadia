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

#include "Arcadia/DataDefinitionLanguage/Values/Number.h"

static void
Arcadia_DataDefinitionLanguage_Values_Number_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Values_Number_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_Number* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Values_Number_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Values_Number_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Values_Number_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Values_Number_typeOperations = {
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Values_Number_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Values.Number", Arcadia_DataDefinitionLanguage_Values_Number,
                         u8"Arcadia.DataDefinitionLanguage.Value", Arcadia_DataDefinitionLanguage_Value,
                         &_Arcadia_DataDefinitionLanguage_Values_Number_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Values_Number_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Values_Number* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_ValueType_Number),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  switch (Arcadia_Value_getTag(&argumentValues[0])) {
    case Arcadia_ValueTag_Integer16: {
      _self->value = Arcadia_ImmutableUtf8String_createFromInteger16(thread, Arcadia_Value_getInteger16Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer32: {
      _self->value = Arcadia_ImmutableUtf8String_createFromInteger32(thread, Arcadia_Value_getInteger32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer64: {
      _self->value = Arcadia_ImmutableUtf8String_createFromInteger64(thread, Arcadia_Value_getInteger64Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer8: {
      _self->value = Arcadia_ImmutableUtf8String_createFromInteger8(thread, Arcadia_Value_getInteger8Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural16: {
      _self->value = Arcadia_ImmutableUtf8String_createFromNatural16(thread, Arcadia_Value_getNatural16Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural32: {
      _self->value = Arcadia_ImmutableUtf8String_createFromNatural32(thread, Arcadia_Value_getNatural32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural64: {
      _self->value = Arcadia_ImmutableUtf8String_createFromNatural64(thread, Arcadia_Value_getNatural64Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural8: {
      _self->value = Arcadia_ImmutableUtf8String_createFromNatural8(thread, Arcadia_Value_getNatural8Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Real32: {
      _self->value = Arcadia_ImmutableUtf8String_createFromReal32(thread, Arcadia_Value_getReal32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Real64: {
      _self->value = Arcadia_ImmutableUtf8String_createFromReal64(thread, Arcadia_Value_getReal64Value(&argumentValues[0]));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Values_Number_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Values_Number* self
  )
{
  if (self->value) {
    Arcadia_ImmutableUtf8String_visit(thread, self->value);
  }
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger32Value(integer32Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger64Value(integer64Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger8Value(integer8Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural16Value(natural16Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural32Value(natural32Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural64Value(natural64Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural8Value(natural8Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeReal32Value(real32Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Values_Number*
Arcadia_DataDefinitionLanguage_Values_Number_createReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeReal64Value(real64Value),
  };
  Arcadia_DataDefinitionLanguage_Values_Number* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Values_Number_getType(thread), 1, &argumentValues[0]);
  return self;
}
