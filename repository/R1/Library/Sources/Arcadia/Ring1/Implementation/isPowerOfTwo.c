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

#include "Arcadia/Ring1/Implementation/isPowerOfTwo.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger8Value
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value x
  )
{
  if (x <= 0) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger16Value
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value x
  )
{
  if (x <= 0) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger32Value
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value x
  )
{
  if (x <= 0) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoInteger64Value
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value x
  )
{
  if (!x) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural8Value
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value x
  )
{
  if (!x) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural16Value
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value x
  )
{
  if (!x) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural32Value
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value x
  )
{
  if (!x) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoNatural64Value
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value x
  )
{
  if (!x) return Arcadia_BooleanValue_False;
  else return 0 == (x & (x - 1));
}

Arcadia_BooleanValue
Arcadia_isPowerOfTwoSizeValue
  (
    Arcadia_Process* process,
    Arcadia_SizeValue x
  )
{
#if Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X64
  return Arcadia_isPowerOfTwoNatural64Value(process, (Arcadia_Natural64Value)x);
#elif Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X86
  return Arcadia_isPowerOfTwoNatural32Value(process, (Arcadia_Natural32Value)x);
#else
  #error("instruction set architecture not (yet) supported")
#endif 
}
