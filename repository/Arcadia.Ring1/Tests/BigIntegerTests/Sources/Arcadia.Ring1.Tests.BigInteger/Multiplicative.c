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

// Last modified: 2024-09-28

#include "Arcadia.Ring1.Tests.BigInteger/Multiplicative.h"

static inline Arcadia_Value
Arcadia_Value_fromBigIntegerValue
  (
    Arcadia_BigIntegerValue v
  )
{
  Arcadia_Value w = Arcadia_Value_Initializer();
  Arcadia_Value_setBigIntegerValue(&w, v);
  return w;
}

#define Test_Op_multiply (1)

static inline void
Arcadia_Test_BigInteger_assertMultiplicative
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value expectedResult,
    Arcadia_Natural8Value operation,
    Arcadia_Integer64Value leftOperand,
    Arcadia_Integer64Value rightOperand
  )
{
  Arcadia_BigInteger* leftOperandBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, leftOperandBigInteger, leftOperand);
  Arcadia_Value leftOperandValue = Arcadia_Value_fromBigIntegerValue(leftOperandBigInteger);
  
  Arcadia_BigInteger* rightOperandBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, rightOperandBigInteger, rightOperand);
  Arcadia_Value rightOperandValue = Arcadia_Value_fromBigIntegerValue(rightOperandBigInteger);
  
  Arcadia_BigInteger* expectedResultBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, expectedResultBigInteger, expectedResult);
  Arcadia_Value expectedResultValue = Arcadia_Value_fromBigIntegerValue(expectedResultBigInteger);

  switch (operation) {
    case Test_Op_multiply: {
      Arcadia_BigInteger* receivedResultBigInteger = Arcadia_BigInteger_create(thread);
      Arcadia_BigInteger_multiply3(thread, receivedResultBigInteger, leftOperandBigInteger, rightOperandBigInteger);
      Arcadia_Tests_assertTrue(thread, Arcadia_Integer8Value_Literal(0) == Arcadia_BigInteger_compareTo(thread, receivedResultBigInteger, expectedResultBigInteger));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
};

void
Arcadia_Ring1_Tests_BigInteger_multiplicativeOperations
  (
    Arcadia_Thread* thread
  )
{
  typedef struct Test {
    Arcadia_Integer32Value result;
    int operation;
    Arcadia_Integer32Value a;
    Arcadia_Integer32Value b;
  } Test;
  static const Test tests[] = {
    { .result = 0, Test_Op_multiply, 0, 0 }, // 0
    { .result = 0, Test_Op_multiply, 0, 1 },
    { .result = 1, Test_Op_multiply, 1, 1 },
    { .result = -1, Test_Op_multiply, -1, 1 },

    {.result = 7, Test_Op_multiply, 1, 7 },

    {.result = 28, Test_Op_multiply, 4, 7 },
    {.result = -28, Test_Op_multiply, 4, -7 },
    {.result = -28, Test_Op_multiply, -4, 7 },

    {.result = 28, Test_Op_multiply, -4, -7 },
  };
  static const Arcadia_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  for (Arcadia_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    const Test* test = &(tests[i]);
    Arcadia_Test_BigInteger_assertMultiplicative(thread, test->result, test->operation, test->a, test->b);
  }
}
