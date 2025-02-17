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

#include <stdlib.h>

#include "R/Include.h"
#include "R/BigInteger/Include.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
    Arcadia_Process_jump(process); \
  }

static inline Arcadia_Value
Arcadia_Value_fromObjectReferenceValue
  (
    Arcadia_ObjectReferenceValue v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = v };
  return w;
}

#define R_Test_Op_isEqualTo (1)
#define R_Test_Op_isGreaterThan (5)
#define R_Test_Op_isGreaterThanOrEqualTo (6)
#define R_Test_Op_isLowerThan (3)
#define R_Test_Op_isLowerThanOrEqualTo (4)
#define R_Test_Op_isNotEqualTo (2)
#define R_Test_Op_add (7)
#define R_Test_Op_subtract (8)

static inline void
R_Test_BigInteger_assertRelational
  (
    Arcadia_Process* process,
    Arcadia_BooleanValue expectedResult,
    Arcadia_Natural8Value op,
    Arcadia_Integer64Value a,
    Arcadia_Integer64Value b
  )
{
  Arcadia_Value va = Arcadia_Value_fromObjectReferenceValue(R_BigInteger_fromInteger64(process, a));
  Arcadia_Value vb = Arcadia_Value_fromObjectReferenceValue(R_BigInteger_fromInteger64(process, b));
  switch (op) {
    case R_Test_Op_isEqualTo: {
      R_Test_assert(expectedResult == Arcadia_Value_isEqualTo(process, &va, &vb));
      R_Test_assert(expectedResult == !Arcadia_Value_isNotEqualTo(process, &va, &vb));
    } break;
    case R_Test_Op_isGreaterThan: {
      Arcadia_BooleanValue receivedResult = Arcadia_Value_isGreaterThan(process, &va, &vb);
      R_Test_assert(expectedResult == receivedResult);
      if (expectedResult) {
        // "isGreaterThan(x,y)" true implies "isLowerThanOrEqualTo(x,y)" and "isLowerThan(x,y)" false.
        R_Test_assert(!Arcadia_Value_isLowerThanOrEqualTo(process, &va, &vb));
        R_Test_assert(!Arcadia_Value_isLowerThan(process, &va, &vb));
      } else {
        // "isGreaterThan(x,y)" false implies "isLowerThanOrEqualTo(x,y)" true.
        R_Test_assert(Arcadia_Value_isLowerThanOrEqualTo(process, &va, &vb));
      }
    } break;
    case R_Test_Op_isGreaterThanOrEqualTo: {
      R_Test_assert(expectedResult == Arcadia_Value_isGreaterThanOrEqualTo(process, &va, &vb));
      if (expectedResult) {
        // "isGreaterThanOrEqualTo(x,y)" true implies "isLowerThan(x,y)" false.
        R_Test_assert(!Arcadia_Value_isLowerThan(process, &va, &vb));
      }
    } break;
    case R_Test_Op_isLowerThan: {
      Arcadia_BooleanValue receivedResult = Arcadia_Value_isLowerThan(process, &va, &vb);
      R_Test_assert(expectedResult == receivedResult);
      if (expectedResult) {
        // "isLowerThan(x,y)" true implies "isGreaterThanOrEqualTo(x,y)" and "isGreaterThan(x,y)" false.
        R_Test_assert(!Arcadia_Value_isGreaterThanOrEqualTo(process, &va, &vb));
        R_Test_assert(!Arcadia_Value_isGreaterThan(process, &va, &vb));
      } else {
        // "isLowerThan(x,y)" false implies "isGreaterThanOrEqualTo(x,y)" true.
        R_Test_assert(Arcadia_Value_isGreaterThanOrEqualTo(process, &va, &vb));
      }
    } break;
    case R_Test_Op_isLowerThanOrEqualTo: {
      R_Test_assert(expectedResult == Arcadia_Value_isLowerThanOrEqualTo(process, &va, &vb));
      if (expectedResult) {
        // "isLowerThanOrEqualTo(x,y)" true implies "isGreaterThan(x,y)" false.
        R_Test_assert(!Arcadia_Value_isGreaterThan(process, &va, &vb));
      }
    } break;
    case R_Test_Op_isNotEqualTo: {
      R_Test_assert(expectedResult == Arcadia_Value_isLowerThanOrEqualTo(process, &va, &vb));
      R_Test_assert(expectedResult == !Arcadia_Value_isLowerThanOrEqualTo(process, &va, &vb));
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  }
};

static inline void
R_Test_BigInteger_assertAdditive
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value expectedResult,
    Arcadia_Natural8Value op,
    Arcadia_Integer64Value a,
    Arcadia_Integer64Value b
  )
{
  R_BigInteger* pa = NULL, * pb = NULL;
  Arcadia_Value vb;
  pa = R_BigInteger_fromInteger64(process, a);
  pb = R_BigInteger_fromInteger64(process,b);
  R_BigInteger* pexpectedResult = R_BigInteger_fromInteger64(process, expectedResult);
  vb = Arcadia_Value_fromObjectReferenceValue(pb);
  switch (op) {
    case R_Test_Op_add: {
      R_BigInteger* preceivedResult = R_BigInteger_add(process, pa, pb);
      R_Test_assert(0 == R_BigInteger_compare(preceivedResult, pexpectedResult));
    } break;
    case R_Test_Op_subtract: {
      R_BigInteger* preceivedResult = R_BigInteger_subtract(process, pa, pb);
      R_Test_assert(0 == R_BigInteger_compare(preceivedResult, pexpectedResult));
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  }
};

static void
relationalOperations
  (
    Arcadia_Process* process
  )
{
  typedef struct Test {
    Arcadia_BooleanValue result;
    int operation;
    Arcadia_Integer32Value a, b;
  } Test;
  Test tests[] = {
    /* two positive numbers */
    { Arcadia_BooleanValue_True, R_Test_Op_isEqualTo, 2, 2 }, // 0

    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThan, 2, 1 },
    { Arcadia_BooleanValue_False, R_Test_Op_isGreaterThan, 2, 2 },

    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThanOrEqualTo, 2, 1 },
    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThanOrEqualTo, 2, 2 },
  
    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThan, 1, 2 },
    { Arcadia_BooleanValue_False, R_Test_Op_isLowerThan, 2, 2 },

    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThanOrEqualTo, 1, 2 },
    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThanOrEqualTo, 2, 2 },

    /* two negative numbers */
    { Arcadia_BooleanValue_True, R_Test_Op_isEqualTo, -2, -2 }, // 9

    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThan, -1, -2 },
    { Arcadia_BooleanValue_False, R_Test_Op_isGreaterThan, -2, -2 },

    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThanOrEqualTo, -1, -2 },
    { Arcadia_BooleanValue_True, R_Test_Op_isGreaterThanOrEqualTo, -2, -2 },

    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThan, -2, -1 },
    { Arcadia_BooleanValue_False, R_Test_Op_isLowerThan, -2, -2 },

    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThanOrEqualTo, -2, -1 },
    { Arcadia_BooleanValue_True, R_Test_Op_isLowerThanOrEqualTo, -2, -2 },
  };
  Arcadia_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  for (Arcadia_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    Test* test = &(tests[i]);
    R_Test_BigInteger_assertRelational(process, test->result, test->operation, test->a, test->b);
  }
}

static void
additiveOperations
  (
    Arcadia_Process* process
  )
{
  typedef struct Test {
    Arcadia_Integer32Value result;
    int operation;
    Arcadia_Integer32Value a, b;
  } Test;
  Test tests[] = {
    { 0, R_Test_Op_add, 0, 0 },
    { 0, R_Test_Op_subtract, 0, 0 },

    { 12, R_Test_Op_add, 5, 7 }, // also tests 7 + 5
    { -2, R_Test_Op_subtract, 5, 7 },

    { 12, R_Test_Op_add, 5, 7 }, // also tests 7 + 5
    { -2, R_Test_Op_subtract, 5, 7 },
  };
  Arcadia_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  R_Test_BigInteger_assertAdditive(process, -2, R_Test_Op_subtract, 5, 7);
  for (Arcadia_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    Test* test = &(tests[i]);
    R_Test_BigInteger_assertAdditive(process, test->result, test->operation, test->a, test->b);
  }
}

static bool
safeExecute
  (
    void (*f)(Arcadia_Process* process)
  )
{
  bool result = true;
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    result = false;
    return result;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    (*f)(process);
  } else {
    result = false;
  }
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    result = false;
  }
  return result;
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!safeExecute(&relationalOperations)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&additiveOperations)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
