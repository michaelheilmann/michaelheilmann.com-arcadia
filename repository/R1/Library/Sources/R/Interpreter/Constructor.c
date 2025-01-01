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

#include "R/Interpreter/Constructor.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static void
R_Interpreter_Constructor_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Interpreter_Constructor_visit
  (
    Arcadia_Process* process,
    R_Interpreter_Constructor* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Constructor_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Constructor_visit,
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

Rex_defineObjectType(u8"R.Interpreter.Constructor", R_Interpreter_Constructor, u8"R.Object", R_Object, &_typeOperations);

static void
R_Interpreter_Constructor_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Interpreter_Constructor* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Constructor_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[0]), _Arcadia_ForeignProcedureValue_getType(process))) {
    _self->isForeign = Arcadia_BooleanValue_True;
    _self->foreignProcedure = R_Value_getForeignProcedureValue(&argumentValues[0]);
  } else if (Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[0]), _R_Interpreter_Code_getType(process))) {
    _self->isForeign = Arcadia_BooleanValue_False;
    _self->code = R_Value_getObjectReferenceValue(&argumentValues[0]);
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_Constructor_visit
  (
    Arcadia_Process* process,
    R_Interpreter_Constructor* self
  )
{
  if (!self->isForeign) {
    R_Object_visit(self->code);
  }
}

R_Interpreter_Constructor*
R_Interpreter_Constructor_createForeign
  (
    Arcadia_Process* process,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedure } };
  R_Interpreter_Constructor* self = R_allocateObject(process, _R_Interpreter_Constructor_getType(process), 1, &argumentValues[0]);
  return self;
}

R_Interpreter_Constructor*
R_Interpreter_Constructor_create
  (
    Arcadia_Process* process,
    R_Interpreter_Code* code
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = code } };
  R_Interpreter_Constructor* self = R_allocateObject(process, _R_Interpreter_Constructor_getType(process), 1, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Interpreter_Constructor_getCode
  (
    R_Interpreter_Constructor* self
  )
{ return self->code; }
