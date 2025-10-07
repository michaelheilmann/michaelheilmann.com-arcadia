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

#include "Arcadia/Interpreter/Constructor.h"

#include "Arcadia/Interpreter/Include.h"

static void
R_Interpreter_Constructor_constructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  );

static void
R_Interpreter_Constructor_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & R_Interpreter_Constructor_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Constructor_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"R.Interpreter.Constructor", R_Interpreter_Constructor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
R_Interpreter_Constructor_constructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  )
{
  Arcadia_TypeValue _type = _R_Interpreter_Constructor_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_ValueStack_isForeignProcedureValue(thread, 1)) {
    self->isForeign = Arcadia_BooleanValue_True;
    self->foreignProcedure = Arcadia_ValueStack_getForeignProcedureValue(thread, 1);
  } else if (Arcadia_ValueStack_getObjectReferenceValue(thread, 1)) {
    self->isForeign = Arcadia_BooleanValue_False;
    self->code = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _R_Interpreter_Code_getType(thread));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
R_Interpreter_Constructor_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  )
{
  if (!self->isForeign) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->code);
  }
}

R_Interpreter_Constructor*
R_Interpreter_Constructor_createForeign
  (
    Arcadia_Thread* thread,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (foreignProcedure) {
    Arcadia_ValueStack_pushForeignProcedureValue(thread, foreignProcedure);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(R_Interpreter_Constructor);
}

R_Interpreter_Constructor*
R_Interpreter_Constructor_create
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* code
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (code) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, code);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(R_Interpreter_Constructor);
}

R_Interpreter_Code*
R_Interpreter_Constructor_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  )
{ return self->code; }
