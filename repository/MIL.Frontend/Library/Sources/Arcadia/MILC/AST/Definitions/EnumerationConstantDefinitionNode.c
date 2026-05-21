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

#include "Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor(variableName:Arcadia.String)
/// @endcode
static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNode* self
  );

static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNodeDispatch* self
  );

static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_EnumerationConstantDefinitionNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_EnumerationConstantDefinitionNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_EnumerationConstantDefinitionNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.EnumerationConstantDefinitionNode", Arcadia_MILC_AST_EnumerationConstantDefinitionNode,
                         u8"Arcadia.MILC.AST.DefinitionNode", Arcadia_MILC_AST_DefinitionNode,
                         &_typeOperations);

static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_EnumerationConstantDefinitionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->initializer = NULL;
  } else {
    self->initializer = (Arcadia_MILC_AST_IntegerLiteralNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_AST_IntegerLiteralNode_getType(thread));
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_EnumerationConstantDefinitionNode);
}

static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_EnumerationConstantDefinitionNode* self
  )
{
  if (self->initializer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->initializer);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name); 
  }
}

Arcadia_MILC_AST_EnumerationConstantDefinitionNode*
Arcadia_MILC_AST_EnumerationConstantDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_MILC_AST_IntegerLiteralNode* initializer
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (initializer) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, initializer);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_EnumerationConstantDefinitionNode);
}
