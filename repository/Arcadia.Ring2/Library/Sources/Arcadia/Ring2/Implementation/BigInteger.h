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

// Last modified: 2025-01-20

#if !defined(ARCADIA_RING2_IMPLEMENTATION_BIGINTEGER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_BIGINTEGER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Implementation/Configure.h"
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Support/apint10.h"

// An Arcadia.Object wrapper around apint10.
Rex_declareObjectType("Arcadia.BigInteger", Arcadia_BigInteger, "Arcadia.Object");

struct Arcadia_BigInteger {
  Arcadia_Object _parent;
  apint10 _apint10;
};

Arcadia_BigInteger*
Arcadia_BigInteger_create
  (
    Arcadia_Process* process,
    Arcadia_Value v
  );

// compute
// @code
// a + b
// @endcode
Arcadia_BigInteger*
Arcadia_BigInteger_add
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

// compute
// @code
// a - b
// @endcode
Arcadia_BigInteger*
Arcadia_BigInteger_subtract
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

// compute
// @code
// |a|
// @endcode
Arcadia_BigInteger*
Arcadia_BigInteger_magnitude
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

// return -1 if |a| is less than |b|
// return +1 if |a| is greater than |b|
// return 0 otherwise
Arcadia_Integer8Value
Arcadia_BigInteger_compareMagnitudes
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

// return -1 if a is less than b
// return +1 if a is greater than b
// return 0 otherwise
Arcadia_Integer8Value
Arcadia_BigInteger_compare
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isZero
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isNegative
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  );

Arcadia_BooleanValue
Arcadia_BigInteger_isPositive
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  );

// assign the values of b to a
// @error #Arcadia_Status_ArgumentInvalid @a is null
// @error #Arcadia_Status_ArgumentInvalid @b is null
// @error #Arcadia_Status_AllocationFailed allocation failed
void
Arcadia_BigInteger_assign
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

void
Arcadia_BigInteger_addInPlace  
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

void
Arcadia_BigInteger_subtractInPlace
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger16
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger32
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger64
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger8
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural16
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural32
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural64
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value v
  );

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural8
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value v
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_RING2_IMPLEMENTATION_BIGINTEGER_H_INCLUDED
