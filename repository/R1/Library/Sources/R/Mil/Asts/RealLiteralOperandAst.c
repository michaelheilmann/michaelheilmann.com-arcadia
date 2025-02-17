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

#include "R/Mil/Ast.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Mil_RealLiteralOperandAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_RealLiteralOperandAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_RealLiteralOperandAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_RealLiteralOperandAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_RealLiteralOperandAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_RealLiteralOperandAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_RealLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_RealLiteralOperandAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.RealLiteralOperandAst", Arcadia_Mil_RealLiteralOperandAst, u8"Arcadia.Mil.OperandAst", Arcadia_Mil_OperandAst, &_Arcadia_Mil_RealLiteralOperandAst_typeOperations);

static void
Arcadia_Mil_RealLiteralOperandAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_RealLiteralOperandAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_IntegerLiteralOperandAst_getType(process);

  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Value_isObjectReferenceValue(&argumentValues[0])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Object* objectValue = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!Arcadia_Type_isSubType(Arcadia_Object_getType(objectValue), _Arcadia_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* stringValue = (Arcadia_String*)objectValue;
  _self->value = stringValue;
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_RealLiteralOperandAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_RealLiteralOperandAst* self
  )
{ Arcadia_Object_visit(process, self->value); }

Arcadia_Mil_RealLiteralOperandAst*
Arcadia_Mil_RealLiteralOperandAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* value
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)value } };
  Arcadia_Mil_RealLiteralOperandAst* self = R_allocateObject(process, _Arcadia_Mil_RealLiteralOperandAst_getType(process), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
