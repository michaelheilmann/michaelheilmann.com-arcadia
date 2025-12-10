// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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
#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

// (integer|natural)(8|16) can be represented exactly by real32
// (integer|natural)(32) can be represented exactly by real64

static void
add
  (
    Arcadia_Thread* thread
  );

static void
divide
  (
    Arcadia_Thread* thread
  );

static void
isEqualTo
  (
    Arcadia_Thread* thread
  );

static void
isGreaterThan
  (
    Arcadia_Thread* thread
  );

static void
isGreaterThanOrEqualTo
  (
    Arcadia_Thread* thread
  );

static void
hash
  (
    Arcadia_Thread* thread
  );

static void
identical
  (
    Arcadia_Thread* thread
  );

static void
isLowerThan
  (
    Arcadia_Thread* thread
  );

static void
isLowerThanOrEqualTo
  (
    Arcadia_Thread* thread
  );

static void
multiply
  (
    Arcadia_Thread* thread
  );

static void
negate
  (
    Arcadia_Thread* thread
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  );

static void
subtract
  (
    Arcadia_Thread* thread
  );

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .add = &add,
  .divide = &divide,
  .equalTo = &isEqualTo,
  .greaterThan = &isGreaterThan,
  .greaterThanOrEqualTo = &isGreaterThanOrEqualTo,
  .hash = &hash,
  .identical = &identical,
  .lowerThan = &isLowerThan,
  .lowerThanOrEqualTo = &isLowerThanOrEqualTo,
  .multiply = &multiply,
  .negate = &negate,
  .notEqualTo = &isNotEqualTo,
  .subtract = &subtract,
};

#define BINARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 3) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 2); \
  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 3);

#define UNARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 2) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 2);

static void
add
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) + (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
divide
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) / (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
isEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
isGreaterThan
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) > (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
isGreaterThanOrEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) >= (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
hash
  (
    Arcadia_Thread* thread
  )
{
  UNARY_OPERATION();
  Arcadia_Real64Value y = Arcadia_Value_getReal64Value(&x);
  if (y == 0.) {
    y = +0.;
  }
  typedef struct Union {
    Arcadia_Real64Value real64Value;
    Arcadia_Natural64Value natural64Value;
  } Union;
  Union z = { .real64Value = y };
  Arcadia_ValueStack_pushSizeValue(thread, (Arcadia_SizeValue)z.natural64Value);
}

static void
identical
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) == Arcadia_Value_getReal64Value(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
isLowerThan
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) < (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
isLowerThanOrEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) <= (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
multiply
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
negate
  (
    Arcadia_Thread* thread
  )
{
  UNARY_OPERATION();
  Arcadia_ValueStack_pushReal64Value(thread, -Arcadia_Value_getReal64Value(&x));
}

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getReal64Value(&x) != (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  }
}

static void
subtract
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isReal32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getReal32Value(&y));
  } else if (Arcadia_Value_isReal64Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * Arcadia_Value_getReal64Value(&y));
  } else if (Arcadia_Value_isInteger8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger8Value(&y));
  } else if (Arcadia_Value_isInteger16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger16Value(&y));
  } else if (Arcadia_Value_isInteger32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getInteger32Value(&y));
  } else if (Arcadia_Value_isNatural8Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural8Value(&y));
  } else if (Arcadia_Value_isNatural16Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural16Value(&y));
  } else if (Arcadia_Value_isNatural32Value(&y)) {
    Arcadia_ValueStack_pushReal64Value(thread, Arcadia_Value_getReal64Value(&x) * (Arcadia_Real64Value)Arcadia_Value_getNatural32Value(&y));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

Arcadia_defineScalarType(Arcadia_Real64, u8"Arcadia.Real64", &_typeOperations);
