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

// Last modified: 2024-10-31

#include "Arcadia/Ring1/Implementation/Integer32.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) + R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) + R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    if (R_Value_getInteger8Value(other)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    if (R_Value_getInteger16Value(other)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    if (R_Value_getInteger32Value(other)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) / R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    if (R_Value_getInteger64Value(other)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setInteger64Value(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) / R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) == R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) == R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) > R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) > R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) >= R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) >= R_Value_getInteger64Value(other));
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
  R_Value_setSizeValue(target, (Arcadia_SizeValue)R_Value_getInteger32Value(self));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) < R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) < R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger32Value(self) <= R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) <= R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * (Arcadia_Integer32Value)R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * (Arcadia_Integer32Value)R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) * R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) * R_Value_getInteger64Value(other));
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
  R_Value_setInteger32Value(target, -R_Value_getInteger32Value(self));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setBooleanValue(target, R_Value_getInteger8Value(self) != R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer16Value)R_Value_getInteger8Value(self) != R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer32Value)R_Value_getInteger8Value(self) != R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setBooleanValue(target, (Arcadia_Integer64Value)R_Value_getInteger8Value(self) != R_Value_getInteger64Value(other));
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
  if (R_Value_isInteger8Value(other)) {
    R_Value_setInteger32Value(target, R_Value_getInteger32Value(self) - R_Value_getInteger8Value(other));
  } else if (R_Value_isInteger16Value(other)) {
    R_Value_setInteger32Value(target, (Arcadia_Integer16Value)R_Value_getInteger32Value(self) - R_Value_getInteger16Value(other));
  } else if (R_Value_isInteger32Value(other)) {
    R_Value_setInteger32Value(target, (Arcadia_Integer32Value)R_Value_getInteger32Value(self) - R_Value_getInteger32Value(other));
  } else if (R_Value_isInteger64Value(other)) {
    R_Value_setInteger64Value(target, (Arcadia_Integer64Value)R_Value_getInteger32Value(self) - R_Value_getInteger64Value(other));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

Rex_defineScalarType(Arcadia_Integer32, u8"Arcadia.Integer32", &_typeOperations);
