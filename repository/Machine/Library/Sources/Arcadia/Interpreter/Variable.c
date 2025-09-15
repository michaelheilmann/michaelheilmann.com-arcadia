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

#include "Arcadia/Interpreter/Variable.h"

#include "Arcadia/Interpreter/Include.h"

static void
R_Interpreter_Variable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Interpreter_Variable_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Variable_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Variable_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"R.Interpreter.Variable", R_Interpreter_Variable,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
R_Interpreter_Variable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Variable* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Variable_getType(thread);
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
  _self->class = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _R_Interpreter_Class_getType(thread));
  _self->name = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
R_Interpreter_Variable_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->class);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
}

R_Interpreter_Variable*
R_Interpreter_Variable_create
  (
    Arcadia_Thread* thread,
    R_Interpreter_Class* class,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (class) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, class);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(R_Interpreter_Variable);
}

R_Interpreter_Class*
R_Interpreter_Variable_getClass
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  )
{ return self->class; }

Arcadia_String*
R_Interpreter_Variable_getName
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  )
{ return self->name; }
