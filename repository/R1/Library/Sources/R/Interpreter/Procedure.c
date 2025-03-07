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

#include "R/Interpreter/Procedure.h"

#include "R/Include.h"
#include "R/ArgumentsValidation.h"

static void
R_Interpreter_Procedure_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Interpreter_Procedure_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Procedure_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Procedure_visit,
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

Rex_defineObjectType(u8"R.Interpreter.Procedure", R_Interpreter_Procedure, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Interpreter_Procedure_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_Procedure* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Procedure_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->parameterNames = Arcadia_List_create(thread);
  _self->unqualifiedName = R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
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
  Arcadia_Object_setType(Arcadia_Process_getThread(process), _self, _type);
}

static void
R_Interpreter_Procedure_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  )
{
  if (!self->isForeign) {
    Arcadia_Object_visit(thread, self->code);
  }
  Arcadia_Object_visit(thread, self->unqualifiedName);
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_createForeign
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name },
    {.tag = Arcadia_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedure },
  };
  R_Interpreter_Procedure* self = Arcadia_allocateObject(thread, _R_Interpreter_Procedure_getType(thread), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    R_Interpreter_Code* code
  )
{
  Arcadia_Value argumentValues[] = { 
    { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name },
    { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = code },
  };
  R_Interpreter_Procedure* self = Arcadia_allocateObject(thread, _R_Interpreter_Procedure_getType(thread), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Interpreter_Procedure_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  )
{ return self->code; }
