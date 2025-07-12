// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Integer64.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

static void
add
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
divide
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
equalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
greaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
greaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
lowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
identical
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
lowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
multiply
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
negate
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
notEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .add = &add,
  .divide = &divide,
  .equalTo = &equalTo,
  .greaterThan = &greaterThan,
  .greaterThanOrEqualTo = &greaterThanOrEqualTo,
  .hash = &hash,
  .identical = &identical,
  .lowerThan = &lowerThan,
  .lowerThanOrEqualTo = &lowerThanOrEqualTo,
  .multiply = &multiply,
  .negate = &negate,
  .notEqualTo = &notEqualTo,
  .subtract = &subtract,
};

static void
add
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) + (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) + (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) + (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) + Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
divide
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    if (Arcadia_Value_getInteger8Value(A2)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) / (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    if (Arcadia_Value_getInteger16Value(A2)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) / (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    if (Arcadia_Value_getInteger32Value(A2)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) / (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    if (Arcadia_Value_getInteger64Value(A2)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) / Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
equalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) == (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) == (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) == (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) == Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
greaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) > (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) > (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) > (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger32Value(A1) > Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
greaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) >= (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) >= (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) >= (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) >= Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)Arcadia_Value_getInteger64Value(A1));
#undef A1
}

static void
identical
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) == Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
lowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) < (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) < (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) < (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) < Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
lowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger32Value(A1) <= (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger32Value(A1) <= (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger32Value(A1) <= (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) <= Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
multiply
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) * (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) * (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) * (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger32Value(A1) * Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
negate
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setInteger64Value(target, -Arcadia_Value_getInteger64Value(A1));
#undef A1
}

static void
notEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) != (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) != (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) != (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getInteger64Value(A1) != Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
#undef A2
#undef A1
}

static void
subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isInteger8Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) - (Arcadia_Integer64Value)Arcadia_Value_getInteger8Value(A2));
  } else if (Arcadia_Value_isInteger16Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) - (Arcadia_Integer64Value)Arcadia_Value_getInteger16Value(A2));
  } else if (Arcadia_Value_isInteger32Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) - (Arcadia_Integer64Value)Arcadia_Value_getInteger32Value(A2));
  } else if (Arcadia_Value_isInteger64Value(A2)) {
    Arcadia_Value_setInteger64Value(target, Arcadia_Value_getInteger64Value(A1) - Arcadia_Value_getInteger64Value(A2));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

Arcadia_defineScalarType(Arcadia_Integer64, u8"Arcadia.Integer64", &_typeOperations);
