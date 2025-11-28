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

#define ARCADIA_DDL_NODES_PRIVATE (1)
#include "Arcadia/DDL/Nodes/Node.h"

static void
Arcadia_DDL_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* self
  );

static void
Arcadia_DDL_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDL_Node_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDL_Node_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_Node_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDL_Node_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDL_Node_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.Node", Arcadia_DDL_Node,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_DDL_Node_typeOperations);

static void
Arcadia_DDL_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_Node_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->type = Arcadia_ValueStack_getInteger32Value(thread, 1);
  switch (self->type) {
    case Arcadia_DDL_NodeType_Boolean:
    case Arcadia_DDL_NodeType_List:
    case Arcadia_DDL_NodeType_Map:
    case Arcadia_DDL_NodeType_MapEntry:
    case Arcadia_DDL_NodeType_Name:
    case Arcadia_DDL_NodeType_Number:
    case Arcadia_DDL_NodeType_String:
    case Arcadia_DDL_NodeType_Void: {
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_DDL_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* self
  )
{/*Initially empty.*/}
