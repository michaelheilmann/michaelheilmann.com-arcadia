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

// Last modified: 2024-10-27

#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

// (integer|natural)(8|16) can be represented exactly by real32
// (integer|natural)(32) can be represented exactly by real64

static void
add
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
divide
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
lowerThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
multiply
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
negate
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
subtract
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
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
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) + (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
divide
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) / (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) == (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
}

static void
greaterThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) > (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) >= (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{
  Arcadia_Real64Value x = R_Value_getReal64Value(self);
  if (x == 0.) {
    x = +0.;
  }
  typedef struct Union {
    Arcadia_Real64Value real64Value;
    Arcadia_Natural64Value natural64Value;
  } Union;
  Union v = { .real64Value = x };
  R_Value_setSizeValue(target, (Arcadia_SizeValue)v.natural64Value);
}

static void
lowerThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) < (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) <= (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
multiply
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
negate
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setReal64Value(target, -R_Value_getReal64Value(self));
}

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getReal64Value(self) != (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
}

static void
subtract
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isReal32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getReal32Value(other));
  } else if (R_Value_isReal64Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * R_Value_getReal64Value(other));
  } else if (R_Value_isInteger8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getInteger32Value(other));
  } else if (R_Value_isNatural8Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    R_Value_setReal64Value(target, R_Value_getReal64Value(self) * (Arcadia_Real64Value)R_Value_getNatural32Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

Rex_defineScalarType(Arcadia_Real64, u8"Arcadia.Real64", &_typeOperations);
