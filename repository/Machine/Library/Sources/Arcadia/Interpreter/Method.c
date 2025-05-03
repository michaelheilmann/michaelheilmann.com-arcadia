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
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"R.Interpreter.Method", R_Interpreter_Method, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

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
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->ready = Arcadia_BooleanValue_False;
  _self->index = Arcadia_SizeValue_Literal(0);
  _self->parameterNames = Arcadia_List_create(thread);
  _self->unqualifiedName = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  if (Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &argumentValues[1]), _Arcadia_ForeignProcedureValue_getType(thread))) {
    _self->isForeign = Arcadia_BooleanValue_True;
    _self->foreignProcedure = Arcadia_Value_getForeignProcedureValue(&argumentValues[1]);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &argumentValues[1]), _R_Interpreter_Code_getType(thread))) {
    _self->isForeign = Arcadia_BooleanValue_False;
    _self->code = Arcadia_Value_getObjectReferenceValue(&argumentValues[1]);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
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
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(unqualifiedName),
    Arcadia_Value_makeForeignProcedureValue(foreignProcedure),
  };
  R_Interpreter_Method* self = Arcadia_allocateObject(thread, _R_Interpreter_Method_getType(thread), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Method*
R_Interpreter_Method_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* unqualifiedName,
    R_Interpreter_Code* code
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(unqualifiedName),
    Arcadia_Value_makeObjectReferenceValue(code),
  };
  R_Interpreter_Method* self = Arcadia_allocateObject(thread, _R_Interpreter_Method_getType(thread), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Interpreter_Method_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Method* self
  )
{ return self->code; }
