// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/MIL/AST/Definitions/ProcedureDefinitionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(nativeName:Arcadia.String, procedureName:Arcadia.String, procedureParameters:Arcadia.List, procedureBody:Arcadia.List)
/// @endcode
static void
Arcadia_MIL_AST_ProcedureDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNode* self
  );

static void
Arcadia_MIL_AST_ProcedureDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNodeDispatch* self
  );

static void
Arcadia_MIL_AST_ProcedureDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_AST_ProcedureDefinitionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_AST_ProcedureDefinitionNode_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.AST.ProcedureDefinitionNode", Arcadia_MIL_AST_ProcedureDefinitionNode,
                         u8"Arcadia.MIL.AST.DefinitionNode", Arcadia_MIL_AST_DefinitionNode,
                         &_typeOperations);

static void
Arcadia_MIL_AST_ProcedureDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_ProcedureDefinitionNode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 5 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->entry = Arcadia_ValueStack_getBooleanValue(thread, 5);
  if (Arcadia_ValueStack_isVoidValue(thread, 4)) {
    self->nativeName = NULL;
  } else {
    self->nativeName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_String_getType(thread));
  }
  self->procedureName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->procedureParameters = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_List_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->procedureBody = NULL;
  } else {
    self->procedureBody = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 5 + 1);
}

static void
Arcadia_MIL_AST_ProcedureDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNodeDispatch* self
  )
{ }

static void
Arcadia_MIL_AST_ProcedureDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ProcedureDefinitionNode* self
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

Arcadia_MIL_AST_ProcedureDefinitionNode*
Arcadia_MIL_AST_ProcedureDefinitionNode_create
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
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_ProcedureDefinitionNode);
}
