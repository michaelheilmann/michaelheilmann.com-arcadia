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

#include "Arcadia/MILC/AST/Literals/BooleanLiteralNode.h"

#include "Arcadia/MILC/AST/Include.h"

static void
Arcadia_MILC_AST_BooleanLiteralNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNode* self
  );

static void
Arcadia_MILC_AST_BooleanLiteralNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNodeDispatch* self
  );

static void
Arcadia_MILC_AST_BooleanLiteralNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MILC_AST_BooleanLiteralNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_BooleanLiteralNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_BooleanLiteralNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_BooleanLiteralNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_MILC_AST_BooleanLiteralNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MILC_AST_BooleanLiteralNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.BooleanLiteralNode", Arcadia_MILC_AST_BooleanLiteralNode,
                         u8"Arcadia.MILC.AST.Node", Arcadia_MILC_AST_Node,
                         &_Arcadia_MILC_AST_BooleanLiteralNode_typeOperations);

static void
Arcadia_MILC_AST_BooleanLiteralNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_BooleanLiteralNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->value = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));

  Arcadia_LeaveConstructor(Arcadia_MILC_AST_BooleanLiteralNode);
}

static void
Arcadia_MILC_AST_BooleanLiteralNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_BooleanLiteralNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BooleanLiteralNode* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->value); }

Arcadia_MILC_AST_BooleanLiteralNode*
Arcadia_MILC_AST_BooleanLiteralNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (value) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, value);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_BooleanLiteralNode);
}
