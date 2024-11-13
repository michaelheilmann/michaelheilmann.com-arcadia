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
// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static void
R_Procedure_visit
  (
    R_Procedure* self
  );

static void
R_Procedure_visit
  (
    R_Procedure* self
  )
{
  R_Object_visit(self->code);
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
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

void
R_Procedure_construct
  (
    R_Procedure* self,
    R_Machine_Code* code
  )
{
  R_Type* _type = _R_Procedure_getType();
  R_Object_construct((R_Object*)self);
  self->code = code;
  R_Object_setType((R_Object*)self, _type);
}

R_Procedure*
R_Procedure_create
  (
    R_Machine_Code* code
  )
{
  R_Procedure* self = R_allocateObject(_R_Procedure_getType());
  R_Procedure_construct(self, code);
  return self;
}

R_Machine_Code*
R_Procedure_getCode
  (
    R_Procedure* self
  )
{ return self->code; }
