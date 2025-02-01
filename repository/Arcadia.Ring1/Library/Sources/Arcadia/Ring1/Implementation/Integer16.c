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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Integer16.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

static void
add
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
divide
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
equalTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
greaterThan
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
lowerThan
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
multiply
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
negate
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
notEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
subtract
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
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
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) + (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) + Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger32Value(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) + Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) + Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
divide
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    if (!Arcadia_Value_getInteger8Value(A2)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) / (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    if (!Arcadia_Value_getInteger16Value(A2)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) / Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    if (!Arcadia_Value_getInteger32Value(A2)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value_setInteger32Value(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) / Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    if (!Arcadia_Value_getInteger64Value(A2)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    Arcadia_Value_setInteger64Value(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) / Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
equalTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) == (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) == Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) == Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) == Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
greaterThan
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) > (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) > Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) > Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) > Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) >= (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) >= Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) >= Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) >= Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)Arcadia_Value_getInteger16Value(A1));
#undef A1
}

static void
lowerThan
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) < (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) < Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) < Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) < Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) <= (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) <= Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) <= Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) <= Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
multiply
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) * (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger32Value(target, Arcadia_Value_getInteger16Value(A1) * Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger32Value(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) * Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) * Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

static void
negate
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setInteger16Value(target, -Arcadia_Value_getInteger16Value(A1));
#undef A1
}

static void
notEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) != (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger16Value(A1) != Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) != Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) != Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
#undef A2
#undef A1
}

static void
subtract
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) - (Arcadia_Integer16Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger16Value(target, Arcadia_Value_getInteger16Value(A1) - Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger32Value(target, (Arcadia_Integer32Value)Arcadia_Value_getInteger16Value(A1) - Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A1) - Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
#undef A2
#undef A1
}

Rex_defineScalarType(Arcadia_Integer16, u8"Arcadia.Integer16", &_typeOperations);
