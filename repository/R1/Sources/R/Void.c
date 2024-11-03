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

#include "R/Void.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

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
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_Type_Operations typeOperations = {
  .add = NULL,
  .and = NULL,
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
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = NULL,
};

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isVoidValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getVoidValue(self) == R_Value_getVoidValue(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  }
}

static void
hash
  (
    R_Value* target,
    R_Value const* self
  )
{ R_Value_setSizeValue(target, (R_SizeValue)71); }

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isVoidValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getVoidValue(self) != R_Value_getVoidValue(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
  }
}

static R_Type* g_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{ g_type = NULL; }

R_Type*
_R_VoidValue_getType
  (
  )
{
  if (!g_type) {
    R_registerVoidType(u8"R.Void", sizeof("R.Void") - 1, &typeOperations, &typeDestructing);
    g_type = R_getType(u8"R.Void", sizeof("R.Void") - 1);
  }
  return g_type;
}
