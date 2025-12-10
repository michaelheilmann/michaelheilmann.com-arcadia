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

#define ARCADIA_DDL_NODES_PRIVATE (1)
#include "Arcadia/DDL/Nodes/NameNode.h"

static void
Arcadia_DDL_NameNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* self
  );

static void
Arcadia_DDL_NameNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNodeDispatch* self
  );

static void
Arcadia_DDL_NameNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDL_NameNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDL_NameNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDL_NameNode_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDL_NameNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDL_NameNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDL.NameNode", Arcadia_DDL_NameNode,
                         u8"Arcadia.DDL.Node", Arcadia_DDL_Node,
                         &_Arcadia_DDL_NameNode_typeOperations);

static inline Arcadia_BooleanValue
isFirst
  (
    Arcadia_Natural8Value byte
  )
{
  return '_' == byte
      || ('a' <= byte && byte <= 'z')
      || ('A' <= byte && byte <= 'Z');
}

static inline Arcadia_BooleanValue
isRest
  (
    Arcadia_Natural8Value byte
  )
{
  return '_' == byte
    || ('a' <= byte && byte <= 'z')
    || ('A' <= byte && byte <= 'Z')
    || ('0' <= byte && byte <= '9');
}

static void
Arcadia_DDL_NameNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDL_NameNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDL_NodeType_Name);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1);
  switch (Arcadia_Value_getTag(&x)) {
    case Arcadia_ValueTag_ObjectReference: {
      self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &x, _Arcadia_String_getType(thread));
      Arcadia_Natural8Value const* start = Arcadia_String_getBytes(thread, self->value);
      Arcadia_Natural8Value const* end = start + Arcadia_String_getNumberOfBytes(thread, self->value);
      Arcadia_Natural8Value const* current = start;
      if (current == end || !isFirst(*current)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      do {
        current++;
      } while (current != end && isRest(*current));
      if (current != end) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_DDL_NameNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNodeDispatch* self
  )
{ }

static void
Arcadia_DDL_NameNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_NameNode* self
  )
{
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

Arcadia_DDL_NameNode*
Arcadia_DDL_NameNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (string) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, string);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DDL_NameNode);
}
