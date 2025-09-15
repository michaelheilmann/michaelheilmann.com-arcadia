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

#include "Arcadia/Interpreter/Method.h"

#include "Arcadia/Include.h"

static void
R_Interpreter_Method_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Interpreter_Method_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Method* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Method_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Method_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"R.Interpreter.Method", R_Interpreter_Method,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
R_Interpreter_Method_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Method* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Method_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->ready = Arcadia_BooleanValue_False;
  _self->index = Arcadia_SizeValue_Literal(0);
  _self->parameterNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  _self->unqualifiedName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  if (Arcadia_ValueStack_isForeignProcedureValue(thread, 1)) {
    _self->isForeign = Arcadia_BooleanValue_True;
    _self->foreignProcedure = Arcadia_ValueStack_getForeignProcedureValue(thread, 1);
  } else if (Arcadia_ValueStack_isObjectReferenceValue(thread, 1)) {
    _self->isForeign = Arcadia_BooleanValue_False;
    _self->code = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _R_Interpreter_Code_getType(thread));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
R_Interpreter_Method_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Method* self
  )
{
  if (!self->isForeign) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->code);
  }
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->unqualifiedName);
}

R_Interpreter_Method*
R_Interpreter_Method_createForeign
  (
    Arcadia_Thread* thread,
    Arcadia_String* unqualifiedName,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (unqualifiedName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, unqualifiedName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (foreignProcedure) {
    Arcadia_ValueStack_pushForeignProcedureValue(thread, foreignProcedure);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(R_Interpreter_Method);
}

R_Interpreter_Method*
R_Interpreter_Method_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* unqualifiedName,
    R_Interpreter_Code* code
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (unqualifiedName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, unqualifiedName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (code) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, code);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(R_Interpreter_Method);
}

R_Interpreter_Code*
R_Interpreter_Method_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Method* self
  )
{ return self->code; }
