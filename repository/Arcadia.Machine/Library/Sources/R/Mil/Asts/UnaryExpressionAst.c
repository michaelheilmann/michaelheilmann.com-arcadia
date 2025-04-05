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

#include "R/Mil/Asts/UnaryExpressionAst.h"

#include "R/ArgumentsValidation.h"
#include "R/Mil/Ast.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(type : Arcadia.Natural32Value<Arcadia.MilUnaryExpressionAstType>, operand1 : Arcadia.MilOperandAst)
/// @endcode
static void
Arcadia_Mil_UnaryExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_UnaryExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_UnaryExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_UnaryExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_UnaryExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_UnaryExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_UnaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_UnaryExpressionAst_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.Mil.UnaryExpressionAst", Arcadia_Mil_UnaryExpressionAst, u8"Arcadia.Mil.ExpressionAst", Arcadia_Mil_ExpressionAst, &_Arcadia_Mil_UnaryExpressionAst_typeOperations);

static void
Arcadia_Mil_UnaryExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_UnaryExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_UnaryExpressionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Value_isInteger32Value(&argumentValues[0])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->type = Arcadia_Value_getInteger32Value(&argumentValues[0]);
  _self->operand1 = (Arcadia_Mil_OperandAst*)R_Argument_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_Mil_OperandAst_getType(thread));
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_UnaryExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_UnaryExpressionAst* self
  )
{ Arcadia_Object_visit(thread, self->operand1); }

Arcadia_Mil_UnaryExpressionAst*
Arcadia_Mil_UnaryExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_UnaryExpressionAstType type,
    Arcadia_Mil_OperandAst* operand1
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = type },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)operand1 }, };
  Arcadia_Mil_UnaryExpressionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_UnaryExpressionAst_getType(thread), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
