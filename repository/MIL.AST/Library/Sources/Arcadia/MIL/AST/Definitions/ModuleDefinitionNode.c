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

#include "Arcadia/MIL/AST/Definitions/ModuleDefinitionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(nativeName:Arcadia.String, procedureName:Arcadia.String, procedureParameters:Arcadia.List, procedureBody:Arcadia.List)
/// @endcode
static void
Arcadia_MIL_AST_ModuleDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNode* self
  );

static void
Arcadia_MIL_AST_ModuleDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNodeDispatch* self
  );

static void
Arcadia_MIL_AST_ModuleDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_AST_ModuleDefinitionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_AST_ModuleDefinitionNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MIL_AST_ModuleDefinitionNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.AST.ModuleDefinitionNode", Arcadia_MIL_AST_ModuleDefinitionNode,
                         u8"Arcadia.MIL.AST.DefinitionNode", Arcadia_MIL_AST_DefinitionNode,
                         &_typeOperations);

static void
Arcadia_MIL_AST_ModuleDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MIL_AST_ModuleDefinitionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->moduleName = (Arcadia_MIL_AST_IdentifierNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MIL_AST_IdentifierNode_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->moduleBody = NULL;
  } else {
    self->moduleBody = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }
  Arcadia_LeaveConstructor(Arcadia_MIL_AST_ModuleDefinitionNode);
}

static void
Arcadia_MIL_AST_ModuleDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_AST_ModuleDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleDefinitionNode* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleName);
  if (self->moduleBody) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleBody);
  }
}

Arcadia_MIL_AST_ModuleDefinitionNode*
Arcadia_MIL_AST_ModuleDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_IdentifierNode* moduleName,
    Arcadia_List* moduleBody
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (moduleName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, moduleName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (moduleBody) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, moduleBody);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_ModuleDefinitionNode);
}
