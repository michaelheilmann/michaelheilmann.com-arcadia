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
#include "Arcadia/VPL/Tree/ConstantRecordField.h"

static void
Arcadia_VPL_Tree_ConstantRecordField_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordField* self
  );

static void
Arcadia_VPL_Tree_ConstantRecordField_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordFieldDispatch* self
  );

static void
Arcadia_VPL_Tree_ConstantRecordField_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordField* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Tree_ConstantRecordField_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Tree_ConstantRecordField_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Tree.ConstantRecordField", Arcadia_VPL_Tree_ConstantRecordField,
                         u8"Arcadia.VPL.Tree.Node", Arcadia_VPL_Tree_Node,
                         &_typeOperations);

static void
Arcadia_VPL_Tree_ConstantRecordField_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordField* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Tree_ConstantRecordField);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_VPL_Tree_NodeFlags_ConstantRecordField);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->type = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_VPL_Tree_ConstantRecordField);
}

static void
Arcadia_VPL_Tree_ConstantRecordField_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordFieldDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_VPL_Tree_ConstantRecordField_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ConstantRecordField* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->type);
  }
}

Arcadia_VPL_Tree_ConstantRecordField*
Arcadia_VPL_Tree_ConstantRecordField_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, type);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Tree_ConstantRecordField);
}
