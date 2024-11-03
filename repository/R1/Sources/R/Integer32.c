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

// Last modified: 2024-10-31

#include "R/Integer32.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

static void
add
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
divide
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
greaterThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThanOrEqualTo
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
lowerThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
lowerThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
multiply
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
negate
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
subtract
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_Type_Operations typeOperations = {
  .add = &add,
  .and = NULL,
  .concatenate = NULL,
  .divide = &divide,
  .equalTo = &equalTo,
  .greaterThan = &greaterThan,
  .greaterThanOrEqualTo = &greaterThanOrEqualTo,
  .hash = &hash,
  .lowerThan = &lowerThan,
  .lowerThanOrEqualTo = &lowerThanOrEqualTo,
  .multiply = &multiply,
  .negate = &negate,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = &subtract,
};

static void
add
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (R_Integer64Value)R_Value_getInteger32Value(self) + R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
divide
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    if (R_Value_getInteger8Value(other)) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    if (R_Value_getInteger16Value(other)) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    if (R_Value_getInteger32Value(other)) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    if (R_Value_getInteger64Value(other)) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setInteger64Value(target, (R_Integer64Value)R_Value_getInteger32Value(self) / R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger32Value(self) == R_Value_getInteger64Value(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  }
}

static void
greaterThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger32Value(self) > R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
greaterThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger32Value(self) >= R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
hash
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, (R_SizeValue)R_Value_getInteger32Value(self));
}

static void
lowerThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger32Value(self) < R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
lowerThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger32Value(self) <= R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
multiply
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * (R_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * (R_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (R_Integer64Value)R_Value_getInteger32Value(self) * R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
negate
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setInteger32Value(target, -R_Value_getInteger32Value(self));
}

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger8Value(self) != R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer16Value)R_Value_getInteger8Value(self) != R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer32Value)R_Value_getInteger8Value(self) != R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (R_Integer64Value)R_Value_getInteger8Value(self) != R_Value_getInteger64Value(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
  }
}

static void
subtract
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) - R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, (R_Integer16Value)R_Value_getInteger32Value(self) - R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, (R_Integer32Value)R_Value_getInteger32Value(self) - R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (R_Integer64Value)R_Value_getInteger32Value(self) - R_Value_getInteger64Value(other));
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
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
_R_Integer32Value_getType
  (
  )
{
  if (!g_type) {
    R_registerIntegerType(u8"R.Integer32", sizeof("R.Integer32") - 1, &typeOperations, &typeDestructing);
    g_type = R_getType(u8"R.Integer32", sizeof("R.Integer32") - 1);
  }
  return g_type;
}
