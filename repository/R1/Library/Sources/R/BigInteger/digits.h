#if !defined(R_BIGINTEGER_DIGITS_H_INCLUDED)
#define R_BIGINTEGER_DIGITS_H_INCLUDED

#include "R/BigInteger/Include.h"

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Create (1)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Add (2)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Subtract (3)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Negate (4)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Magnitude (5)

void
Digits_allocate
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue capacity
  );

void
Digits_deallocate
  (
    R_BigInteger_Digit* array
  );

void
Digits_reallocate
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue capacity
  );

void
Digits_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** array,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredFreeCapacity
  );

#endif // R_BIGINTEGER_DIGITS_H_INCLUDED
