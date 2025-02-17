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

// Last modified: 2024-10-04

#include "R/Mil/Asts/ConstructorDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// constructor(constructorParameters:R.List, constructorBody:R.List)
/// @endcode
static void
Arcadia_Mil_ConstructorDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_ConstructorDefinitionAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_ConstructorDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_ConstructorDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_ConstructorDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_ConstructorDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_ConstructorDefinitionAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_ConstructorDefinitionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.ConstructorDefinitionAst", Arcadia_Mil_ConstructorDefinitionAst, u8"Arcadia.Mil.ClassMemberDefinitionAst", Arcadia_Mil_ClassMemberDefinitionAst, &_Arcadia_Mil_ConstructorDefinitionAst_typeOperations);

static void
Arcadia_Mil_ConstructorDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_ConstructorDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_ConstructorDefinitionAst_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[0], _Arcadia_String_getType(process));
  _self->constructorParameters = (Arcadia_List*)R_Argument_getObjectReferenceValue(process, &argumentValues[1], _Arcadia_List_getType(process));
  _self->constructorBody = (Arcadia_List*)R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[2], _Arcadia_List_getType(process));
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_ConstructorDefinitionAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_ConstructorDefinitionAst* self
  )
{
  Arcadia_Object_visit(process, self->nativeName);
  Arcadia_Object_visit(process, self->constructorParameters);
  Arcadia_Object_visit(process, self->constructorBody);
}

Arcadia_Mil_ConstructorDefinitionAst*
Arcadia_Mil_ConstructorDefinitionAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* nativeName,
    Arcadia_List* constructorParameters,
    Arcadia_List* constructorBody
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)constructorParameters },
    {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
  };
  if (nativeName) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[0], nativeName);
  }
  if (constructorBody) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[2], constructorBody);
  }
  Arcadia_Mil_ConstructorDefinitionAst* self = R_allocateObject(process, _Arcadia_Mil_ConstructorDefinitionAst_getType(process), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
