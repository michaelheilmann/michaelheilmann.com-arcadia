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

#define ARCADIA_DDLS_NODES_PRIVATE (1)
#include "Arcadia/DDLS/Nodes/ScalarNode.h"

static void
Arcadia_DDLS_ScalarNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNode* self
  );

static void
Arcadia_DDLS_ScalarNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNodeDispatch* self
  );

static void
Arcadia_DDLS_ScalarNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_ScalarNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDLS_ScalarNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_ScalarNode_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDLS_ScalarNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_ScalarNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.ScalarNode", Arcadia_DDLS_ScalarNode,
                         u8"Arcadia.DDLS.Node", Arcadia_DDLS_Node,
                         &_Arcadia_DDLS_ScalarNode_typeOperations);

static void
Arcadia_DDLS_ScalarNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_ScalarNode_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->name = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DDLS_ScalarNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNodeDispatch* self
  )
{ }

static void
Arcadia_DDLS_ScalarNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ScalarNode* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

Arcadia_DDLS_ScalarNode*
Arcadia_DDLS_ScalarNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_ScalarNode);
}
