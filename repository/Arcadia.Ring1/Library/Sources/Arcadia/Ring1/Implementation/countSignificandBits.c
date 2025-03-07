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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/countSignificandBits.h"

#include "Arcadia/Ring1/Include.h"

#if Arcadia_Configuration_CompilerC == Arcadia_Configuration_CompilerC_Msvc
  #include <intrin.h>
#endif

Arcadia_SizeValue
Arcadia_countSignificandBitsInteger8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countSignificandBitsNatural8Value(thread, (Arcadia_Natural8Value)x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsInteger16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countSignificandBitsNatural16Value(thread, (Arcadia_Natural16Value)x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countSignificandBitsNatural32Value(thread, (Arcadia_Natural32Value)x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsInteger64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countSignificandBitsNatural64Value(thread, (Arcadia_Natural64Value)x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value x
  )
{
  return 8 - Arcadia_countLeadingZeroesNatural8Value(thread, x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value x
  )
{
  return 16 - Arcadia_countLeadingZeroesNatural16Value(thread, x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value x
  )
{
  return 32 - Arcadia_countLeadingZeroesNatural32Value(thread, x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value x
  )
{
  return 64 - Arcadia_countLeadingZeroesNatural64Value(thread, x);
}

Arcadia_SizeValue
Arcadia_countSignificandBitsSizeValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue x
  )
{
#if Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X64
  return Arcadia_countSignificandBitsNatural64Value(thread, x);
#elif Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X86
  return Arcadia_countSignificandBitsNatural32Value(thread, x);
#else
  #error("environment not (yet) supported")
#endif
}
