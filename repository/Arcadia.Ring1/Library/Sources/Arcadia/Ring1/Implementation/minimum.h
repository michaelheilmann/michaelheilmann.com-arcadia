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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_MINIMUM_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_MINIMUM_H_INCLUDED

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

#define Define(Type, Suffix) \
  static inline Type##Value \
  R_minimum##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      Type##Value x, \
      Type##Value y \
    ) \
  { return x < y ? x : y; } 

Define(Arcadia_Integer16, Integer16)
Define(Arcadia_Integer32, Integer32)
Define(Arcadia_Integer64, Integer64)
Define(Arcadia_Integer8, Integer8)

Define(Arcadia_Natural16, Natural16)
Define(Arcadia_Natural32, Natural32)
Define(Arcadia_Natural64, Natural64)
Define(Arcadia_Natural8, Natural8)

Define(Arcadia_Size, Size)

#undef Define

#endif // ARCADIA_RING1_IMPLEMENTATION_MINIMUM_H_INCLUDED
