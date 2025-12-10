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

#include "Arcadia/Interpreter/Procedure.h"

#include "Arcadia/Include.h"

static void
R_Interpreter_Procedure_constructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  );

static void
R_Interpreter_Procedure_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcedureDispatch* self
  );

static void
R_Interpreter_Procedure_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&R_Interpreter_Procedure_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&R_Interpreter_Procedure_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"R.Interpreter.Procedure", R_Interpreter_Procedure,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
R_Interpreter_Procedure_constructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  )
{
  Arcadia_TypeValue _type = _R_Interpreter_Procedure_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->parameterNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->unqualifiedName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  if (Arcadia_ValueStack_isForeignProcedureValue(thread, 1)) {
    self->isForeign = Arcadia_BooleanValue_True;
    self->foreignProcedure = Arcadia_ValueStack_getForeignProcedureValue(thread, 1);
  } else if (Arcadia_ValueStack_isObjectReferenceValue(thread, 1)) {
    self->isForeign = Arcadia_BooleanValue_False;
    self->code = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _R_Interpreter_Code_getType(thread));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
R_Interpreter_Procedure_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcedureDispatch* self
  )
{ }

static void
R_Interpreter_Procedure_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  )
{
  if (!self->isForeign) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->code);
  }
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->unqualifiedName);
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_createForeign
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (foreignProcedure) {
    Arcadia_ValueStack_pushForeignProcedureValue(thread, foreignProcedure);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(R_Interpreter_Procedure);
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    R_Interpreter_Code* code
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (code) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, code);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(R_Interpreter_Procedure);
}

R_Interpreter_Code*
R_Interpreter_Procedure_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  )
{ return self->code; }
