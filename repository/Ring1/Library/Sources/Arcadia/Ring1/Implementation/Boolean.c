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
#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

static void
and
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isEqualTo
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
identical
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
not
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
or
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value * arguments
  );

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
  .add = NULL,
  .and = &and,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &isEqualTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .identical = &identical,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = &not,
  .notEqualTo = &isNotEqualTo,
  .or = &or ,
  .subtract = NULL,
};

static void
and
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isBooleanValue(A2)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Value_getBooleanValue(A1) && Arcadia_Value_getBooleanValue(A2));
#undef A2
#undef A1
}

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isBooleanValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getBooleanValue(A1) == Arcadia_Value_getBooleanValue(A2));
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
  Arcadia_Value_setSizeValue(target, Arcadia_Value_getBooleanValue(A1) ? 1231 : 1237);
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
  if (!Arcadia_Value_isBooleanValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getBooleanValue(A1) == Arcadia_Value_getBooleanValue(A2));
  }
#undef A2
#undef A1
}

static void
not
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setBooleanValue(target, !Arcadia_Value_getBooleanValue(A1));
#undef A1
}

static void
isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isBooleanValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getBooleanValue(A1) != Arcadia_Value_getBooleanValue(A2));
  }
#undef A2
#undef A1
}

static void
or
  (
    Arcadia_Thread * thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isBooleanValue(A2)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Value_getBooleanValue(A1) || Arcadia_Value_getBooleanValue(A2));
#undef A2
#undef A1
}

Arcadia_defineScalarType(Arcadia_Boolean, "Arcadia.Boolean", &_typeOperations);
