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

#include "Arcadia/MIL/Frontend/Asts/UnaryExpressionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(type : Arcadia.Natural32Value<Arcadia.MILUnaryExpressionAstType>, operand1 : Arcadia.MILOperandAst)
/// @endcode
static void
Arcadia_MIL_UnaryExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_UnaryExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_UnaryExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_UnaryExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_UnaryExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_UnaryExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_UnaryExpressionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_UnaryExpressionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.UnaryExpressionAst", Arcadia_MIL_UnaryExpressionAst,
                         u8"Arcadia.MIL.ExpressionAst", Arcadia_MIL_ExpressionAst,
                         &_Arcadia_MIL_UnaryExpressionAst_typeOperations);

static void
Arcadia_MIL_UnaryExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_UnaryExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_UnaryExpressionAst_getType(thread);
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
  _self->type = Arcadia_ValueStack_getInteger32Value(thread, 2);
  _self->operand1 = (Arcadia_MIL_OperandAst*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MIL_OperandAst_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_UnaryExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_UnaryExpressionAst* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->operand1); }

Arcadia_MIL_UnaryExpressionAst*
Arcadia_MIL_UnaryExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_UnaryExpressionAstType type,
    Arcadia_MIL_OperandAst* operand1
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, type);
  if (operand1) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, operand1);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_UnaryExpressionAst);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
