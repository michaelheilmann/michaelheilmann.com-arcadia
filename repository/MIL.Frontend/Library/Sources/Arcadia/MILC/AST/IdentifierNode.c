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

#include "Arcadia/MILC/AST/IdentifierNode.h"

#include "Arcadia/MILC/AST/Include.h"

static void
Arcadia_MILC_AST_IdentifierNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* self
  );

static void
Arcadia_MILC_AST_IdentifierNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNodeDispatch* self
  );

static void
Arcadia_MILC_AST_IdentifierNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_IdentifierNode_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_IdentifierNode_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_IdentifierNode_visitImpl
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.IdentifierNode", Arcadia_MILC_AST_IdentifierNode,
                         u8"Arcadia.MILC.AST.Node", Arcadia_MILC_AST_Node,
                         &_typeOperations);

static void
Arcadia_MILC_AST_IdentifierNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_IdentifierNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->names = (Arcadia_ImmutableList*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ImmutableList_getType(thread));
  if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->names)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_IdentifierNode);
}

static void
Arcadia_MILC_AST_IdentifierNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_IdentifierNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* self
  )
{ 
  if (self->names) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->names);
  }
}

Arcadia_MILC_AST_IdentifierNode*
Arcadia_MILC_AST_IdentifierNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* names
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (names) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, names);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_IdentifierNode);
}
