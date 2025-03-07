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

// Last modified: 2025-01-26

#if !defined(ARCADIA_RING1_SAFEADD_H_INCLUDED)
#define ARCADIA_RING1_SAFEADD_H_INCLUDED

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

#include "Arcadia/Ring1/Implementation/Size.h"

void
Arcadia_safeAddNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value augend,
    Arcadia_Natural16Value addend,
    Arcadia_Natural16Value* sumHigh,
    Arcadia_Natural16Value* sumLow
  );

void
Arcadia_safeAddNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value augend,
    Arcadia_Natural32Value addend,
    Arcadia_Natural32Value* sumHigh,
    Arcadia_Natural32Value* sumLow
  );

void
Arcadia_safeAddNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value augend,
    Arcadia_Natural64Value addend,
    Arcadia_Natural64Value* sumHigh,
    Arcadia_Natural64Value* sumLow
  );

void
Arcadia_safeAddNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value augend,
    Arcadia_Natural8Value addend,
    Arcadia_Natural8Value* sumHigh,
    Arcadia_Natural8Value* sumLow
  );

#endif // ARCADIA_RING1_SAFEADD_H_INCLUDED
