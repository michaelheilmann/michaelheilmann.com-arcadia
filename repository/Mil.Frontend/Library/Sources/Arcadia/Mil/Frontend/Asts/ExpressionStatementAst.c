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

#include "Arcadia/Mil/Frontend/Asts/ExpressionStatementAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

/// @code
/// construct(targetVariableName : Arcadia.String, expression : Mil.ExpressionAst)
/// @endcode
static void
Arcadia_Mil_ExpressionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_ExpressionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ExpressionStatementAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_ExpressionStatementAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_ExpressionStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_ExpressionStatementAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_ExpressionStatementAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_ExpressionStatementAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.ExpressionStatementAst", Arcadia_Mil_ExpressionStatementAst, u8"Arcadia.Mil.StatementAst", Arcadia_Mil_StatementAst, &_Arcadia_Mil_ExpressionStatementAst_typeOperations);

static void
Arcadia_Mil_ExpressionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_ExpressionStatementAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_ExpressionStatementAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
     Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
     Arcadia_Thread_jump(thread);
  }
  _self->targetVariableName = (Arcadia_String*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->expression = (Arcadia_Mil_ExpressionAst*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_Mil_ExpressionAst_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_ExpressionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ExpressionStatementAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->targetVariableName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->expression);
}

Arcadia_Mil_ExpressionStatementAst*
Arcadia_Mil_ExpressionStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* targetVariableName,
    Arcadia_Mil_ExpressionAst* expression
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(targetVariableName),
    Arcadia_Value_makeObjectReferenceValue(expression),
  };
  Arcadia_Mil_ExpressionStatementAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_ExpressionStatementAst_getType(thread), 2, &argumentValues[0]);
  return self;
}

Arcadia_String*
Arcadia_Mil_ExpressionStatementAst_getTargetVariableName
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ExpressionStatementAst* self
  )
{ return self->targetVariableName; }

Arcadia_Mil_ExpressionAst*
Arcadia_Mil_ExpressionStatementAst_getExpression
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ExpressionStatementAst* self
  )
{ return self->expression; }

