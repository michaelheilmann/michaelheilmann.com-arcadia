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

#include "Arcadia/MIL/Frontend/Asts/InvokeExpressionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/// @code
/// construct(callee:Arcadia.MIL.VariableOperandAst,operands:Arcadia.List)
/// @endcode
static void
Arcadia_MIL_InvokeExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_InvokeExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_InvokeExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_InvokeExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_InvokeExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_InvokeExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_InvokeExpressionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_InvokeExpressionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.InvokeExpressionAst", Arcadia_MIL_InvokeExpressionAst,
                         u8"Arcadia.MIL.ExpressionAst", Arcadia_MIL_ExpressionAst,
                         &_Arcadia_MIL_InvokeExpressionAst_typeOperations);

void
Arcadia_MIL_InvokeExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_InvokeExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_InvokeExpressionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->callee = (Arcadia_MIL_VariableOperandAst*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_MIL_VariableOperandAst_getType(thread));
  _self->operands = (Arcadia_List*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_List_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_InvokeExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_InvokeExpressionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->callee);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->operands);
}

Arcadia_MIL_InvokeExpressionAst*
Arcadia_MIL_InvokeExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_VariableOperandAst* callee,
    Arcadia_List* operands
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (callee) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, callee);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (operands) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operands);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_InvokeExpressionAst);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
