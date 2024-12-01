// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-11-21

#include "R/Procedure.h"

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/UnmanagedMemory.h"
#include "R/Interpreter/Code.h"
#include "R/cstdlib.h"

static void
R_Procedure_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Procedure_visit
  (
    R_Procedure* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Procedure_constructImpl,
  .destruct = NULL,
  .visit = &R_Procedure_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.Procedure", R_Procedure, "R.Object", R_Object, &_typeOperations);

static void
R_Procedure_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Procedure* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Procedure_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_Interpreter_Code_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->code = R_Value_getObjectReferenceValue(&argumentValues[0]);
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Procedure_visit
  (
    R_Procedure* self
  )
{
  R_Object_visit(self->code);
}

R_Procedure*
R_Procedure_create
  (
    R_Interpreter_Code* code
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = code } };
  R_Procedure* self = R_allocateObject(_R_Procedure_getType(), 1, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Procedure_getCode
  (
    R_Procedure* self
  )
{ return self->code; }
