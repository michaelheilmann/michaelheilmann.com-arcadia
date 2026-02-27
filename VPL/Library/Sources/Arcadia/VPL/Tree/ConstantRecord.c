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

#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/Tree/ConstantRecord.h"

static void
Arcadia_VPL_Tree_ConstantRecord_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecord* self
  );

static void
Arcadia_VPL_Tree_ConstantRecord_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordDispatch* self
  );

static void
Arcadia_VPL_Tree_ConstantRecord_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecord* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Tree_ConstantRecord_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Tree_ConstantRecord_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Tree.ConstantRecord", Arcadia_VPL_Tree_ConstantRecord,
                         u8"Arcadia.VPL.Tree.Node", Arcadia_VPL_Tree_Node,
                         &_typeOperations);

static void
Arcadia_VPL_Tree_ConstantRecord_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecord* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Tree_ConstantRecord);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_VPL_Tree_NodeFlags_ConstantRecord);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  self->fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_LeaveConstructor(Arcadia_VPL_Tree_ConstantRecord);
}

static void
Arcadia_VPL_Tree_ConstantRecord_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_VPL_Tree_ConstantRecord_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecord* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->fields) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fields);
  }
}

Arcadia_VPL_Tree_ConstantRecord*
Arcadia_VPL_Tree_ConstantRecord_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Tree_ConstantRecord);
}
