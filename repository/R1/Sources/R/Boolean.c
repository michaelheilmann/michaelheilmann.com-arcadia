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

// Last modified: 2024-10-27

#include "R/Boolean.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

static void
and
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hash
  (
    R_Value* target,
    R_Value const* self
  );

static void
not
  (
    R_Value* target,
    R_Value const* self
  );

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
or
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
  .add = NULL,
  .and = &and,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = &not,
  .notEqualTo = &notEqualTo,
  .or = &or ,
  .subtract = NULL,
};

static void
and
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Value_isBooleanValue(other)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Value_setBooleanValue(target, R_Value_getBooleanValue(self) && R_Value_getBooleanValue(other));
}

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{ 
  if (!R_Value_isBooleanValue(other)) {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  } else {
    R_Value_setBooleanValue(target, R_Value_getBooleanValue(self) == R_Value_getBooleanValue(other));
  }
}

static void
hash
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, R_Value_getBooleanValue(self) ? 1231 : 1237);
}

static void
not
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setBooleanValue(target, !R_Value_getBooleanValue(self));
}

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Value_isBooleanValue(other)) {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
  } else {
    R_Value_setBooleanValue(target, R_Value_getBooleanValue(self) != R_Value_getBooleanValue(other));
  }
}

static void
or
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Value_isBooleanValue(other)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Value_setBooleanValue(target, R_Value_getBooleanValue(self) || R_Value_getBooleanValue(other));
}

static R_Type* g_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{ g_type = NULL; }

R_Type*
_R_BooleanValue_getType
  (
  )
{
  if (!g_type) {
    R_registerBooleanType(u8"R.Boolean", sizeof("R.Boolean") - 1, &_typeOperations, &typeDestructing);
    g_type = R_getType(u8"R.Boolean", sizeof("R.Boolean") - 1);
  }
  return g_type;
}
