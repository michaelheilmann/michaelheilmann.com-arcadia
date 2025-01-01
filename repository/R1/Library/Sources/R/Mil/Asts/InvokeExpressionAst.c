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

// Last modified: 2025-01-01

#include "R/Mil/Asts/InvokeExpressionAst.h"

#include "R/ArgumentsValidation.h"
#include "R/Mil/Asts/VariableOperandAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(callee:R.Mil.VariableOperandAst,operands:R.List)
/// @endcode
static void
R_Mil_InvokeExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_InvokeExpressionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_InvokeExpressionAst* self
  );

static const R_ObjectType_Operations _R_Mil_InvokeExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_InvokeExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_InvokeExpressionAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_InvokeExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_InvokeExpressionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.InvokeExpressionAst", R_Mil_InvokeExpressionAst, u8"R.Object", R_Object, &_R_Mil_InvokeExpressionAst_typeOperations);

void
R_Mil_InvokeExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_InvokeExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_InvokeExpressionAst_getType(process);
  {
    R_Value argumentValues[] = { { .tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }

  if (2 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }

  if (!Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[0]), _R_Mil_VariableOperandAst_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[1]), _R_List_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }

  _self->callee = R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->operands = R_Value_getObjectReferenceValue(&argumentValues[1]);

  R_Object_setType(_self, _type);
}

static void
R_Mil_InvokeExpressionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_InvokeExpressionAst* self
  )
{
  R_Object_visit(self->callee);
  R_Object_visit(self->operands);
}

R_Mil_InvokeExpressionAst*
R_Mil_InvokeExpressionAst_create
  (
    Arcadia_Process* process,
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)callee },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operands }, };
  R_Mil_InvokeExpressionAst* self = R_allocateObject(process, _R_Mil_InvokeExpressionAst_getType(process), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
