// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-12-12

#include "R/Interpreter/Method.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static void
R_Interpreter_Method_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Interpreter_Method_visit
  (
    Arcadia_Process* process,
    R_Interpreter_Method* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
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

Rex_defineObjectType(u8"R.Interpreter.Method", R_Interpreter_Method, u8"R.Object", R_Object, &_typeOperations);

static void
R_Interpreter_Method_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Interpreter_Method* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Method_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->ready = Arcadia_BooleanValue_False;
  _self->index = Arcadia_SizeValue_Literal(0);
  _self->parameterNames = R_List_create(process);
  _self->unqualifiedName = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _R_String_getType(process));
  if (Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[1]), _Arcadia_ForeignProcedureValue_getType(process))) {
    _self->isForeign = Arcadia_BooleanValue_True;
    _self->foreignProcedure = R_Value_getForeignProcedureValue(&argumentValues[1]);
  } else if (Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[1]), _R_Interpreter_Code_getType(process))) {
    _self->isForeign = Arcadia_BooleanValue_False;
    _self->code = R_Value_getObjectReferenceValue(&argumentValues[1]);
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_Method_visit
  (
    Arcadia_Process* process,
    R_Interpreter_Method* self
  )
{
  if (!self->isForeign) {
    R_Object_visit(self->code);
  }
  R_Object_visit(self->unqualifiedName);
}

R_Interpreter_Method*
R_Interpreter_Method_createForeign
  (
    Arcadia_Process* process,
    R_String* unqualifiedName,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = unqualifiedName },
    {.tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedure },
  };
  R_Interpreter_Method* self = R_allocateObject(process, _R_Interpreter_Method_getType(process), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Method*
R_Interpreter_Method_create
  (
    Arcadia_Process* process,
    R_String* unqualifiedName,
    R_Interpreter_Code* code
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = unqualifiedName },
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = code },
  };
  R_Interpreter_Method* self = R_allocateObject(process, _R_Interpreter_Method_getType(process), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Interpreter_Method_getCode
  (
    R_Interpreter_Method* self
  )
{ return self->code; }
