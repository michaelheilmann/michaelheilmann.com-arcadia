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

#include "Arcadia/MIL/Frontend/Asts/VariableDefinitionStatementAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/// @code
/// construct(name:Arcadia.String)
/// @endcode
static void
Arcadia_MIL_VariableDefinitionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_VariableDefinitionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_VariableDefinitionStatementAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_VariableDefinitionStatementAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_VariableDefinitionStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_VariableDefinitionStatementAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_VariableDefinitionStatementAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_VariableDefinitionStatementAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.VariableDefinitionStatementAst", Arcadia_MIL_VariableDefinitionStatementAst,
                         u8"Arcadia.MIL.StatementAst", Arcadia_MIL_StatementAst,
                         &_Arcadia_MIL_VariableDefinitionStatementAst_typeOperations);

static void
Arcadia_MIL_VariableDefinitionStatementAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_VariableDefinitionStatementAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_VariableDefinitionStatementAst_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->variableName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_MIL_VariableDefinitionStatementAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_VariableDefinitionStatementAst* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableName); }

Arcadia_MIL_VariableDefinitionStatementAst*
Arcadia_MIL_VariableDefinitionStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* variableName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (variableName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, variableName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_VariableDefinitionStatementAst);
}
