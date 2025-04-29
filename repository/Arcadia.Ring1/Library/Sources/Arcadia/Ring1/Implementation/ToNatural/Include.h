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

// Last modified: 2025-03-07

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TONATURAL_INCLUDE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TONATURAL_INCLUDE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

Arcadia_Natural16Value
Arcadia_toNatural16
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  );

Arcadia_Natural32Value
Arcadia_toNatural32
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  );

Arcadia_Natural64Value
Arcadia_toNatural64
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  );

Arcadia_Natural8Value
Arcadia_toNatural8
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TONATURAL_INCLUDE_H_INCLUDED
