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

// Last modified: 2024-12-07

#include "R/Interpreter/Code/Constants.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/String.h"
#include "R/Interpreter/Include.h"
#include "R/cstdlib.h"

static void
constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
destructImpl
  (
    R_Interpreter_Code_Constants* self
  );

static void
visitImpl
  (
    R_Interpreter_Code_Constants* self
  );

static R_Natural32Value
getOrCreate
  (
    R_Interpreter_Code_Constants* self,
    R_Value const* constant
  );

static const R_ObjectType_Operations objectTypeOperations = {
  .construct = &constructImpl,
  .destruct = &destructImpl,
  .visit = &visitImpl,
};

static const R_Type_Operations typeOperations = {
  .objectTypeOperations = &objectTypeOperations,
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

Rex_defineObjectType("R.Interpreter.Code.Constants", R_Interpreter_Code_Constants, "R.Object", R_Object, &typeOperations);

static void
constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_Code_Constants* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Interpreter_Code_Constants_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  if (!R_allocateUnmanaged_nojump(&_self->p, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
destructImpl
  (
    R_Interpreter_Code_Constants* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

static void
visitImpl
  (
    R_Interpreter_Code_Constants* self
  )
{
  for (R_SizeValue i = 0, n = self->cp; i < n; ++i) {
    R_Value_visit(self->p + i);
  }
}

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_Interpreter_Code_Constants* self = R_allocateObject(_R_Interpreter_Code_Constants_getType(), 0, &argumentValues[0]);
  return self;
}

static R_Natural32Value
getOrCreate
  (
    R_Interpreter_Code_Constants* self,
    R_Value const* constant
  )
{ 
  for (R_SizeValue i = 0, n = self->cp; i < n; ++i) {
    if (R_Value_isEqualTo(self->p + i, constant)) {
      return i;
    }
  }
  R_DynamicArrayUtilities_ensureFreeCapacity(&self->p, sizeof(R_Value), self->sz, &self->cp, 1, R_DynamicArrayUtilities_GrowthStrategy4);
  self->p[self->sz++] = *constant;
  return self->sz - 1;
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    R_Interpreter_Code_Constants* self,
    R_BooleanValue booleanValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Boolean, .booleanValue = booleanValue };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    R_Interpreter_Code_Constants* self,
    R_ForeignProcedureValue foreignProcedureValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedureValue };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    R_Interpreter_Code_Constants* self,
    R_Integer16Value integer16Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer16, .integer16Value = integer16Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    R_Interpreter_Code_Constants* self,
    R_Integer32Value integer32Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer32, .integer32Value = integer32Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    R_Interpreter_Code_Constants* self,
    R_Integer64Value integer64Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer32, .integer64Value = integer64Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    R_Interpreter_Code_Constants* self,
    R_Integer8Value integer8Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer8, .integer8Value = integer8Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    R_Interpreter_Code_Constants* self,
    R_Natural16Value natural16Value
  )
{ 
  R_Value const constant = { .tag = R_ValueTag_Natural16, .natural16Value = natural16Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    R_Interpreter_Code_Constants* self,
    R_Natural32Value natural32Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural32, .natural32Value = natural32Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    R_Interpreter_Code_Constants* self,
    R_Natural64Value natural64Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural64, .natural64Value = natural64Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    R_Interpreter_Code_Constants* self,
    R_Natural8Value natural8Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural8, .natural8Value = natural8Value };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    R_Interpreter_Code_Constants* self,
    R_SizeValue sizeValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Size, .sizeValue = sizeValue };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    R_Interpreter_Code_Constants* self,
    R_String* stringValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = stringValue };
  return getOrCreate(self, &constant);
}

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    R_Interpreter_Code_Constants* self,
    R_VoidValue voidValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Void, .voidValue = voidValue };
  return getOrCreate(self, &constant);
}

R_Value const*
R_Interpreter_Code_Constants_getAt
  (
    R_Interpreter_Code_Constants const* self,
    R_Natural32Value index
  )
{
  if (index >= self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return self->p + index;
}
