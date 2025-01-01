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

// Last modified: 2024-09-29

#include "Arcadia/Ring1/Implementation/nextPowerOfTwoGt.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

#define Define(Type, Suffix, Bits) \
Type##Value \
Arcadia_nextPowerOfTwoGreaterThan##Suffix##Value \
  ( \
    Arcadia_Process* process, \
    Type##Value x \
  ) \
{ \
  /* i is Bits is x is 0. i is Bits - 1 if x is 1. i is Bits - 2 if x is 2 or 3. ... i is 0 if x >= greatestPowerOfTwo. Consequently the shift is Bits - i.*/ \
  Arcadia_SizeValue numberOfLeadingZeroes = Arcadia_countLeadingZeroes##Suffix##Value(process, x); \
  if (!numberOfLeadingZeroes) { \
    Arcadia_Process_setStatus(process, Arcadia_Status_NotExists); \
    Arcadia_Process_jump(process); \
  } \
  Arcadia_SizeValue shift = Bits - numberOfLeadingZeroes; \
  Type##Value t = Type##Value_Literal(1) << shift; \
  return t; \
}

Define(Arcadia_Natural8, Natural8, Arcadia_Natural8Value_NumberOfBits)
Define(Arcadia_Natural16, Natural16, Arcadia_Natural16Value_NumberOfBits)
Define(Arcadia_Natural32, Natural32, Arcadia_Natural32Value_NumberOfBits)
Define(Arcadia_Natural64, Natural64, Arcadia_Natural64Value_NumberOfBits)

#undef Define

Arcadia_SizeValue
R_nextPowerOfTwoGreaterThanSizeValue
  (
    Arcadia_Process* process,
    Arcadia_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return Arcadia_nextPowerOfTwoGreaterThanNatural64Value(process, x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return Arcadia_nextPowerOfTwoGreaterThanNatural32Value(process, x);
#else
  #error("environment not (yet) supported")
#endif
}
