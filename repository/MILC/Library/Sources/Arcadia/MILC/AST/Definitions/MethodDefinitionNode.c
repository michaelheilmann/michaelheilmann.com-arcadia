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

#include "Arcadia/MILC/AST/Definitions/MethodDefinitionNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor(methodName:Arcadia.String, methodParameters:Arcadia.List, methodBody:Arcadia.List)
/// @endcode
static void
Arcadia_MILC_AST_MethodDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNode* self
  );

static void
Arcadia_MILC_AST_MethodDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNodeDispatch* self
  );

static void
Arcadia_MILC_AST_MethodDefinitionNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_MethodDefinitionNode_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_MethodDefinitionNode_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_MethodDefinitionNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.MethodDefinitionNode", Arcadia_MILC_AST_MethodDefinitionNode,
                         u8"Arcadia.MILC.AST.DefinitionNode", Arcadia_MILC_AST_DefinitionNode,
                         &_typeOperations);

static void
Arcadia_MILC_AST_MethodDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_MethodDefinitionNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (5 !=_numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 5)) {
    self->nativeName = NULL;
  } else {
    self->nativeName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 5, _Arcadia_String_getType(thread));
  }
  self->name = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_String_getType(thread));
  self->parameters = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_List_getType(thread));
  self->returnType = (Arcadia_MILC_AST_IdentifierNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_AST_IdentifierNode_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->body = NULL;
  } else {
    self->body = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_MethodDefinitionNode);
}

static void
Arcadia_MILC_AST_MethodDefinitionNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_MethodDefinitionNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_MethodDefinitionNode* self
  )
{
  if (self->nativeName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->nativeName);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->parameters) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameters);
  }
  if (self->returnType) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->returnType);
  }
  if (self->body) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->body);
  }
}

Arcadia_MILC_AST_MethodDefinitionNode*
Arcadia_MILC_AST_MethodDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_String* name,
    Arcadia_List* parameters,
    Arcadia_MILC_AST_IdentifierNode* returnType,
    Arcadia_List* body
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_AST_MethodDefinitionNode);
  if (nativeName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, nativeName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (parameters) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, parameters);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (returnType) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, returnType);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (body) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, body);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  _Arcadia_EndCreate(Arcadia_MILC_AST_MethodDefinitionNode);
}
