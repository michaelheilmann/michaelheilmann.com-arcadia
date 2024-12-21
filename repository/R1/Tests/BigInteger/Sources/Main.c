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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "R.h"
#include "R/BigInteger/Include.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

static inline R_Value R_Value_fromObjectReferenceValue(R_ObjectReferenceValue v) {
  R_Value w = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = v };
  return w;
}

#define R_Test_Op_equalTo (1)
#define R_Test_Op_greaterThan (5)
#define R_Test_Op_greaterThanOrEqualTo (6)
#define R_Test_Op_lowerThan (3)
#define R_Test_Op_lowerThanOrEqualTo (4)
#define R_Test_Op_notEqualTo (2)
#define R_Test_Op_add (7)
#define R_Test_Op_subtract (8)

static inline void
R_Test_BigInteger_assertRelational
  (
    R_BooleanValue expectedResult,
    R_Natural8Value op,
    R_Integer64Value a,
    R_Integer64Value b
  )
{
  R_BigInteger *pa = NULL, *pb = NULL;
  R_Value vb;
  pa = R_BigInteger_fromInteger64(a);
  pb = R_BigInteger_fromInteger64(b);
  vb = R_Value_fromObjectReferenceValue(pb);
  switch (op) {
    case R_Test_Op_equalTo: {
      R_Test_assert(expectedResult == R_Object_equalTo((R_Object*)pa, &vb));
      R_Test_assert(expectedResult == !R_Object_notEqualTo((R_Object*)pa, &vb));
    } break;
    case R_Test_Op_greaterThan: {
      R_BooleanValue receivedResult = R_Object_greaterThan((R_Object*)pa, &vb);
      R_Test_assert(expectedResult == receivedResult);
      if (expectedResult) {
        // "greaterThan(x,y)" true implies "lowerThanOrEqualTo(x,y)" and "lowerThan(x,y)" false.
        R_Test_assert(!R_Object_lowerThanOrEqualTo((R_Object*)pa, &vb));
        R_Test_assert(!R_Object_lowerThan((R_Object*)pa, &vb));
      } else {
        // "greaterThan(x,y)" false implies "lowerThanOrEqualTo(x,y)" true.
        R_Test_assert(R_Object_lowerThanOrEqualTo((R_Object*)pa, &vb));
      }
    } break;
    case R_Test_Op_greaterThanOrEqualTo: {
      R_Test_assert(expectedResult == R_Object_greaterThanOrEqualTo((R_Object*)pa, &vb));
      if (expectedResult) {
        // "greaterThanOrEqualTo(x,y)" true implies "lowerThan(x,y)" false.
        R_Test_assert(!R_Object_lowerThan((R_Object*)pa, &vb));
      }
    } break;
    case R_Test_Op_lowerThan: {
      R_BooleanValue receivedResult = R_Object_lowerThan((R_Object*)pa, &vb);
      R_Test_assert(expectedResult == receivedResult);
      if (expectedResult) {
        // "lowerThan(x,y)" true implies "greaterThanOrEqualTo(x,y)" and "greaterThan(x,y)" false.
        R_Test_assert(!R_Object_greaterThanOrEqualTo((R_Object*)pa, &vb));
        R_Test_assert(!R_Object_greaterThan((R_Object*)pa, &vb));
      } else {
        // "lowerThan(x,y)" false implies "greaterThanOrEqualTo(x,y)" true.
        R_Test_assert(R_Object_greaterThanOrEqualTo((R_Object*)pa, &vb));
      }
    } break;
    case R_Test_Op_lowerThanOrEqualTo: {
      R_Test_assert(expectedResult == R_Object_lowerThanOrEqualTo((R_Object*)pa, &vb));
      if (expectedResult) {
        // "lowerThanOrEqualTo(x,y)" true implies "greaterThan(x,y)" false.
        R_Test_assert(!R_Object_greaterThan((R_Object*)pa, &vb));
      }
    } break;
    case R_Test_Op_notEqualTo: {
      R_Test_assert(expectedResult == R_Object_lowerThanOrEqualTo((R_Object*)pa, &vb));
      R_Test_assert(expectedResult == !R_Object_lowerThanOrEqualTo((R_Object*)pa, &vb));
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
};

static inline void
R_Test_BigInteger_assertAdditive
  (
    R_Integer64Value expectedResult,
    R_Natural8Value op,
    R_Integer64Value a,
    R_Integer64Value b
  )
{
  R_BigInteger* pa = NULL, * pb = NULL;
  R_Value vb;
  pa = R_BigInteger_fromInteger64(a);
  pb = R_BigInteger_fromInteger64(b);
  R_BigInteger* pexpectedResult = R_BigInteger_fromInteger64(expectedResult);
  vb = R_Value_fromObjectReferenceValue(pb);
  switch (op) {
    case R_Test_Op_add: {
      R_BigInteger* preceivedResult = R_BigInteger_add(pa, pb);
      R_Test_assert(0 == R_BigInteger_compare(preceivedResult, pexpectedResult));
    } break;
    case R_Test_Op_subtract: {
      R_BigInteger* preceivedResult = R_BigInteger_subtract(pa, pb);
      R_Test_assert(0 == R_BigInteger_compare(preceivedResult, pexpectedResult));
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
};

static void
relationalOperations
  (
  )
{
  typedef struct Test {
    R_BooleanValue result;
    int operation;
    R_Integer32Value a, b;
  } Test;
  Test tests[] = {
    /* two positive numbers */
    { R_BooleanValue_True, R_Test_Op_equalTo, 2, 2 }, // 0

    { R_BooleanValue_True, R_Test_Op_greaterThan, 2, 1 },
    { R_BooleanValue_False, R_Test_Op_greaterThan, 2, 2 },

    { R_BooleanValue_True, R_Test_Op_greaterThanOrEqualTo, 2, 1 },
    { R_BooleanValue_True, R_Test_Op_greaterThanOrEqualTo, 2, 2 },
  
    { R_BooleanValue_True, R_Test_Op_lowerThan, 1, 2 },
    { R_BooleanValue_False, R_Test_Op_lowerThan, 2, 2 },

    { R_BooleanValue_True, R_Test_Op_lowerThanOrEqualTo, 1, 2 },
    { R_BooleanValue_True, R_Test_Op_lowerThanOrEqualTo, 2, 2 },

    /* two negative numbers */
    { R_BooleanValue_True, R_Test_Op_equalTo, -2, -2 }, // 9

    { R_BooleanValue_True, R_Test_Op_greaterThan, -1, -2 },
    { R_BooleanValue_False, R_Test_Op_greaterThan, -2, -2 },

    { R_BooleanValue_True, R_Test_Op_greaterThanOrEqualTo, -1, -2 },
    { R_BooleanValue_True, R_Test_Op_greaterThanOrEqualTo, -2, -2 },

    { R_BooleanValue_True, R_Test_Op_lowerThan, -2, -1 },
    { R_BooleanValue_False, R_Test_Op_lowerThan, -2, -2 },

    { R_BooleanValue_True, R_Test_Op_lowerThanOrEqualTo, -2, -1 },
    { R_BooleanValue_True, R_Test_Op_lowerThanOrEqualTo, -2, -2 },
  };
  R_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  for (R_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    Test* test = &(tests[i]);
    R_Test_BigInteger_assertRelational(test->result, test->operation, test->a, test->b);
  }
}

static void
additiveOperations
  (
  )
{
  typedef struct Test {
    R_Integer32Value result;
    int operation;
    R_Integer32Value a, b;
  } Test;
  Test tests[] = {
    { 0, R_Test_Op_add, 0, 0 },
    { 0, R_Test_Op_subtract, 0, 0 },

    { 12, R_Test_Op_add, 5, 7 }, // also tests 7 + 5
    { -2, R_Test_Op_subtract, 5, 7 },

    { 12, R_Test_Op_add, 5, 7 }, // also tests 7 + 5
    { -2, R_Test_Op_subtract, 5, 7 },
  };
  R_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  R_Test_BigInteger_assertAdditive(-2, R_Test_Op_subtract, 5, 7);
  for (R_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    Test* test = &(tests[i]);
    R_Test_BigInteger_assertAdditive(test->result, test->operation, test->a, test->b);
  }
}

static bool
safeExecute
  (
    void (*f)()
  )
{
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)();
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
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
