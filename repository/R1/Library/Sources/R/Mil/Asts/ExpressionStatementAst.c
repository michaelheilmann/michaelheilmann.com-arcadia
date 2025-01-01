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

#include "R/Mil/Asts/ExpressionStatementAst.h"

#include "R/ArgumentsValidation.h"
#include "R/Mil/Asts/ExpressionAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(targetVariableName : R.String, expression : Mil.ExpressionAst)
/// @endcode
static void
R_Mil_ExpressionStatementAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_ExpressionStatementAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ExpressionStatementAst* self
  );

static const R_ObjectType_Operations _R_Mil_ExpressionStatementAst_objectTypeOperations = {
  .construct = &R_Mil_ExpressionStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ExpressionStatementAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_ExpressionStatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ExpressionStatementAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, u8"R.Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_ExpressionStatementAst_typeOperations);

static void
R_Mil_ExpressionStatementAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_ExpressionStatementAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_ExpressionStatementAst_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
 
  if (2 != numberOfArgumentValues) {
     Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
     Arcadia_Process_jump(process);
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(R_Object_getType(R_Value_getObjectReferenceValue(&argumentValues[0])), _R_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[1])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(R_Object_getType(R_Value_getObjectReferenceValue(&argumentValues[1])), _R_Mil_ExpressionAst_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  
  _self->targetVariableName = (R_String*)R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->expression =  (R_Mil_ExpressionAst*)R_Value_getObjectReferenceValue(&argumentValues[1]);
  R_Object_setType(_self, _type);
}

static void
R_Mil_ExpressionStatementAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ExpressionStatementAst* self
  )
{
  R_Object_visit(self->targetVariableName);
  R_Object_visit(self->expression);
}

R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    Arcadia_Process* process,
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)targetVariableName },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)expression } };
  R_Mil_ExpressionStatementAst* self = R_allocateObject(process, _R_Mil_ExpressionStatementAst_getType(process), 2, &argumentValues[0]);
  return self;
}

R_String*
R_Mil_ExpressionStatementAst_getTargetVariableName
  (
    R_Mil_ExpressionStatementAst* self
  )
{ return self->targetVariableName; }

R_Mil_ExpressionAst*
R_Mil_ExpressionStatementAst_getExpression
  (
    R_Mil_ExpressionStatementAst* self
  )
{ return self->expression; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
