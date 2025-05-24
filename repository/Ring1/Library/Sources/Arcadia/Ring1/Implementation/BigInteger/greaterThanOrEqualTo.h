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

#if !defined(ARCADIA_RING1_BIGINTEGER_GREATERTHANOREQUALTO_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_GREATERTHANOREQUALTO_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Get if this BigInteger is greater than or equal to another BigInteger.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

// Get if this BigInteger is greater than or equal to an Integer16.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  );

// Get if this BigInteger is greater than or equal to an Integer32.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  );

// Get if this BigInteger is greater than or equal to an Integer64.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  );

// Get if this BigInteger is greater than or equal to an Integer8.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  );

// Get if this BigInteger is greater than or equal to a Natural16.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Get if this BigInteger is greater than or equal to a Natural32.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Get if this BigInteger is greater than or equal to a Natural64.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Get if this BigInteger is greater than or equal to to a Natural8.
Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_GREATERTHANOREQUALTO_H_INCLUDED
