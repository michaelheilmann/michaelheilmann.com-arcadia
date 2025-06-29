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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NUMERICS_ISDIVISIBLEBYPOWEROFFIVE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NUMERICS_ISDIVISIBLEBYPOWEROFFIVE_H_INCLUDED

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

#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/Thread.h"

#include "Arcadia/Ring1/Implementation/Size.h"

// Returns true if <code>v</code> is divisible by <code>5^p</code>.
// In particular, this function returns logically false if <code>v = 0</code>.
Arcadia_BooleanValue
Arcadia_isDivisibleByPowerOfFiveNatural16
  (
    Arcadia_Thread* thread,
    const uint16_t v,
    const uint16_t p
  );

// Returns true if <code>v</code> is divisible by <code>5^p</code>.
// In particular, this function returns logically false if <code>v = 0</code>.
Arcadia_BooleanValue
Arcadia_isDivisibleByPowerOfFiveNatural32
  (
    Arcadia_Thread* thread,
    const uint32_t v,
    const uint32_t p
  );

// Returns true if <code>v</code> is divisible by <code>5^p</code>.
// In particular, this function returns logically false if <code>v = 0</code>.
Arcadia_BooleanValue
Arcadia_isDivisibleByPowerOfFiveNatural64
  (
    Arcadia_Thread* thread,
    const uint64_t v,
    const uint64_t p
  );

// Returns true if <code>v</code> is divisible by <code>5^p</code>.
// In particular, this function returns logically false if <code>v = 0</code>.
Arcadia_BooleanValue
Arcadia_isDivisibleByPowerOfFiveNatural8
  (
    Arcadia_Thread* thread,
    const uint8_t v,
    const uint8_t p
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_NUMERICS_ISDIVISIBLEBYPOWEROFFIVE_H_INCLUDED
