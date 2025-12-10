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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NUMERICS_QUOTIENTREMAINDER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NUMERICS_QUOTIENTREMAINDER_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Size.h"

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value dividend,
    Arcadia_Integer16Value divisor,
    Arcadia_Integer16Value* quotient,
    Arcadia_Integer16Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderIntegerl32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value dividend,
    Arcadia_Integer32Value divisor,
    Arcadia_Integer32Value* quotient,
    Arcadia_Integer32Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value dividend,
    Arcadia_Integer64Value divisor,
    Arcadia_Integer64Value* quotient,
    Arcadia_Integer64Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value dividend,
    Arcadia_Integer8Value divisor,
    Arcadia_Integer8Value* quotient,
    Arcadia_Integer8Value* remainder
  );



// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value dividend,
    Arcadia_Natural16Value divisor,
    Arcadia_Natural16Value* quotient,
    Arcadia_Natural16Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value dividend,
    Arcadia_Natural32Value divisor,
    Arcadia_Natural32Value* quotient,
    Arcadia_Natural32Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value dividend,
    Arcadia_Natural64Value divisor,
    Arcadia_Natural64Value* quotient,
    Arcadia_Natural64Value* remainder
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_quotientRemainder*
void
Arcadia_quotientRemainderNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value dividend,
    Arcadia_Natural8Value divisor,
    Arcadia_Natural8Value *quotient,
    Arcadia_Natural8Value* remainder
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_NUMERICS_QUOTIENTREMAINDER_H_INCLUDED
