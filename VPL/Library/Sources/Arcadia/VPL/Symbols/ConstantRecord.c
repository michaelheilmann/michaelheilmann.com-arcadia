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
#include "Arcadia/VPL/Symbols/ConstantRecord.h"

#include "Arcadia/VPL/Program.h"
#include <string.h>

static void
Arcadia_VPL_ConstantRecord_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  );

static void
Arcadia_VPL_ConstantRecord_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordDispatch* self
  );

static void
Arcadia_VPL_ConstantRecord_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  );

static Arcadia_VPL_ConstantKind
Arcadia_VPL_ConstantRecord_getKindImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  );

static Arcadia_String*
Arcadia_VPL_ConstantRecord_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_ConstantRecord_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_ConstantRecord_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.ConstantRecord", Arcadia_VPL_ConstantRecord,
                         u8"Arcadia.VPL.Constant", Arcadia_VPL_Constant,
                         &_typeOperations);

static void
Arcadia_VPL_ConstantRecord_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_ConstantRecord);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_VPL_Program_getType(thread));
  self->fields = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  self->mappedName = NULL;
  self->scope = NULL;
  Arcadia_LeaveConstructor(Arcadia_VPL_ConstantRecord);
}

static void
Arcadia_VPL_ConstantRecord_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecordDispatch* self
  )
{ 
  ((Arcadia_VPL_ConstantDispatch*)self)->getKind = (Arcadia_VPL_ConstantKind (*)(Arcadia_Thread*, Arcadia_VPL_Constant*))&Arcadia_VPL_ConstantRecord_getKindImpl;
  ((Arcadia_VPL_ConstantDispatch*)self)->getName = (Arcadia_String*(*)(Arcadia_Thread*, Arcadia_VPL_Constant*)) & Arcadia_VPL_ConstantRecord_getNameImpl;
}

static void
Arcadia_VPL_ConstantRecord_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->program) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->program);
  }
  if (self->fields) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fields);
  }

  if (self->mappedName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->mappedName);
  }
  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fields);
  }
}

static Arcadia_VPL_ConstantKind
Arcadia_VPL_ConstantRecord_getKindImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  )
{ return Arcadia_VPL_ConstantKind_Record; }

static Arcadia_String*
Arcadia_VPL_ConstantRecord_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  )
{ return self->name; }

Arcadia_VPL_ConstantRecord*
Arcadia_VPL_ConstantRecord_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_VPL_Program* program,
    Arcadia_List* fields
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (program) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)program);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (fields) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)fields);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_ConstantRecord);
}

Arcadia_List*
Arcadia_VPL_ConstantRecord_getFields
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ConstantRecord* self
  )
{ return self->fields; }
