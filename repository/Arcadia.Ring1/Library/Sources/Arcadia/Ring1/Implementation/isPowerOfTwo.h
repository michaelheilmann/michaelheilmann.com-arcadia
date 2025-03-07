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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ISPOWEROFTWO_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ISPOWEROFTWO_H_INCLUDED

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

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Size.h"

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value x
  );

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isPowerOfTwo
Arcadia_BooleanValue
Arcadia_isPowerOfTwoSizeValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue x
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_ISPOWEROFTWO_H_INCLUDED
