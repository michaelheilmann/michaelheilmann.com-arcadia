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

// Last modified: 2024-09-29

#include "R/nextPowerOfTwoGt.h"

#include "R/countLeadingZeroes.h"
#include "R/JumpTarget.h"
#include "R/Status.h"

#define Define(Type, Bits) \
R_##Type##Value \
R_nextPowerOfTwoGt##Type##Value \
  ( \
    R_##Type##Value x \
  ) \
{ \
  /* i is Bits is x is 0. i is Bits - 1 if x is 1. i is Bits - 2 if x is 2 or 3. ... i is 0 if x >= greatestPowerOfTwo. Consequently the shift is Bits - i.*/ \
  R_SizeValue numberOfLeadingZeroes = R_countLeadingZeroes##Type##Value(x); \
  if (!numberOfLeadingZeroes) { \
    R_setStatus(R_Status_NotExists); \
    R_jump(); \
  } \
  R_SizeValue shift = Bits - numberOfLeadingZeroes; \
  R_##Type##Value t = R_##Type##Value_Literal(1) << shift; \
  return t; \
}

Define(Natural8, R_Natural8Value_NumberOfBits)
Define(Natural16, R_Natural16Value_NumberOfBits)
Define(Natural32, R_Natural32Value_NumberOfBits)
Define(Natural64, R_Natural64Value_NumberOfBits)

#undef Define

R_SizeValue
R_nextPowerOfTwoGtSizeValue
  (
    R_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return R_nextPowerOfTwoGtNatural64Value(x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return R_nextPowerOfTwoGtNatural32Value(x);
#else
  #error("environment not (yet) supported")
#endif
}
