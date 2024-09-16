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

// Last modified: 2024-09-15

#include "R/nextPowerOfTwoGt.h"

#include "R/countLeadingZeroes.h"
#include "R/JumpTarget.h"
#include "R/Status.h"

#define Define(Type, Suffix, Bits) \
  R_##Type##Value \
  R_nextPowerOfTwoGt_##Suffix \
    ( \
      R_##Type##Value x \
    ) \
  { \
  static R_##Type##Value const greatestPowerOfTwo = R_##Type##Value_Literal(1) << (Bits - 1); \
  if (x < R_##Type##Value_Literal(1)) { \
    return R_##Type##Value_Literal(1); \
  } \
  if (x >= greatestPowerOfTwo) { \
    R_setStatus(R_Status_NotExists); \
    R_jump(); \
  } \
  R_SizeValue i = R_countLeadingZeroes_##Suffix(x); \
  R_##Type##Value t = R_##Type##Value_Literal(1) << (Bits - i); \
  if (i == R_##Type##Value_Literal(0) && t != x) { \
    R_setStatus(R_Status_NotExists); \
    R_jump(); \
  } \
  return i; \
}

Define(Natural8, n8, R_Natural8Value_NumberOfBits)
Define(Natural16, n16, R_Natural16Value_NumberOfBits)
Define(Natural32, n32, R_Natural32Value_NumberOfBits)
Define(Natural64, n64, R_Natural64Value_NumberOfBits)

#undef Define

R_SizeValue
R_nextPowerOfTwoGt_s
  (
    R_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return R_nextPowerOfTwoGt_n64(x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return R_nextPowerOfTwoGt_n32(x);
#else
  #error("environment not (yet) supported")
#endif
}
