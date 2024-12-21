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

#include "R/nextPowerOfTwoGte.h"

#include "R/nextPowerOfTwoGt.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/isPowerOfTwo.h"

#define Define(Type, Bits) \
  R_##Type##Value \
  R_nextPowerOfTwoGte##Type##Value \
    ( \
      R_##Type##Value x \
    ) \
  { \
    if (R_isPowerOfTwo##Type##Value(x)) { \
      return x; \
    } \
    return R_nextPowerOfTwoGt##Type##Value(x); \
  }

Define(Natural8, R_Natural8Value_NumberOfBits)
Define(Natural16, R_Natural16Value_NumberOfBits)
Define(Natural32, R_Natural32Value_NumberOfBits)
Define(Natural64, R_Natural64Value_NumberOfBits)

#undef Define

R_SizeValue
R_nextPowerOfTwoGteSizeValue
  (
    R_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return R_nextPowerOfTwoGteNatural64Value(x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return R_nextPowerOfTwoGteNatural32Value(x);
#else
  #error("environment not (yet) supported")
#endif
}
