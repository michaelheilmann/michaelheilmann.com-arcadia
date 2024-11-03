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

#include "R/Real64.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

// (integer|natural)(8|16) can be represented exactly by real32
// (integer|natural)(32) can be represented exactly by real64

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
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (R_Real64Value)R_Value_getNatural32Value(other));
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
  R_Real64Value x = R_Value_getReal64Value(self);
  if (x == 0.) {
    x = +0.;
  }
  typedef struct Union {
    R_Real64Value real64Value;
    R_Natural64Value natural64Value;
  } Union;
  Union v = { .real64Value = x };
  R_Value_setSizeValue(target, (R_SizeValue)v.natural64Value);
}

static void
lowerThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural32Value(other));
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
  R_Value_setReal64Value(target, -R_Value_getReal64Value(self));
}

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (R_Real64Value)R_Value_getNatural32Value(other));
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
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (R_Real64Value)R_Value_getNatural32Value(other));
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
_R_Real64Value_getType
  (
  )
{
  if (!g_type) {
    R_registerRealType(u8"R.Real64", sizeof("R.Real64") - 1, &typeOperations, &typeDestructing);
    g_type = R_getType(u8"R.Real64", sizeof("R.Real64") - 1);
  }
  return g_type;
}
