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

#include "Arcadia/MIL/Frontend/Asts/ProcedureDefinitionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/// @code
/// construct(nativeName:Arcadia.String, procedureName:Arcadia.String,procedureParameters:R.List,procedureBody:List)
/// @endcode
static void
Arcadia_MIL_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_ProcedureDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ProcedureDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_ProcedureDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_ProcedureDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_ProcedureDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_ProcedureDefinitionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_ProcedureDefinitionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.ProcedureDefinitionAst", Arcadia_MIL_ProcedureDefinitionAst,
                         u8"Arcadia.MIL.Ast", Arcadia_MIL_Ast,
                         &_Arcadia_MIL_ProcedureDefinitionAst_typeOperations);

static void
Arcadia_MIL_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_ProcedureDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_ProcedureDefinitionAst_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 5 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->entry = Arcadia_ValueStack_getBooleanValue(thread, 5);
  if (Arcadia_ValueStack_isVoidValue(thread, 4)) {
    _self->nativeName = NULL;
  } else {
    _self->nativeName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_String_getType(thread));
  }
  _self->procedureName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  _self->procedureParameters = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_List_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    _self->procedureBody = NULL;
  } else {
    _self->procedureBody = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 5 + 1);
}

static void
Arcadia_MIL_ProcedureDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ProcedureDefinitionAst* self
  )
{
  if (self->nativeName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->nativeName);
  }
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureParameters);
  if (self->procedureBody) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureBody);
  }
}

Arcadia_MIL_ProcedureDefinitionAst*
Arcadia_MIL_ProcedureDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue entry,
    Arcadia_String* nativeName,
    Arcadia_String* procedureName,
    Arcadia_List* procedureParameters,
    Arcadia_List* procedureBody
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushBooleanValue(thread, entry);
  if (nativeName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, nativeName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (procedureName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, procedureName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (procedureParameters) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, procedureParameters);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (procedureBody) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, procedureBody);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_ProcedureDefinitionAst);
}
