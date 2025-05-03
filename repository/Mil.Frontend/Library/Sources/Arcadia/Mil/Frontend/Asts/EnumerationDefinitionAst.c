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

#include "Arcadia/Mil/Frontend/Asts/EnumerationDefinitionAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

static void
Arcadia_Mil_EnumerationDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_EnumerationDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_EnumerationDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_EnumerationDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_EnumerationDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_EnumerationDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_EnumerationDefinitionAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_EnumerationDefinitionAst_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.Mil.EnumerationDefinitionAst", Arcadia_Mil_EnumerationDefinitionAst, u8"Arcadia.Mil.Ast", Arcadia_Mil_Ast, &_Arcadia_Mil_EnumerationDefinitionAst_typeOperations);

static void
Arcadia_Mil_EnumerationDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{ 
  Arcadia_Mil_EnumerationDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_EnumerationDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->enumerationName = (Arcadia_String*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->enumerationBody = (Arcadia_List*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[2], _Arcadia_List_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_EnumerationDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_EnumerationDefinitionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->enumerationName);
  if (self->enumerationBody) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enumerationBody);
  }
}

Arcadia_Mil_EnumerationDefinitionAst*
Arcadia_Mil_EnumerationDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* enumerationName,
    Arcadia_String* extendedClassName,
    Arcadia_List* enumerationBody
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = enumerationName },
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = enumerationBody },
  };
  Arcadia_Mil_EnumerationDefinitionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_EnumerationDefinitionAst_getType(thread), 3, &argumentValues[0]);
  return self;
}
