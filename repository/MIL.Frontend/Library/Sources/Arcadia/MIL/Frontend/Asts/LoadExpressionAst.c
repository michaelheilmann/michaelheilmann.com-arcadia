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

#include "Arcadia/MIL/Frontend/Asts/LoadExpressionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/// @code
/// construct(expression : Arcadia.MILOperandAst)
/// @endcode
static void
Arcadia_MIL_LoadExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_LoadExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_LoadExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_LoadExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_LoadExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_LoadExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_LoadExpressionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_LoadExpressionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.LoadExpressionAst", Arcadia_MIL_LoadExpressionAst,
                         u8"Arcadia.MIL.ExpressionAst", Arcadia_MIL_ExpressionAst,
                         &_Arcadia_MIL_LoadExpressionAst_typeOperations);

static void
Arcadia_MIL_LoadExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_LoadExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_LoadExpressionAst_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->operand = (Arcadia_MIL_OperandAst*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MIL_OperandAst_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_MIL_LoadExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_LoadExpressionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->operand);
}

Arcadia_MIL_LoadExpressionAst*
Arcadia_MIL_LoadExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_OperandAst* operand
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (operand) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operand);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_LoadExpressionAst);
}

