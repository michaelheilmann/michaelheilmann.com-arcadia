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

#include "R/isPowerOfTwo.h"

#include "R/countLeadingZeroes.h"
#include "R/nextPowerOfTwoGt.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Boolean.h"

R_BooleanValue
R_isPowerOfTwoInteger8Value
  (
    R_Integer8Value x
  )
{
  if (x <= 0) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoInteger16Value
  (
    R_Integer16Value x
  )
{
  if (x <= 0) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoInteger32Value
  (
    R_Integer32Value x
  )
{
  if (x <= 0) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoInteger64Value
  (
    R_Integer64Value x
  )
{
  if (!x) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoNatural8Value
  (
    R_Natural8Value x
  )
{
  if (!x) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoNatural16Value
  (
    R_Natural16Value x
  )
{
  if (!x) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoNatural32Value
  (
    R_Natural32Value x
  )
{
  if (!x) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoNatural64Value
  (
    R_Natural64Value x
  )
{
  if (!x) return R_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

R_BooleanValue
R_isPowerOfTwoSizeValue
  (
    R_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return R_isPowerOfTwoNatural64Value((R_Natural64Value)x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return R_isPowerOfTwoNatural32Value((R_Natural32Value)x);
#else
  #error("instruction set architecture not (yet) supported")
#endif 
}
