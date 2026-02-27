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
#include "Arcadia/VPL/Symbols/ConstantRecordField.h"

#include "Arcadia/VPL/Symbols/ConstantRecord.h"
#include <string.h>

static void
Arcadia_VPL_ConstantRecordField_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordField* self
  );

static void
Arcadia_VPL_ConstantRecordField_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordFieldDispatch* self
  );

static void
Arcadia_VPL_Block_Field_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordField* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_ConstantRecordField_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.VPL.ConstantRecordField", Arcadia_VPL_ConstantRecordField,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_ConstantRecordField_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordField* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_ConstantRecordField);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->type= Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->constantRecord = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_VPL_ConstantRecord_getType(thread));
  self->typeSymbol = NULL;
  Arcadia_LeaveConstructor(Arcadia_VPL_ConstantRecordField);
}

static void
Arcadia_VPL_ConstantRecordField_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordFieldDispatch* self
  )
{ }

static void
Arcadia_VPL_Block_Field_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordField* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->type);
  }
  if (self->constantRecord) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->constantRecord);
  }
  if (self->typeSymbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->typeSymbol);
  }
}

Arcadia_VPL_ConstantRecordField*
Arcadia_VPL_ConstantRecordField_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type,
    Arcadia_VPL_ConstantRecord* constantRecord
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (type) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)type);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (constantRecord) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)constantRecord);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_ConstantRecordField);
}
